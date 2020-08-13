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

typedef enum {
    dd_gpio_num_0_en = 0,
    dd_gpio_num_1_en = 1,
    dd_gpio_num_2_en = 2,
    dd_gpio_num_3_en = 3,
    dd_gpio_num_4_en = 4,
    dd_gpio_num_5_en = 5,
    dd_gpio_num_6_en = 6,
    dd_gpio_num_7_en = 7,
    dd_gpio_num_8_en = 8,
    dd_gpio_num_9_en = 9,
    dd_gpio_num_10_en = 10,
    dd_gpio_num_11_en = 11,
    dd_gpio_num_12_en = 12,
    dd_gpio_num_13_en = 13,
    dd_gpio_num_14_en = 14,
    dd_gpio_num_15_en = 15,
    dd_gpio_num_16_en = 16,
    dd_gpio_num_17_en = 17,
    dd_gpio_num_18_en = 18,
    dd_gpio_num_19_en = 19,
    dd_gpio_num_20_en = 20,
    dd_gpio_num_21_en = 21,
    dd_gpio_num_22_en = 22,
    dd_gpio_num_23_en = 23,
    dd_gpio_num_24_en = 24,
    dd_gpio_num_25_en = 25,
    dd_gpio_num_26_en = 26,
    dd_gpio_num_27_en = 27,
    dd_gpio_num_28_en = 28,
    dd_gpio_num_29_en = 29,
    dd_gpio_num_30_en = 30,
    dd_gpio_num_31_en = 31,
    dd_gpio_num_32_en = 32,
    dd_gpio_num_33_en = 33,
    dd_gpio_num_34_en = 34,
    dd_gpio_num_35_en = 35,
    dd_gpio_num_36_en = 36,
    dd_gpio_num_37_en = 37,
    dd_gpio_num_38_en = 38,
    dd_gpio_num_39_en = 39,
    dd_gpio_num_max_en,
} dd_gpio_num_en; // gpio number

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

void dd_gpio_Config_func(dd_gpio_Config_tst gpioConfig);
/**
 * @brief {function description}
 * @param[in] signal input form gpio
 * @return this func use to config the gpio pin
 */

#ifdef __cplusplus
}
#endif

#endif