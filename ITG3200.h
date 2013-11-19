//��ƽ̨�޹�
//�궨�崫����I2C��ַ���ڲ��Ĵ�����ַ���������ò����Լ�����������
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ITG3200_H_
#define _ITG3200_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "HAL_ITG3200.h"

/**
* @addtogroup ITG3200
* @{
*/

#define ITG_Internal_Clk_Sel                   	((u8)0x00)
#define ITG_SMPLRT_DIV                      	((u8)0x07) //0~255
#define ITG_Full_Scale_2000                   	((u8)0x18)
#define ITG_LPFilter_Bandwidth_256Hz            ((u8)0x00)
#define ITG_LPFilter_Bandwidth_188Hz            ((u8)0x01)
#define ITG_LPFilter_Bandwidth_98Hz            	((u8)0x02)
#define ITG_LPFilter_Bandwidth_42Hz            	((u8)0x03)
#define ITG_LPFilter_Bandwidth_20Hz            	((u8)0x04)
#define ITG_LPFilter_Bandwidth_10Hz            	((u8)0x05)
#define ITG_LPFilter_Bandwidth_5Hz            	((u8)0x06)
#define ITG_Int_Mode               				((u8)0xA5)

#define ITG_I2C_ADDRESS         		0xD0

#define ITG_I2C_REG_PID					0x00	//always 0x68 or 0x69

#define ITG_POWERMANAGE_REG_ADDR     	0x3E

#define ITG_SR_DIVIDER_REG_ADDR     	0x15

#define ITG_FULL_SCALE_REG_ADDR     	0x16

#define ITG_INT_CONFIG_ADDR     		0x17
//----------------------------------------------------
#define ITG_INT_STATUS_REG_ADDR     	0x1A

#define ITG_TEMP_OUT_H_REG_ADDR  		0x1B

#define ITG_TEMP_OUT_L_REG_ADDR     	0x1C

#define ITG_XOUT_H_ADDR     			0x1D

#define ITG_XOUT_L_ADDR     			0x1E

#define ITG_YOUT_H_ADDR     			0x1F

#define ITG_YOUT_L_ADDR     			0x20

#define ITG_ZOUT_H_ADDR     			0x21

#define ITG_ZOUT_L_ADDR     			0x22

typedef struct
{
  u8 ClkSel; 
  u8 SamRate; /*!< sample Rate */
  u8 FS;     /*!< Full Scale */
  u8 LPFBandwidth;  
  u8 IntMode;   
}ITG_ConfigTypeDef;

void ITG_I2C_Init(void);	 //��ʼ����Ҫ�õ���I2C
void ITG_I2C_ByteWrite(u8 slAddr, u8* pBuffer, u8 WriteAddr);	//��ָ��������ָ���Ĵ���д�ֽ�
void ITG_I2C_BufferRead(u8 slAddr,u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);		//��ȡ
void ITG_Init(ITG_ConfigTypeDef *ITG_Config_Struct);		  //�������ĳ�ʼ��

u8 ITG_Read_RawData(s16* out);	   //��ȡԭʼ��������
void ITG_Read_GyroRate(float* out);	   //��ȡ������׼�������ݣ�����λ��ת����ȥ����Ư������������
void ITG_Raw2Gyro(u8 *raw, float *gyr);

void ITG3205_Config(void);
/**
 * @} 
 */  /* end of group ITG303DLH */

#endif /* __ITG_H */

/******************* (C) COPYRIGHT 2010 Skyworks*****************/
/*****END OF FILE****/

