set(COMPONENT_ADD_INCLUDEDIRS ./include
./lib/adc_button
./lib/gpio_isr
./lib/button
./audio/include
)

# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES driver esp_adc_cal)
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS ./esp_peripherals.c
                ./periph_adc_button.c
                ./periph_button.c
                ./periph_gpio_isr.c
                ./periph_led.c
                ./periph_ws2812.c
                ./lib/button/button.c
                ./lib/adc_button/adc_button.c
                ./lib/gpio_isr/gpio_isr.c
                ./audio/audio_event_iface.c
                ./audio/audio_mem.c
                ./audio/audio_sys.c)

register_component()
