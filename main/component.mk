COMPONENT_ADD_INCLUDEDIRS = . include/
COMPONENT_OBJS :=  main.o

ifdef CONFIG_PROJECT_WIFI_ENABLE
ifdef CONFIG_IDF_TARGET_ESP8266
COMPONENT_OBJS += wifi_connect_esp8266.o
endif
endif

ifdef CONFIG_PROJECT_SNTP_ENABLE
COMPONENT_OBJS += sntp_connect.o
endif
