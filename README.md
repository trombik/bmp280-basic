# `bmp280-basic`

An example project for ESP8266 and `BME280`.

ESP8266 communicate with the sensor over I2C.

The ESP8266 does:

- Connect to WiFi AP (optional)
- Sync time (optional)
- Read sensor values from `BME280`
- Print values to serial console
- Deep sleep

See `Project configuration` in `make menuconfig` for options.

## Pins

| ESP8266   | BME280 |
|-----------|--------|
| `GPIO` 4  | SDA    |
| `GPIO` 5  | SCL    |

Also, connect `GPIO` 16 to `RST` to make `esp_deep_sleep()` to work.

## Example log

```console
 ets Jan  8 2013,rst cause:2, boot mode:(3,0)

load 0x40100000, len 7168, room 16
tail 0
chksum 0xed
load 0x3ffe8408, len 24, room 8
tail 0
chksum 0x64
load 0x3ffe8420, len 3540, room 8
tail 12
chksum 0x49
I (61) boot: ESP-IDF v3.2-480-g2524a695-dirty 2nd stage bootloader
I (61) boot: compile time 02:26:52
I (70) qio_mode: Enabling default flash chip QIO
I (70) boot: SPI Speed      : 40MHz
I (76) boot: SPI Mode       : QIO
I (82) boot: SPI Flash Size : 2MB
I (88) boot: Partition Table:
I (94) boot: ## Label            Usage          Type ST Offset   Length
I (105) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (117) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (128) boot:  2 factory          factory app      00 00 00010000 000f0000
I (140) boot: End of partition table
I (147) esp_image: segment 0: paddr=0x00010010 vaddr=0x40210010 size=0x5f0f4 (389364) map
I (291) esp_image: segment 1: paddr=0x0006f10c vaddr=0x4026f104 size=0x0f66c ( 63084) map
I (312) esp_image: segment 2: paddr=0x0007e780 vaddr=0x3ffe8000 size=0x006d0 (  1744) load
I (313) esp_image: segment 3: paddr=0x0007ee58 vaddr=0x40100000 size=0x00fa0 (  4000) load
I (324) esp_image: segment 4: paddr=0x0007fe00 vaddr=0x40100fa0 size=0x05880 ( 22656) load
I (344) boot: Loaded app from partition at offset 0x10000
I (367) system_api: Base MAC address is not set, read default base MAC address from EFUSE
I (371) system_api: Base MAC address is not set, read default base MAC address from EFUSE
phy_version: 1159.0, 85b471e, Apr 21 2020, 17:03:08, RTOS new
I (437) phy_init: phy ver: 1159_0
I (439) reset_reason: RTC reset 2 wakeup 0 store 8, reason is 8
I (444) APP_MAIN: Initializing NVS
I (450) APP_MAIN: Configuring WiFi
I (474) wifi_connect_esp8266: start the WIFI SSID:[makers]
I (477) wifi_connect_esp8266: Waiting for wifi
I (3089) wifi: state: 0 -> 2 (b0)
I (3093) wifi: state: 2 -> 3 (0)
I (3097) wifi: state: 3 -> 5 (10)
I (3099) wifi: pm start, type: 1
I (4088) tcpip_adapter: sta ip: 192.168.99.22, mask: 255.255.255.0, gw: 192.168.99.254
I (4093) APP_MAIN: Configured WiFi. Waiting for WIFI_CONNECTED_BIT...
I (4099) APP_MAIN: Connected to WiFi
I (4106) APP_MAIN: Configuring time
I (4113) APP_MAIN: Current time: 1970-01-01T00:00:03Z
I (4121) APP_MAIN: Time is not set yet. Setting time over NTP
I (4131) init_sntp: Initializing SNTP: mode: POLL server: pool.ntp.org
I (4142) init_sntp: Waiting for system time to be set... (1/10)
I (6145) init_sntp: Waiting for system time to be set... (2/10)
I (8146) init_sntp: Waiting for system time to be set... (3/10)
I (10147) init_sntp: Current time: 2020-06-07T17:52:38Z
I (10149) APP_MAIN: Configured time
I (10152) gpio: GPIO[4]| InputEn: 0| OutputEn: 1| OpenDrain: 1| Pullup: 0| Pulldown: 0| Intr:0
I (10162) gpio: GPIO[5]| InputEn: 0| OutputEn: 1| OpenDrain: 1| Pullup: 0| Pulldown: 0| Intr:0
BMP280: found BME280
Pressure: 59751.68 Pa, Temperature: 22.25 C, Humidity: 79.11
Uptime 9 sec
Sleeping 30 sec
I (10317) wifi: state: 5 -> 0 (0)
I (10319) wifi: pm stop
E (10322) wifi_connect_esp8266: Disconnect reason : 8
I (10325) wifi_connect_esp8266: Retrying to connect to the AP
```
