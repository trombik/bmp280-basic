COMPONENT_ADD_INCLUDEDIRS = . include/
COMPONENT_OBJS :=  main.o sntp_connect.o

ifdef CONFIG_IDF_TARGET_ESP8266
COMPONENT_OBJS += wifi_connect_esp8266.o
endif
