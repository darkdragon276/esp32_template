#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_ADD_INCLUDEDIRS := ./include ./lib/gpio_isr ./lib/adc_button ./lib/button ./audio/include
COMPONENT_SRCDIRS :=  . ./lib/button ./lib/adc_button ./lib/gpio_isr ./audio
COMPONENT_PRIV_INCLUDEDIRS := ./lib/button

CFLAGS+=-D__FILENAME__=\"$(<F)\"
