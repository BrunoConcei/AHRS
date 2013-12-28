#include "UART.h"
#include "stm32f10x.h"

void USART_Config(void) //��������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

//--------------------------------USART2----------------------------------------------
//����2������printf���ض���
//���ռ�������
	/* Configure USART2 Tx (PA2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
   /* Configure USART2 Rx (PA3) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;//| USART_Mode_Rx;
	
	USART_Init(USART2, &USART_InitStructure);
	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);		
}

void USART_IT_Config(void)//�����ж����ã���ѡ
{
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); /*�����ж�ʹ��*/  // |
//////	USART_ITConfig(USART1, USART_IT_TXE,ENABLE);   /*���ͼĴ������ж�ʹ��*/
////	
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   /*3.4�Ŀⲻ��ʹ��USART1_IRQChannel����stm32f10x.h��*/	
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
//	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : int fputc(int ch, FILE *f)
* Description    : Retargets the C library printf function to the USART.printf�ض���
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  /* Write a character to the USART */
  USART_SendData(USART2, (u8) ch);

  /* Loop until the end of transmission */
  while(!(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET))
  {
  }

  return ch;
}

/*******************************************************************************
* Function Name  : int fgetc(FILE *f)
* Description    : Retargets the C library printf function to the USART.fgetc�ض���
* Input          : None
* Output         : None
* Return         : ��ȡ�����ַ�
*******************************************************************************/
int fgetc(FILE *f)
{
  /* Loop until received a char */
  while(!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET))
  {
  }
  
    /* Read a character from the USART and RETURN */
  return (USART_ReceiveData(USART2));
}

//------------------------RTOS layer----------------------------------

