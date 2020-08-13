#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h" 
#include "define.h"

static xQueueHandle dd_gpio_Queue_st = NULL; // declare variable to receive the value of a func pointer

static void IRAM_ATTR dd_gpio_isr_handler(void* intr_value_vpt){
    uint32_t gpio_num = (uint32_t) intr_value_vpt; // add value of gpio to a variable.
    xQueueSendFromISR(dd_gpio_Queue_st, &gpio_num, NULL); // function to send value of gpio out.
}
static void gpio_task (void* arg){
    unit_32_t gpioStatus;
    while(1){
        printf("%d", gpioStatus);
    }
} // this func to create the task if the interrupt happen

void dd_gpio_Config_func(dd_gpio_Config_tst gpioConfig){
    gpio_config((dd_gpio_Config_tst*)&gpioConfig); // get the value of interrupt signal
    gpio_set_intr_type(gpioConfig.dd_gpio_num_0_en, gpioConfig.dd_gpio_intr_posEdge_en); // set interrupt type (gpio 0, rising)
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE); // interrupt whenever the signal is asserted
    gpio_isr_handle_add(gpioConfig.dd_gpio_num_0_en, gpioConfig.isrHandler_func, gpioConfig.isrArgument);
    dd_gpio_Queue_st = xQueueCreate(gpioConfig.queueLenght_cu32, sizeof(uint32_t));
} // this func to configurate gpio pin 
int app_main(void){
    while(1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
}