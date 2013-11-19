//��ƽ̨�޹�
//�궨�崫����I2C��ַ���ڲ��Ĵ�����ַ���������ò����Լ�����������
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MXR6202_H_
#define _MXR6202_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "HAL_MXR6202.h"

/**
* @addtogroup MXR6202
* @{
*/

#define MXR_I2C_ADDRESS         		0x20

#define MXR_ONLY_REG_ADDR     			0x00

#define MXR_X_MSB_REG_ADDR				0x01

typedef struct
{
	u8 byte;
}MXR_ConfigTypeDef;

void MXR_I2C_Init(void);	 //��ʼ����Ҫ�õ���I2C
void MXR_I2C_ByteWrite(u8 slAddr, u8* pBuffer, u8 WriteAddr);	//��ָ��������ָ���Ĵ���д�ֽ�
void MXR_I2C_BufferRead(u8 slAddr,u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);		//��ȡ
void MXR_Init(MXR_ConfigTypeDef *MXR_Config_Struct);		  //�������ĳ�ʼ��

u8 MXR_Read_RawData(u16* out);	   //��ȡԭʼ��������
void MXR_Read_Acc(float* out);	   //��ȡ������׼�������ݣ�����λ��ת����ȥ����Ư������������

/**
 * @} 
 */  /* end of group MXR303DLH */

#endif /* __MXR_H */

/******************* (C) COPYRIGHT 2013 Skyworks Embedded System*****END OF FILE****/

