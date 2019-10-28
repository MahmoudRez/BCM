/******************************************************************************
 *
 * Module: Basic Communication Module (BCM) service layer
 *
 * File Name: BCM.c
 *
 * Description: Source file for BCM Driver
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "BCM.h"
#include "REG_Lib.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/************************ EnmBCM_TxDispatch_t **********************************/
typedef enum
{
	Txidle,
	sending_bcm_id,
	sending_no_ofbytes,
	sending_byte,
	sending_cs
}STATE_TxStatus;

/************************ EnmBCM_RxDispatch_t **********************************/


typedef enum
{
	Rxidle,
	receiving_id,
	receiving_numberofbytes,
	receiving_data,
	recieving_cs,
	frame_complete,
	frame_error
}STATE_RxStatus;

typedef struct
{
	uint8 BCM_id;
	uint16 BCM_noOfBytes;
	uint8 * Data;
	uint8 BCM_cs;
}ST_BcmFrame;

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/


ST_BcmFrame g_St_BCM_RxrequestFrame;

BCM_ConfigType * BCM_ptrConfigType;

static volatile BCM_ptrToFuncTX BCM_ptrConsumerFuncTX= NULL;
static volatile BCM_ptrToFuncRX BCM_ptrConsumerFuncRX= NULL;
static volatile STATE_TxStatus g_u8BcmTxStatus=Txidle;
static volatile STATE_RxStatus g_u8BcmRxStatus=Rxidle;
static volatile uint8 g_u8BcmTxFlag=RESET;
static volatile uint8 g_u8BcmTxReqFlag=UNLOCK;
static volatile uint8 g_u8BcmRxReqFlag=LOCK;
static volatile ST_BcmFrame g_st_SEND_request;
static volatile uint8 g_u8BcmInitFlag=DEINIT;


/*******************************************************************************
 * Function Name:	BCM_txCallBack
 *
 * Description: 	static Callback function from UART_Tx interrupt to continue
 * 					sending of data
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
static void BCM_txCallBack(void)
{
	g_u8BcmTxFlag=SET;
}
/*******************************************************************************
 * Function Name:	BCM_rxCallBack
 *
 * Description: 	static Callback function from UART_Rx interrupt to continue
 * 					receiving of data
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
static void BCM_rxCallBack(void)
{
	static volatile uint16 LOC_Counter=0;
	uint8 LOC_RxData;
	UART_vidReceiveWord(&LOC_RxData);
	if(LOCK==g_u8BcmRxReqFlag)
	{

	}
	else if (UNLOCK==g_u8BcmRxReqFlag)
	{
		switch(g_u8BcmRxStatus)
		{
		case Rxidle:
			LOC_Counter=0;
			if(LOC_RxData==g_St_BCM_RxrequestFrame.BCM_id)
			{
				g_u8BcmRxStatus=receiving_id;
			}
			break;
		case receiving_id:
			g_St_BCM_RxrequestFrame.BCM_noOfBytes|=(uint16)LOC_RxData;
			g_u8BcmRxStatus=receiving_numberofbytes;
/*			LCD_NUM_DISP(1,8,g_St_BCM_RxrequestFrame.BCM_noOfBytes);*/
			break;
		case receiving_numberofbytes:
			g_St_BCM_RxrequestFrame.BCM_noOfBytes|=(((uint16)LOC_RxData)<<8);
			g_u8BcmRxStatus=receiving_data;
/*			LCD_NUM_DISP(1,10,g_St_BCM_RxrequestFrame.BCM_noOfBytes);*/
			break;
		case receiving_data:
			if(LOC_Counter < g_St_BCM_RxrequestFrame.BCM_noOfBytes)
			{
				*(g_St_BCM_RxrequestFrame.Data)=LOC_RxData;
				g_St_BCM_RxrequestFrame.BCM_cs^=LOC_RxData;
				g_St_BCM_RxrequestFrame.Data++;
				LOC_Counter++;
			}
			if(LOC_Counter == (g_St_BCM_RxrequestFrame.BCM_noOfBytes))
			{
				DDRB |= 0x10;
				PORTB |= 0x10;
				g_u8BcmRxStatus=recieving_cs;
			}
			else
			{

			}
			break;
		case recieving_cs:
			DDRB |= 0x20;
			PORTB |= 0x20;
			if(g_St_BCM_RxrequestFrame.BCM_cs==LOC_RxData)
			{
				DDRB |= 0x40;
				PORTB |= 0x40;
				g_u8BcmRxStatus=frame_complete;
			}
			else
			{
				g_u8BcmRxStatus=frame_error;
			}
			break;
		default:
			break;
		}

	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	BCM_Init
 *
 * Description: 	Initialize the BCM Driver
 *
 * Inputs:			Pointer to configuration structure
 *
 * Outputs:			NULL
 *
 * Return:			Status to check function execution
 *******************************************************************************/
EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr )
{
	EnmBCMError_t LOC_u8BcmError=bcm_ok;
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
/*******************************************************************************
 * Function Name:	BCM_DeInit
 *
 * Description: 	Disable the BCM Driver
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			Status to check function execution
 *******************************************************************************/
EnmBCMError_t BCM_DeInit ( void )
{
	EnmBCMError_t LOC_u8BcmError=bcm_ok;
	if(g_u8BcmInitFlag==INIT)
	{
		UART_vidDeInitialize();
		g_u8BcmInitFlag=DEINIT;
	}
	else if (g_u8BcmInitFlag==DEINIT)
	{
		LOC_u8BcmError=repeted_deinit;
	}
	else
	{
		LOC_u8BcmError=bcm_nok;
	}


	return LOC_u8BcmError;
}
/*******************************************************************************
 * Function Name:	BCM_TxDispatch
 *
 * Description: 	Check status for sending communication in BCM
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/

void BCM_TxDispatch(void)
{

	static uint8 LOC_dataCounter=0;
	switch(g_u8BcmTxStatus)
	{
	case Txidle:
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
			g_u8BcmTxStatus=Txidle;
			g_u8BcmTxReqFlag=UNLOCK;
			BCM_ptrConsumerFuncTX();
		}
		else
		{

		}
		/*don't forget to unlock BCM Send request*/

		break;
	}



}
/*******************************************************************************
 * Function Name:	BCM_Send
 *
 * Description: 	start the sending communication
 *
 * Inputs:			pointer to array	(uint8)
 * 					uint16 size of Data array
 * 					pointer to consumer function
 *
 * Outputs:			NULL
 *
 * Return:			Status to check function execution
 *******************************************************************************/
EnmBCMError_t BCM_Send(uint8 * COPY_ptrData,uint16 COPY_u16BufferSize, BCM_ptrToFuncTX COPY_BCM_ptrConsumerFunc)
{
	EnmBCMError_t LOC_u8BcmError=bcm_ok;
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
			BCM_ptrConsumerFuncTX = COPY_BCM_ptrConsumerFunc;
			g_u8BcmTxReqFlag=LOCK;
		}
		else
		{
			LOC_u8BcmError=bcm_busy;
		}
	}



	return LOC_u8BcmError;
}
/*******************************************************************************
 * Function Name:	BCM_RxDispatch
 *
 * Description: 	Check status for receiving communication in BCM
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void BCM_RxDispatch(void)
{
	LCD_NUM_DISP(1,3,g_u8BcmRxReqFlag);
	if(g_u8BcmRxStatus==frame_complete)
	{

		g_u8BcmRxReqFlag=LOCK;
		g_u8BcmRxStatus=Rxidle;
		g_St_BCM_RxrequestFrame.Data -=  g_St_BCM_RxrequestFrame.BCM_noOfBytes;
		BCM_ptrConsumerFuncRX(g_St_BCM_RxrequestFrame.Data,g_St_BCM_RxrequestFrame.BCM_noOfBytes,&g_u8BcmRxStatus);

	}
	else if(g_u8BcmRxStatus==frame_error)
	{
		g_u8BcmRxStatus=Rxidle;
	}

}
/*******************************************************************************
 * Function Name:	BCM_SetupRxBuffer
 *
 * Description: 	Start the receiving communication
 *
 * Inputs:			 array size 	(uint16)
 * 					pointer to consumer function
 *
 * Outputs:			pointer to array 		(uint8)
 *
 *
 * Return:			Status to check function execution
 *******************************************************************************/
EnmBCMError_t BCM_SetupRxBuffer(uint8* COPY_ptrRxBuffer,uint16 COPY_u16BufferSize,BCM_ptrToFuncRX COPY_BCM_ptrConsumerFunc)
{
	EnmBCMError_t LOC_u8BcmError=bcm_ok;
	if(NULL==COPY_ptrRxBuffer)
	{
		LOC_u8BcmError=invalid_adress;
	}
	else if (0==COPY_u16BufferSize)
	{
		LOC_u8BcmError=void_size;
	}
	else if(LOCK==g_u8BcmRxReqFlag)
	{
		LOC_u8BcmError=locked_buffer;
	}
	else if(NULL == COPY_BCM_ptrConsumerFunc)
	{
		LOC_u8BcmError=invalid_adress;
	}
	else
	{
		g_St_BCM_RxrequestFrame.BCM_id=BCM_ID;
		g_St_BCM_RxrequestFrame.BCM_noOfBytes=0;
		g_St_BCM_RxrequestFrame.Data=COPY_ptrRxBuffer;
		g_St_BCM_RxrequestFrame.BCM_cs=0;
		BCM_ptrConsumerFuncRX = COPY_BCM_ptrConsumerFunc;
	}
	return LOC_u8BcmError;
}
/*******************************************************************************
 * Function Name:	BCM_vidRxBufferUnlock
 *
 * Description: 	Unlock the receiving buffer to allow another
 * 					another receive request
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 *
 * Return:			NULL
 *******************************************************************************/
void BCM_vidRxBufferUnlock(void)
{
	g_u8BcmRxReqFlag=UNLOCK;
}
