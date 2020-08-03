#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define TASK_CREATE(name)   xTaskCreate(task_##name##, "task_##name##", 1024, NULL, 10 + name, &task_##name##)

typedef enum {
    TASK_NONE,
    TASK_1S,
    TASK_3S,
    TASK_5S,
    TASK_MAX,
} gpio_TaskType_ten;

static gpio_TaskType_ten task_state_en = TASK_NONE;
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
            printf("in button isr \n");
            switch(task_state_en++) {
                case TASK_1S:
                    TASK_CREATE(TASK_1S);
                break;
                case TASK_3S:
                    TASK_CREATE(TASK_3S);
                break;
                case TASK_5S:
                    TASK_CREATE(TASK_5S);
                break;
                default:
                    printf("task state is unknow \n");
                break;
            }
            vTaskDelay(500 / portTICK_RATE_MS);
            xQueueReset(gpio_evt_queue);  
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