#ifndef __OBJECT_DETECTOR_H__
#define __OBJECT_DETECTOR_H__

#include "optoelectronic_sensor.h"

#define OBJ_DETECT_CHANNEL_0 GPIO_NUM_2

void ObjDetector_Init();
bool DetectObject(uint8_t channel_num); 

#endif //__OBJECT_DETECTOR_H__