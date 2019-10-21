/*
 * APP.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "BCM.h"
#include "REG_Lib.h"

#define ARR_SIZE 7
EnmBCMError_t Print_Data(uint8 * COPY_ptrBuffer,uint16 COPY_BufferSize,uint8 * COPY_Error);

void func(void)
{
	DDRB = 0x80;
	PORTB |= 0x80;
}

void main (void)
{
	uint8 LOC_arrTxBuffer[ARR_SIZE]={'M','A','H','M','O','U','D'/*,'K','H','A','L','I','L',\
			                 ' ',' ',' ',' ',' ',' ',' ','K','H','A','L','I','L',\
							 'M','A','H','M','O','U','D',' ',' ',' ',' ',' ','O'*/};
	uint8 LOC_arrRxBuffer[ARR_SIZE];
	BCM_Init(ST_ptrBcmInitConfigType);
	BCM_Send(LOC_arrTxBuffer,ARR_SIZE,func);
	BCM_vidRxBufferUnlock();
	BCM_SetupRxBuffer(LOC_arrRxBuffer,ARR_SIZE);
	while(1)
	{
		BCM_TxDispatch();
		BCM_RxDispatch();
	}





}

void Print_Data(uint8 * COPY_ptrBuffer,uint16 COPY_BufferSize,uint8 * COPY_Error)
{

}
