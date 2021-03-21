/* HTTPS GET Example using plain mbedTLS sockets
 *
 * Contacts the howsmyssl.com API via TLS v1.2 and reads a JSON
 * response.
 *
 * Adapted from the ssl_client1 example in mbedtls.
 *
 * Original Copyright (C) 2006-2016, ARM Limited, All Rights Reserved, Apache 2.0 License.
 * Additions Copyright (C) Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD, Apache 2.0 License.
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_netif.h"
#include "esp_http_client.h"
#include "driver/gpio.h"
#include "optoelectronic_sensor.h"
#include "object_detector.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "esp_tls.h"
#include "esp_crt_bundle.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_URL "https://che-smart-parking.000webhostapp.com/post-esp-data.php"
#define API_KEY_VALUE "tPmAT5Ab3j7F9"

#define AMOUNT_OF_OBJ_SENSORS 4

QueueHandle_t xMailbox;

static const char *TAG = "example";

static void http_task(void *pvParameters)
{
    static char str[1024];
    char local_objects_state_arr[AMOUNT_OF_OBJ_SENSORS];

    esp_http_client_config_t config = {
        .url = WEB_URL,
        .method = HTTP_METHOD_POST,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");

    while (1)
    {
        xQueueReceive(xMailbox, local_objects_state_arr, 0xffffffff);
        sprintf(str, "api_key=%s&value1=%d&value2=%d&value3=%d&value4=%d",
                API_KEY_VALUE, local_objects_state_arr[0], local_objects_state_arr[1],
                local_objects_state_arr[2], local_objects_state_arr[3]);
        // ESP_LOGI(TAG, "Request str: %s\r\n", str);
        esp_http_client_set_post_field(client, str, strlen(str));
        ESP_ERROR_CHECK(esp_http_client_perform(client));
    }
}

static void object_detector_task(void *pvParameters)
{
    bool objects_state_arr[AMOUNT_OF_OBJ_SENSORS];
    // ESP_LOGI(TAG, "sizeof(objects_state_arr)%d\r\n", sizeof(objects_state_arr));
    ObjDetector_Init();
    while (1)
    {
        objects_state_arr[0] = DetectObject(OBJ_DETECT_CHANNEL_0);
        objects_state_arr[1] = DetectObject(OBJ_DETECT_CHANNEL_1);
        objects_state_arr[2] = DetectObject(OBJ_DETECT_CHANNEL_2);
        objects_state_arr[3] = DetectObject(OBJ_DETECT_CHANNEL_3);

        xQueueSend(xMailbox, (void *)objects_state_arr, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_LOGE(TAG, "Hello world!\n");

    xMailbox = xQueueCreate(1, sizeof(bool *));

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(object_detector_task, "object_detector", 8192, NULL, 4, NULL);
    xTaskCreate(http_task, "http_task", 8192, NULL, 5, NULL);
}