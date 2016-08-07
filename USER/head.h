#ifndef __HEAD_H
#define __HEAD_H

#include "stm32f10x.h"


u8 tim_flag3;//用于保证产生0.2秒的变量


extern void TIM3_Configuration(void);
extern void LED_Confrigration(void);
extern void KEY_Confrigration(void);


#endif

