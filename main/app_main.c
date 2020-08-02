#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

int state = 0;
static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR button_isr(void* arg){
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}
static void Task_1(void*arg) {
    while(1) {  
        printf("ngat 1 giay\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
static void Task_2(void*arg){
    while(1){  
        printf("ngat 3 giay\n");
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}
static void Task_3(void*arg){
    while(1){  
        printf("ngat 5 giay\n");
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}        
static void Task(void* arg){
    uint32_t io_num = 1;
    while(1){
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)){
            if(io_num != GPIO_NUM_0){
                printf("%d", io_num);
                continue;
            }
        // state = io_num;
        state ++;
        if(state == 1){
            xTaskCreate(Task_1, "Task_1", 2048, NULL, 10, NULL);
        } else if(state == 2){
            xTaskCreate(Task_2, "Task_2", 2048, NULL, 10, NULL);
        } else if(state == 3){
            xTaskCreate(Task_3, "Task_3", 2048, NULL, 20, NULL);
        }else if (state == 4){
            state = 0;
        }
        xQueueReset(gpio_evt_queue);
        vTaskDelay(500 / portTICK_RATE_MS);
        }
    }
}
void app_main(){
    // implement button
    gpio_config_t button_config ;
    button_config.pin_bit_mask = BIT0 ; //(1ull << GPIO_NUM_0);
    button_config.mode = GPIO_MODE_INPUT;
    button_config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    button_config.intr_type = GPIO_INTR_POSEDGE;

    gpio_config(&button_config);
    gpio_set_intr_type (GPIO_NUM_0,GPIO_INTR_POSEDGE);
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    
    gpio_install_isr_service (ESP_INTR_FLAG_EDGE);
    gpio_isr_handler_add(GPIO_NUM_0, button_isr, (void*) GPIO_NUM_0); // (variable interrupt, isr function,...)
    xTaskCreate(Task, "Task", 2048, NULL, 10, NULL);
    while(1){
        printf("tick\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}