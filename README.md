# `bmp280-basic`

An example project for ESP8266 and `BMP280` and `BME280`.

ESP8266 communicate with the sensor over I2C.

The ESP8266 does:

- Connect to WiFi AP (optional)
- Sync time (optional)
- Read sensor values from `BME280`
- Print values to serial console
- Deep sleep

See `Project configuration` in `make menuconfig` for options.

## Rationales

I want a simple example to make a sensor device. Read values from a sensor,
do something, and sleep. Some devices need WiFi access to send the values to
somewhere. Some devices need synchronized time for display, such as LCD.

## Requirements

The example uses float in `printf(3)`. `CONFIG_NEWLIB_LIBRARY_LEVEL_NORMAL`
must be set to `y` in `sdkconfig`.

## Pins

| ESP8266   | BME280 |
|-----------|--------|
| `GPIO` 4  | SDA    |
| `GPIO` 5  | SCL    |

Also, connect `GPIO` 16 to `RST` to make `esp_deep_sleep()` to work.

## Example log

```console
 ets Jan  8 2013,rst cause:2, boot mode:(3,6)

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
I (61) boot: compile time 03:20:11
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
I (147) esp_image: segment 0: paddr=0x00010010 vaddr=0x40210010 size=0x5f294 (389780) map
I (291) esp_image: segment 1: paddr=0x0006f2ac vaddr=0x4026f2a4 size=0x0f694 ( 63124) map
I (313) esp_image: segment 2: paddr=0x0007e948 vaddr=0x3ffe8000 size=0x006d0 (  1744) load
I (314) esp_image: segment 3: paddr=0x0007f020 vaddr=0x40100000 size=0x00fa0 (  4000) load
I (324) esp_image: segment 4: paddr=0x0007ffc8 vaddr=0x40100fa0 size=0x05880 ( 22656) load
I (345) boot: Loaded app from partition at offset 0x10000
I (372) system_api: Base MAC address is not set, read default base MAC address from EFUSE
I (376) system_api: Base MAC address is not set, read default base MAC address from EFUSE
phy_version: 1159.0, 85b471e, Apr 21 2020, 17:03:08, RTOS new
I (440) phy_init: phy ver: 1159_0
I (443) reset_reason: RTC reset 2 wakeup 0 store 8, reason is 8
I (448) APP_MAIN: Initializing NVS
I (454) APP_MAIN: Configuring WiFi
I (480) wifi_connect_esp8266: start the WIFI SSID:[makers]
I (483) wifi_connect_esp8266: Waiting for wifi
I (3205) wifi: state: 0 -> 2 (b0)
I (3210) wifi: state: 2 -> 3 (0)
I (3214) wifi: state: 3 -> 5 (10)
I (3216) wifi: pm start, type: 1
I (4209) tcpip_adapter: sta ip: 192.168.99.22, mask: 255.255.255.0, gw: 192.168.99.254
I (4213) APP_MAIN: Configured WiFi. Waiting for WIFI_CONNECTED_BIT...
I (4220) APP_MAIN: Connected to WiFi
I (4226) APP_MAIN: Configuring time
I (4234) APP_MAIN: Current time: 1970-01-01T00:00:03Z
I (4241) APP_MAIN: Time is not set yet. Setting time over NTP
I (4251) init_sntp: Initializing SNTP: mode: POLL server: pool.ntp.org
I (4263) init_sntp: Waiting for system time to be set... (1/10)
I (6267) init_sntp: Current time: 2020-06-07T19:33:34Z
I (6269) APP_MAIN: Configured time
I (6271) gpio: GPIO[4]| InputEn: 0| OutputEn: 1| OpenDrain: 1| Pullup: 0| Pulldown: 0| Intr:0
I (6282) gpio: GPIO[5]| InputEn: 0| OutputEn: 1| OpenDrain: 1| Pullup: 0| Pulldown: 0| Intr:0
BMP280: found BME280
Pressure: 100436.26 Pa, Temperature: 33.79 C, Humidity: 55.38
Uptime 6 sec
Sleeping 30 sec
I (6527) wifi: state: 5 -> 0 (0)
I (6529) wifi: pm stop
E (6532) wifi_connect_esp8266: Disconnect reason : 8
I (6535) wifi_connect_esp8266: Retrying to connect to the AP
```

## License

ISC license unless other license is used in files.

```c
/*
 * Copyright (c) 2020 Tomoyuki Sakurai <y@trombik.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
```
