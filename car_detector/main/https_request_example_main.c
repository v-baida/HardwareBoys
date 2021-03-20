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
#define WEB_SERVER "www.howsmyssl.com"
#define WEB_PORT "443"
#define WEB_URL "https://www.howsmyssl.com/a/check"
#define API_KEY_VALUE "tPmAT5Ab3j7F9"
#warning change sensor name!
#define SENSOR_NAME "BME280"
#define SENSOR_LOCATION "Office"

typedef struct objects_struct
{
    bool obj0_state;
    bool obj1_state;
    bool obj2_state;
    bool obj3_state;
} objects_struct_t;

QueueHandle_t xMailbox;
static const char *TAG = "example";

static void http_task(void *pvParameters)
{
    static char str[1024];
    objects_struct_t test_struct;

    while (1)
    {
        xQueuePeek(xMailbox, &test_struct, portMAX_DELAY);
        sprintf(str, "ch0: %d, ch1: %d, ch2: %d, ch3: %d\r\n",
                test_struct.obj0_state, test_struct.obj1_state, test_struct.obj2_state, test_struct.obj3_state);
        ESP_LOGI(TAG, "%s", str);
    }

    // esp_http_client_config_t config = {
    //     .url = WEB_URL,
    //     .method = HTTP_METHOD_POST,
    // };

    // while(1) {

    // esp_http_client_handle_t client = esp_http_client_init(&config);
    // esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");
    // // esp_http_client_send_post_data()
    // sprintf(str, "api_key=%s&value1=%d&value2=%d&value3=%d&value4=%d",
    //         API_KEY_VALUE, SENSOR_NAME, SENSOR_LOCATION, 14, 88, 19, 39);
    // ESP_LOGI(TAG, "Request str: %s\r\n", str);
    // esp_http_client_set_post_field(client, str, strlen(str));
    // ESP_ERROR_CHECK(esp_http_client_perform(client));
    // esp_http_client_cleanup(client);

    // vTaskDelay(pdMS_TO_TICKS(4000));
    // }
}

static void object_detector_task(void *pvParameters)
{
    ObjDetector_Init();
    objects_struct_t obj_data;

    while (1)
    {
        obj_data.obj0_state = DetectObject(OBJ_DETECT_CHANNEL_0);
        obj_data.obj1_state = DetectObject(OBJ_DETECT_CHANNEL_0);
        obj_data.obj2_state = DetectObject(OBJ_DETECT_CHANNEL_0);
        obj_data.obj3_state = DetectObject(OBJ_DETECT_CHANNEL_0);

        // ESP_LOGI(TAG, "ch0: %d, ch1: %d, ch2: %d, ch3: %d\r\n",
        // obj_data.ch0, obj_data.ch1, obj_data.ch2, obj_data.ch3);

        xQueueOverwrite(xMailbox, &obj_data);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGE(TAG, "Hello world!\n");

    xMailbox = xQueueCreate(1, sizeof(objects_struct_t));

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(object_detector_task, "object_detector", 8192, NULL, 4, NULL);
    xTaskCreate(http_task, "http_task", 8192, NULL, 5, NULL);
}
