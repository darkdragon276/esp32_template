/* GPIO Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "esp_log.h"

typedef enum {
    TASK_NONE,
    TASK_1S,
    TASK_3S,
    TASK_5S,
    TASK_MAX,
} gpio_TaskType_ten;

static gpio_TaskType_ten task_state_en = TASK_NONE;
static xQueueHandle gpio_evt_queue = NULL;
TaskHandle_t task_1 = NULL, task_2 = NULL, task_3 = NULL;

static void task_1s(void* arg) {
    // ESP_LOGI("GPIO", "enter task 1s");
    while(1) {
        printf("enter task 1s \n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}


static void task_3s(void* arg) {
    // ESP_LOGI("GPIO", "enter task 3s");
    while(1) {
        printf("enter task 3s \n");
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}


static void task_5s(void* arg) {
    // ESP_LOGI("GPIO", "enter task 5s");
    while(1) {
        printf("enter task 5s \n");
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}

static void IRAM_ATTR button_isr(void *arg) {
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);

}

static void gpio_task(void* arg)
{
    uint32_t io_num;
    while(1) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            if(io_num != GPIO_NUM_0) {
                continue;
            }
            printf("in button isr \n");
            switch(task_state_en++) {
                case TASK_1S:
                    xTaskCreate(task_1s, "create task 1s", 1024, NULL, 10, &task_1);
                break;
                case TASK_3S:
                    xTaskCreate(task_3s, "create task 1s", 1024, NULL, 11, &task_2);
                break;
                case TASK_5S:
                    xTaskCreate(task_5s, "create task 1s", 1024, NULL, 12, &task_3);
                break;
                default:
                    printf("task state is unknow");
                break;
            }
            vTaskDelay(500 / portTICK_RATE_MS);
            xQueueReset(gpio_evt_queue);  
        }
    }
}

void app_main() {
    // implement button
    gpio_config_t button_config;
    button_config.pin_bit_mask = (1ULL << GPIO_NUM_0);
    button_config.mode = GPIO_MODE_INPUT;
    button_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    button_config.pull_up_en = GPIO_PULLUP_ENABLE;
    button_config.intr_type = GPIO_INTR_POSEDGE;
    gpio_config(&button_config);


    gpio_evt_queue = xQueueCreate(20, sizeof(uint32_t));
    xTaskCreate(gpio_task, "gpio_task_example", 1024, NULL, 9, NULL);

    gpio_set_intr_type(GPIO_NUM_0, GPIO_INTR_ANYEDGE);
    gpio_install_isr_service(GPIO_INTR_DISABLE);
    gpio_isr_handler_add(GPIO_NUM_0, button_isr, (void *)GPIO_NUM_0);

    while(1) {
        printf("in main \n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}