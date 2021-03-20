#ifndef __OPTOELEC_H__
#define __OPTOELEC_H__

#include "driver/gpio.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"

esp_err_t config_optoel_gpio(uint64_t gpio_mask);
uint8_t optoel_get_state(gpio_num_t gpio_num);

#endif //__OPTOELEC_H__