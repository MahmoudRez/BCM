/*
 * BCM.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "BCM.h"
#include "UART_Interface.h"



typedef enum State
{
	idle,
	sending_bcm_id,
	sending_no_ofbytes,
	sending_byte,
	sending_cs
}STATE_Status;

typedef struct
{
	uint8 BCM_id;
	uint16 BCM_noOfBytes;
	uint8 * Data;
	uint8 BCM_cs;
}ST_BcmFrame;


BCM_ConfigType * BCM_ptrConfigType;

static volatile BCM_ptrToFunc BCM_ptrConsumerFunc= NULL;
static volatile uint8 g_u8BcmTxStatus=idle;
static volatile uint8 g_u8BcmTxFlag=RESET;
static volatile uint8 g_u8BcmRxFlag=RESET;
static volatile uint8 g_u8BcmTxReqFlag=UNLOCK;
static volatile uint8 g_u8BcmRxReqFlag=UNLOCK;
static volatile ST_BcmFrame g_st_SEND_request;



uint8 g_u8BcmInitFlag=DEINIT;

static void BCM_txCallBack(void)
{
	g_u8BcmTxFlag=SET;
}
static void BCM_rxCallBack(void)
{
	g_u8BcmRxFlag=SET;
}
EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr )
{
	uint8 LOC_u8BcmError;
	if(g_u8BcmInitFlag==DEINIT)
	{

		UART_vidInitialize();
		INTPTx_vidSetCallBack(BCM_txCallBack);
		INTPRx_vidSetCallBack(BCM_rxCallBack);

	}
	else
	{
		LOC_u8BcmError= repeted_init;
	}
	g_u8BcmInitFlag= INIT;
	return LOC_u8BcmError;
}

EnmBCMError_t BCM_DeInit ( void )
{
	uint8 LOC_u8BcmError;

	UART_vidDeInitialize();

	g_u8BcmInitFlag=DEINIT;

	return LOC_u8BcmError;
}
void BCM_RxDispatch(void)
{

}
void BCM_TxDispatch(void)
{
	static uint8 LOC_dataCounter=0;
	switch(g_u8BcmTxStatus)
	{
	case idle:
		if(g_u8BcmTxReqFlag==LOCK)
		{
			UART_vidSendWord(g_st_SEND_request.BCM_id);
			g_u8BcmTxStatus=sending_bcm_id;
		}
		else
		{

		}
		break;

	case sending_bcm_id:
		if(g_u8BcmTxFlag==SET)
		{
			UART_vidSendWord((uint8)g_st_SEND_request.BCM_noOfBytes);
			g_u8BcmTxStatus=sending_no_ofbytes;
			g_u8BcmTxFlag=RESET;
		}
		else
		{

		}

		break;

	case sending_no_ofbytes:
		if(g_u8BcmTxFlag==SET)
		{
			UART_vidSendWord((uint8)(g_st_SEND_request.BCM_noOfBytes>>8));
			g_u8BcmTxStatus=sending_byte;
			g_u8BcmTxFlag=RESET;

		}
		else
		{

		}
		break;
	case sending_byte:
		if(g_u8BcmTxFlag==SET)
		{
			if(g_st_SEND_request.BCM_noOfBytes > LOC_dataCounter  )
			{
				UART_vidSendWord(*(g_st_SEND_request.Data));
				g_st_SEND_request.BCM_cs ^= *(g_st_SEND_request.Data);
				LOC_dataCounter++;
				g_st_SEND_request.Data++;
				g_u8BcmTxFlag=RESET;

			}
			else if(g_st_SEND_request.BCM_noOfBytes==LOC_dataCounter  )
			{
				UART_vidSendWord(g_st_SEND_request.BCM_cs);
				g_u8BcmTxStatus=sending_cs;
				g_u8BcmTxFlag=RESET;
				LOC_dataCounter=RESET;
			}
			else
			{

			}
		}
		else
		{

		}

		break;

	case sending_cs:
		if(g_u8BcmTxFlag==SET)
		{
			g_u8BcmTxFlag=RESET;
			g_u8BcmTxStatus=idle;
			g_u8BcmTxReqFlag=UNLOCK;
			BCM_ptrConsumerFunc();
		}
		else
		{

		}
		/*don't forget to unlock BCM Send request*/

		break;
	}



}
EnmBCMError_t BCM_Send(uint8 * COPY_ptrData,uint16 COPY_u16BufferSize, BCM_ptrToFunc COPY_BCM_ptrConsumerFunc)
{
	uint8 LOC_u8BcmError=OK;
	if(COPY_u16BufferSize==0)
	{
		LOC_u8BcmError=void_size;
	}
	else if(COPY_ptrData==NULL)
	{
		LOC_u8BcmError=invalid_adress;
	}
	else
	{
		if(g_u8BcmTxReqFlag==UNLOCK)
			{
				g_st_SEND_request.BCM_id=BCM_ID;
				g_st_SEND_request.BCM_noOfBytes=COPY_u16BufferSize;
				g_st_SEND_request.Data=COPY_ptrData;
				g_st_SEND_request.BCM_cs=0;
				BCM_ptrConsumerFunc = COPY_BCM_ptrConsumerFunc;
				g_u8BcmTxReqFlag=LOCK;
			}
			else
			{
				LOC_u8BcmError=bcm_busy;
			}
	}



	return LOC_u8BcmError;
}
EnmBCMError_t BCM_Receive(void)
{
	uint8 LOC_u8BcmError;





	return LOC_u8BcmError;
}

