PROJECT_NAME := bmp280-basic

EXTRA_COMPONENT_DIRS := components/esp-idf-lib/components
EXCLUDE_COMPONENTS = "max7219 mcp23x17"

include $(IDF_PATH)/make/project.mk
