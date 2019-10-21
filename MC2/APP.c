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


uint8 LOC_arrTxBuffer[ARR_SIZE] = {'M','O','S','T','A','F','A','K','H','A','L','I','L','R','I','Z'};
uint8 LOC_arrTxBuffer2[ARR_SIZE] = {'H','A','M','M','O','O','B','E','E','E','K','A','A','A','A','A'};
uint8 LOC_arrTxBuffer3[ARR_SIZE] = {'A','D','E','L','S','H','A','K','A','L','Z','A','3','A','M','A'};
uint8 LOC_arrRxBuffer[ARR_SIZE];
void func(void)
{
DDRB |= 0x80;
PORTB |= 0x80;
BCM_vidRxBufferUnlock();
BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE,Print_Data);
}

void main (void)
{
	uint8 arrNum=0;

	LCD_INIT_4bit();
	LCD_CHAR_DISP(0,0,'H');


	BCM_Init(ST_ptrBcmInitConfigType);
	DDRB |= 0x40;
	PORTB |= 0x40;
	BCM_vidRxBufferUnlock();
	BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE,Print_Data);
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


	_delay_us(5000);
	LCD_NUM_DISP(1,0,arrNum);
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

	arrNum++;
	if(arrNum == 3)
	{
		arrNum=0;
	}

}
