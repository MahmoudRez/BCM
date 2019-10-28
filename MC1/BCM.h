/******************************************************************************
 *
 * Module: Basic Communication Modul (BCM) service layer
 *
 * File Name: BCM.h
 *
 * Description: Header file for BCM Driver
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef BCM_H_
#define BCM_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "BCM_pbConfig.h"
#include "UART_Interface.h"
#include "STD_Types.h"

typedef void (*BCM_ptrToFuncTX)(void);
typedef void (*BCM_ptrToFuncRX)(uint8 * ,uint16 ,uint8 *);


/****************************** EnmBCMstatus_t ********************************/
typedef enum
{
	bcm_ok,
	bcm_nok,
	repeted_init,
	bcm_busy,
	void_size,
	invalid_adress,
	repeted_deinit,
	locked_buffer,

}EnmBCMError_t;


#define INIT 1
#define DEINIT 0
#define SET 1
#define RESET 0
#define  LOCK 1
#define UNLOCK 0
/*****************************BCM ID *********************************/
#define BCM_ID 'X'

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
extern EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr );

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
extern EnmBCMError_t BCM_DeInit ( void ) ;
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
extern void BCM_RxDispatch(void);
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
extern void BCM_TxDispatch(void);

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
extern EnmBCMError_t BCM_Send(uint8 * COPY_ptrData,uint16 COPY_u16BufferSize, BCM_ptrToFuncTX COPY_BCM_ptrConsumerFunc);
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
extern EnmBCMError_t BCM_SetupRxBuffer(uint8* COPY_ptrRxBuffer,uint16 COPY_u16BufferSize,BCM_ptrToFuncRX COPY_BCM_ptrConsumerFunc);
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
extern void BCM_vidRxBufferUnlock(void);

#endif /* BCM_H_ */
