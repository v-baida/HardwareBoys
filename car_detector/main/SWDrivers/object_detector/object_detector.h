#ifndef __OBJECT_DETECTOR_H__
#define __OBJECT_DETECTOR_H__

#include "optoelectronic_sensor.h"

#define OBJ_DETECT_CHANNEL_0 GPIO_NUM_2
#define OBJ_DETECT_CHANNEL_1 GPIO_NUM_18
#define OBJ_DETECT_CHANNEL_2 GPIO_NUM_19
#define OBJ_DETECT_CHANNEL_3 GPIO_NUM_5

void ObjDetector_Init();
bool DetectObject(uint8_t channel_num); 
// bool ObjDetector_StateChanged(bool* state_arr, uint16_t len);

#endif //__OBJECT_DETECTOR_H__