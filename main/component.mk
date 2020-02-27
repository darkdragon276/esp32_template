#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_ADD_INCLUDEDIRS := ./app .
COMPONENT_SRCDIRS :=  ./app .
COMPONENT_EXTRA_INCLUDES := \
	$(IDF_PATH)/components/freertos/include/freertos \
