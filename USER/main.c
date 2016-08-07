#include "head.h"


int main(void)
{
	u8 count=0;
	u8 LED0=0;
	u8 LED1=0;
	TIM3_Configuration();
	LED_Confrigration();
  KEY_Confrigration();
	while(1)
	{
		if(1==tim_flag3)
		{
			tim_flag3=0;
			count++;
			if(240==count)count=0;
			if(0==(count%2))LED0=!LED0;
			if(0==(count%4))LED1=!LED1;
		}
		if(1==LED0)GPIO_ResetBits(GPIOA,GPIO_Pin_8); //PA.8=0 输出低,打开LED0
		else GPIO_SetBits(GPIOA,GPIO_Pin_8); //PA.8=1 输出高,关闭LED0
		if(1==LED1)GPIO_ResetBits(GPIOD,GPIO_Pin_2); //PD.2=0 输出低,打开LED1
		else GPIO_SetBits(GPIOD,GPIO_Pin_2); //PD.2=1 输出高 ,关闭LED1
	}
}






