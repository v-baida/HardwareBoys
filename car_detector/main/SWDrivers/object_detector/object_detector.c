#include "object_detector.h"

void ObjDetector_Init()
{
    uint64_t gpio_mask = BIT(OBJ_DETECT_CHANNEL_0) | BIT(OBJ_DETECT_CHANNEL_1) | 
                         BIT(OBJ_DETECT_CHANNEL_2) | BIT(OBJ_DETECT_CHANNEL_3);
    ESP_ERROR_CHECK(config_optoel_gpio(gpio_mask));
}

bool DetectObject(uint8_t channel_num)
{
    bool ret_val;

    ret_val = (bool)optoel_get_state(channel_num);
    return !ret_val; // Active level is 0 voltage
}

// bool ObjDetector_StateChanged(bool* state_arr, uint16_t len) 
// {
// 
// }