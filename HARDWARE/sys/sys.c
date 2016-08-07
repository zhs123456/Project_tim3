#include "sys.h"




/***************************************************************************
*ʹ��TIM3ʱ�򿪴˺���
*TIM3�ĳ�ʼ������
***************************************************************************/
#define arr3 1999//���������Զ���װֵ���������Զ���װֵΪarr3+1��
#define psc3 7199//��Ƶϵ���������ķ�Ƶϵ��Ϊpsc3+1��
void TIM3_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//��ʼ���ж����ȼ�����Ľṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//��ʼ����ʱ�������Ľṹ�������ʼ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3��ʱ��ʱ��
	
	TIM_DeInit(TIM3);//��TIM3����ΪĬ��ȱʡֵ
	  
	TIM_TimeBaseStructure.TIM_Period = arr3;//�����Զ���װ�ؼĴ�����ֵ����֤ÿ�θ����жϼ��Ϊ200ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc3;//����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//��Ƶ1ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//�������õĲ�����ʼ����ʱ��
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);			 //ע�⣺TIM_TimeBaseInit����������һ��UG�¼�����˺�����жϱ�־λһ��Ҫ�����
	 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//ʹ�� TIM3 �ĸ����ж�
	TIM_Cmd(TIM3, ENABLE); //ʹ�� TIM3���裨������TIM3��ʱ����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	// ���ȼ��� ˵������ռ���ȼ����õ�λ����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ� 3 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ� 1 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ�� NVIC �Ĵ���
}




/***************************************************************************
*ʹ��LEDʱ�򿪴˺���
*LED��IO�����ú���
***************************************************************************/
void LED_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE); //ʹ�� PA,PD �˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ���ٶ�Ϊ 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�����趨������ʼ�� GPIOB.8
	GPIO_SetBits(GPIOA,GPIO_Pin_8); //PA.8=1 �����,�ر�LED0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //LED1-->PD.2 �˿�����, �������
  GPIO_Init(GPIOD, &GPIO_InitStructure); //������� �� IO ���ٶ�Ϊ 50MHz
  GPIO_SetBits(GPIOD,GPIO_Pin_2); //PD.2=1 ����� ,�ر�LED1
}




/***************************************************************************
*ʹ��KEYʱ�򿪴˺���
*KEY��IO�����ú���
***************************************************************************/
void KEY_Confrigration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//�ṹ�����������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//WK_UP-->PA.0 �˿�����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO ���ٶ�Ϊ 50MHz(��Ϊ����ʱ������������)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//GPIOA0��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);//�����趨������ʼ�� GPIOA.0
}





