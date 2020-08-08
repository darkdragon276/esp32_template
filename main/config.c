#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h" 

#define DD_GPIO_OUTPUT_IO_1 1;
#define DD_GPIO_OUTPUT_IO_2 2;
#define DD_GPIO_OUTPUT_IO_3 3;
#define DD_GPIO_OUTPUT_IO_4 4;
#define DD_GPIO_OUTPUT_IO_5 5;

static xQueueHandle gpio_evt_queue = NULL; // declare variable to receive the value of 

static void IRAM_ATTR button_isr_handler(void* value_of_intr_gpio){
    uint32_t gpio_num = (uint32_t) value_of_intr_gpio; // add value of gpio to a variable.
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL); // function to send value of gpio out.
}
    static void gpio_task(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}
void intr_config(int a){
    dd_gpio_config_t button_config;
    button_config.pin_bit_mask = BIT0; // declare GPIO 0 for interrupt signal input 
    button_config.mode = GPIO_MODE_INPUT; // set up GPIO is input
    button_config.pull_up_en = GPIO_PULLUP_ENABLE; // set volrage for gpio 0 to high
    button_config.intr_type = GPIO_INTR_POSEDGE; // set interrupt when the signal is rising. 0 -> 1
    gpio_config(&button_config); // get the value of button signal
    gpio_set_intr_type(GPIO_NUM_0,GPIO_INTR_POSEDGE); // set interrupt type (gpio 0, rising)
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE); // interrupt whenever the signal is asserted
    gpio_isr_handle_add(GPIO_NUM_0, button_isr_handler, (void*) GPIO_NUM_0) 
  
}
int app_main(void){
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

}