#ifndef _ESP_BUTTON_
#define _ESP_BUTTON_

#include "driver/gpio.h"
#include "audio_error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_GPIO_OUTPUT_IO_1 1
#define DD_GPIO_OUTPUT_IO_2 2
#define DD_GPIO_OUTPUT_IO_3 3
#define DD_GPIO_OUTPUT_IO_4 4
#define DD_GPIO_OUTPUT_IO_5 5


typedef enum {
    dd_gpio_intr_disable_en = 0,     //  disable interrupt
    dd_gpio_intr_posEdge_en = 1,     //  interrupt when rising edge
    dd_gpio_intr_negEdge_en = 2,     //  interrupt when falling edge
    dd_gpio_intr_anyEdge_en = 3,     //  interrupt whenever the sign change, falling and rising
    dd_gpio_intr_lowLevel_en = 4,    // interrupt when signal is low (0)
    dd_gpio_intr_highLevel_en = 5,   // interrupt when signal is high (1)
    dd_gpio_intr_max,
} dd_gpio_intr_type_en;

typedef struct {
    uint64_t gpioMask_u64;
    gpio_mode_t mode_en;
    gpio_pull_mode_t pullUp_en;
    gpio_int_type_t intrType_en;
    gpio_num_t ioNum_en;
    void (*isrHandler_func)(void* arg);
    void * isrArgument_v;
    const UBaseType_t queueLenght_cu32;
    UBaseType_t queueSize_u32;
} dd_gpio_Config_tst;

#ifdef __cplusplus
}
#endif

#endif