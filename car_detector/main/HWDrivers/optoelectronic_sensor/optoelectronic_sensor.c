#include "optoelectronic_sensor.h"

esp_err_t config_optoel_gpio(uint64_t gpio_mask) {

    gpio_config_t gpio_conf_str = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = gpio_mask
    };

    return gpio_config(&gpio_conf_str);
}

uint8_t optoel_get_state(gpio_num_t gpio_num) {
    return gpio_get_level(gpio_num);
}