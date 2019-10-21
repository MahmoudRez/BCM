/*
 * APP.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "BCM.h"
#include "REG_Lib.h"
#include "LCD.h"

#include <util/delay.h>

#define ARR_SIZE 16
void Print_Data(uint8 * COPY_ptrBuffer,uint16 COPY_BufferSize,uint8 * COPY_Error);

uint8 LOC_arrTxBuffer[ARR_SIZE]={'M','A','H','M','O','U','D','K','H','A','L','I','L','R','I','Z'};
uint8 LOC_arrTxBuffer2[ARR_SIZE] = {'H','A','M','A','D','A','Y','E','L','3','A','A','A','A','A','B'};
uint8 LOC_arrTxBuffer3[ARR_SIZE] = {'E','M','B','E','D','D','E','D','S','Y','S','T','E','M','S','S'};
uint8 LOC_arrRxBuffer[ARR_SIZE];
void func(void)
{
	BCM_vidRxBufferUnlock();
	BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE,Print_Data);
}

void main (void)
{

	LCD_INIT_4bit();
	LCD_CHAR_DISP(0,0,'H');
	BCM_vidRxBufferUnlock();
	BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE,Print_Data);
	BCM_Init(ST_ptrBcmInitConfigType);
	BCM_Send(LOC_arrTxBuffer,ARR_SIZE,func);

	while(1)
	{
		BCM_TxDispatch();
		BCM_RxDispatch();
	}





}

void Print_Data(uint8 * COPY_ptrBuffer,uint16 COPY_BufferSize,uint8 * COPY_Error)
{
	uint8 static arrNum=0;
	DDRB |= 0x20;
	PORTB |= 0x20;
	LCD_String_DISP(0,0,COPY_ptrBuffer);
	BCM_vidRxBufferUnlock();
	BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE,Print_Data);


	arrNum++;

	if(arrNum == 3)
	{
		arrNum=0;
	}

	LCD_NUM_DISP(1,0,arrNum);
	_delay_us(5000);
	switch(arrNum)
	{
	case 0:
		BCM_Send(LOC_arrTxBuffer,ARR_SIZE,func);
		break;
	case 1:
		BCM_Send(LOC_arrTxBuffer2,ARR_SIZE,func);
		break;
	case 2:
		BCM_Send(LOC_arrTxBuffer3,ARR_SIZE,func);
		break;
	}

}
