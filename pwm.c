#include "pwm.h"

/*��ʱ��2�Ƚ�����
���ȣ���������ͨ����ָ���ܽű�USART2��TX��RXռ��
��Σ���Ҫ�������һ·��׼�ġ�����Ϊ20ms��PWM���������ƶ��
�ٴΣ���Ҫ���𲶻�����������������*/
void TIM2_Config(void) //PWM��������
{
	u16 CCR1_Val=1000;
	u16 CCR2_Val=1400;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure; 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	//ʹ�ܶ�ʱ��2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//��ʱ��2ͨ��1���ܽ�PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //��ʱ��2ͨ��2���ܽ�PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_BaseInitStructure.TIM_Period = 20000; //20ms       //��ʱ��2��ʱ����   
    TIM_BaseInitStructure.TIM_Prescaler = (uint16_t) (SystemCoreClock / 1000000) - 1; //1us       
    TIM_BaseInitStructure.TIM_ClockDivision = 0;     
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //���ϼ���
    TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure); 

//--------------------------------------ͨ��1��PWM���------------------------------------------
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //��ʱ��2ͨ��1PWM���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //PWM����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;                            //д�Ƚ�ֵ(ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�ø�
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
//--------------------------------------ͨ��2��PWM���------------------------------------------
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //��ʱ��2ͨ��2PWM���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //PWM����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;                            //д�Ƚ�ֵ(ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�ø�
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

//--------------------------------------ͨ��3�����벶��------------------------------------------
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 		   //��ʱ��2ͨ��3���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM2, &TIM_ICInitStructure);

//--------------------------------------ͨ��4�����벶��------------------------------------------
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 		   //��ʱ��2ͨ��4���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	   	
	TIM_ITConfig(TIM2,TIM_IT_CC3 | TIM_IT_CC4, ENABLE); 
  	TIM_Cmd(TIM2, ENABLE); 
}

void TIM2_IT_Config(void)	//��ʱ��2�ж�
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_Config(void)	//PWM���
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	uint16_t CCR1_Val = 1000;
	uint16_t CCR2_Val = 1200;
	uint16_t CCR3_Val = 1000;
	uint16_t CCR4_Val = 1000;
	uint16_t PrescalerValue = 0;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
	TIM_TimeBaseStructure.TIM_Period = 5000;                                  //����
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;              //��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                             //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	                //����ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                    //��ʼTIM3
	
	/*************************** ͨ��1 ********************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //PWM����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;                            //д�Ƚ�ֵ(ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�ø�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/****************************** ͨ��2 ******************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/******************************* ͨ��3 *********************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/****************************** ͨ��4 *********************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                        //
	TIM_Cmd(TIM3, ENABLE);                                          //ʹ�ܼ���
}

void TIM4_Config(void) //PWM��������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure; 
	TIM_ICInitTypeDef  TIM_ICInitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_BaseInitStructure.TIM_Period = 40000; //40ms          
    TIM_BaseInitStructure.TIM_Prescaler = (uint16_t) (SystemCoreClock / 1000000) - 1; //1us       
    TIM_BaseInitStructure.TIM_ClockDivision = 0;     
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure); 

   	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 		   //��ʱ��2ͨ��1���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM4, &TIM_ICInitStructure); 

   	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; 		   //��ʱ��2ͨ��1���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM4, &TIM_ICInitStructure); 

   	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 		   //��ʱ��2ͨ��1���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM4, &TIM_ICInitStructure); 

   	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 		   //��ʱ��2ͨ��1���벶��ģʽ
   	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; 
   	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
   	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
   	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
   	TIM_ICInit(TIM4, &TIM_ICInitStructure); 
   	
	TIM_ITConfig(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE); 
  	TIM_Cmd(TIM4, ENABLE);    
}

void TIM4_IT_Config(void)	//��ʱ��4�ж�
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
