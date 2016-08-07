#include "sys.h"




/***************************************************************************
*使用TIM3时打开此函数
*TIM3的初始化函数
***************************************************************************/
#define arr3 1999//计数器的自动重装值（真正的自动重装值为arr3+1）
#define psc3 7199//分频系数（真正的分频系数为psc3+1）
void TIM3_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//初始化中断优先级分组的结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//初始化定时器参数的结构体变量初始化
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3定时器时钟
	
	TIM_DeInit(TIM3);//将TIM3设置为默认缺省值
	  
	TIM_TimeBaseStructure.TIM_Period = arr3;//设置自动重装载寄存器的值，保证每次更新中断间隔为200ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc3;//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频1模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//根据设置的参数初始化定时器
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);			 //注意：TIM_TimeBaseInit函数会引发一个UG事件，因此后面的中断标志位一定要被清楚
	 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//使能 TIM3 的更新中断
	TIM_Cmd(TIM3, ENABLE); //使能 TIM3外设（即开启TIM3定时器）
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	// 优先级组 说明了抢占优先级所用的位数，
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级 3 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //从优先级 1 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure);//初始化 NVIC 寄存器
}




/***************************************************************************
*使用LED时打开此函数
*LED的IO口配置函数
***************************************************************************/
void LED_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE); //使能 PA,PD 端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO 口速度为 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //根据设定参数初始化 GPIOB.8
	GPIO_SetBits(GPIOA,GPIO_Pin_8); //PA.8=1 输出高,关闭LED0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //LED1-->PD.2 端口配置, 推挽输出
  GPIO_Init(GPIOD, &GPIO_InitStructure); //推挽输出 ， IO 口速度为 50MHz
  GPIO_SetBits(GPIOD,GPIO_Pin_2); //PD.2=1 输出高 ,关闭LED1
}




/***************************************************************************
*使用KEY时打开此函数
*KEY的IO口配置函数
***************************************************************************/
void KEY_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//结构体变量的声明
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//WK_UP-->PA.0 端口配置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO 口速度为 50MHz(作为输入时不用设置速率)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//GPIOA0下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//根据设定参数初始化 GPIOA.0
}





