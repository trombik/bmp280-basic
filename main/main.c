#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <bmp280.h>
#include <string.h>
#include <esp_sleep.h>

#if defined(CONFIG_IDF_TARGET_ESP8266)
#define SDA_GPIO 4
#define SCL_GPIO 5
#else
#define SDA_GPIO 16
#define SCL_GPIO 17
#endif

void bmp280_test(void *pvParamters)
{
    bmp280_params_t params;
    bmp280_init_default_params(&params);
    bmp280_t dev;
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bool bme280p = dev.id == BME280_CHIP_ID;
    printf("BMP280: found %s\n", bme280p ? "BME280" : "BMP280");

    float pressure, temperature, humidity;

    if (bmp280_read_float(&dev, &temperature, &pressure, &humidity) != ESP_OK)
    {
        printf("Temperature/pressure reading failed\n");
        goto fail;
    }

    /* float is used in printf(). you need non-default configuration in
     * sdkconfig for ESP8266, which is enabled by default for this
     * example. see sdkconfig.defaults.esp8266
     */
    printf("Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);
    if (bme280p)
        printf(", Humidity: %.2f\n", humidity);
    else
        printf("\n");
fail:
    return;
}

uint32_t sec_to_usec(int sec)
{
    return sec * 1000000;
}

void app_main()
{
    int sleep_sec = 30;

    ESP_ERROR_CHECK(i2cdev_init());
    bmp280_test(NULL);
    printf("Sleeping %d sec\n", sleep_sec);

    /* wait a bit for the message above to be printed */
    vTaskDelay(100 / portTICK_PERIOD_MS);

    esp_deep_sleep(sec_to_usec(CONFIG_DEEP_SLEEP_TIME_SEC));
}
