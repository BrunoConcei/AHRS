#include "flashTask.h"
#include "AHRS.h"

volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

void vFlashTask(void* pvParameters)
{
	portBASE_TYPE xstatus;
	AccCaliType act;
	u32 buffer[15];
	u8 i;
	for(i=0;i<15;i++)
	{
		buffer[i]=*((u32 *)OperationFlashAddr+i);
	}

	//�����Ѵ����Ϣ
	act=*(AccCaliType *)buffer;
	xQueueSend(xAccCaliQueue,&act,portMAX_DELAY);
	//make sure that data has been read
	xstatus = xQueuePeek(xAccCaliQueue,&act,0);
	while(xstatus == pdPASS)
	{
		vTaskDelay((portTickType)10/portTICK_RATE_MS);
		xstatus = xQueuePeek(xAccCaliQueue,&act,0);
	}

	for(;;)
	{
		//������Ϣ
		xQueueReceive(xAccCaliQueue, &act, portMAX_DELAY);
		*(AccCaliType *)buffer = act;
		//����
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		//����
		FLASHStatus=FLASH_ErasePage(OperationFlashAddr);
		vTaskDelay((portTickType)5/portTICK_RATE_MS);
		//д��
		for(i=0;i<15;i++)
			FLASHStatus=FLASH_ProgramWord(OperationFlashAddr+i*sizeof(u32),buffer[i]);
		//����
		FLASH_Lock();
		vTaskDelay((portTickType)50/portTICK_RATE_MS);
	}
}

