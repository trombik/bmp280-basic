#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <esp_system.h>
#include <bmp280.h>
#include <string.h>
#include <esp_sleep.h>
#include <esp_timer.h>
#include <nvs_flash.h>
#include <esp_err.h>
#include <esp_log.h>
#include <time.h>

#include "sntp_connect.h"
#include "wifi_connect.h"

#if defined(CONFIG_IDF_TARGET_ESP8266)
#define SDA_GPIO 4
#define SCL_GPIO 5
#else
#define SDA_GPIO 16
#define SCL_GPIO 17
#endif

#define TAG "APP_MAIN"
#define NOT_WAIT_FOR_ALL_BITS pdFALSE
#define NOT_CLEAR_ON_EXIT pdFALSE
#define WIFI_CONNECTED_WAIT_TICK (1000 / portTICK_PERIOD_MS)

EventGroupHandle_t s_wifi_event_group;
int WIFI_CONNECTED_BIT = BIT0;

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
    int64_t uptime_in_msec;
    time_t now;
    struct tm timeinfo;
    char time_string[64];
    esp_err_t err;

    ESP_LOGI(TAG, "Initializing NVS");
    err = nvs_flash_init();
#if defined(CONFIG_IDF_TARGET_ESP32)
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
#elif defined(CONFIG_IDF_TARGET_ESP8266)
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
#endif // defined(CONFIG_IDF_TARGET_ESP32)

        /* OTA app partition table has a smaller NVS partition size than the
         * non-OTA partition table. This size mismatch may cause NVS
         * initialization to fail.  If this happens, we erase NVS partition
         * and initialize NVS again.
         */
        ESP_LOGI(TAG, "Re-Initializing NVS");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    ESP_LOGI(TAG, "Configuring WiFi");
    ESP_ERROR_CHECK(init_wifi());
    ESP_LOGI(TAG, "Configured WiFi. Waiting for WIFI_CONNECTED_BIT...");
    while (1) {
        if (xEventGroupWaitBits(s_wifi_event_group,
                                WIFI_CONNECTED_BIT,
                                NOT_WAIT_FOR_ALL_BITS,
                                NOT_CLEAR_ON_EXIT,
                                WIFI_CONNECTED_WAIT_TICK)) {
            break;
        }
    }

    ESP_LOGI(TAG, "Configuring time");
    if (time(&now) == -1) {
        ESP_LOGI(TAG, "time()");
    }
    localtime_r(&now, &timeinfo);
    strftime(time_string, sizeof(time_string), "%FT%TZ", &timeinfo);
    ESP_LOGI(TAG, "Current time: %s", time_string);
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGI(TAG, "Time is not set yet. Setting time over NTP");
        if ((err = init_sntp()) != ESP_OK) {
            ESP_LOGE(TAG, "init_sntp(): %x", err);
            goto fail;
        }
    }
    ESP_LOGI(TAG, "Configured time");

    ESP_ERROR_CHECK(i2cdev_init());
    bmp280_test(NULL);
    uptime_in_msec = esp_timer_get_time() / 1000ULL;
    printf("Uptime %lld sec\n", uptime_in_msec / 1000);
    printf("Sleeping %d sec\n", sleep_sec);

fail:
    /* wait a bit for the message above to be printed */
    vTaskDelay(100 / portTICK_PERIOD_MS);

    esp_deep_sleep(sec_to_usec(CONFIG_DEEP_SLEEP_TIME_SEC));
}
