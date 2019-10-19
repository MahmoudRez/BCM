/*
 * APP.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "BCM.h"
#include "REG_Lib.h"

#define ARR_SIZE 7

void func(void)
{
	DDRB = 0x80;
	PORTB |= 0x80;
}

void main (void)
{
	uint8 LOC_arrBuffer[ARR_SIZE]={'M','A','H','M','O','U','D'/*,'K','H','A','L','I','L',\
			                 ' ',' ',' ',' ',' ',' ',' ','K','H','A','L','I','L',\
							 'M','A','H','M','O','U','D',' ',' ',' ',' ',' ','O'*/};
	BCM_Init(ST_ptrBcmInitConfigType);
	BCM_Send(LOC_arrBuffer,ARR_SIZE,func);
	while(1)
	{
		BCM_TxDispatch();
	}





}

