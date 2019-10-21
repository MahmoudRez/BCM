/*
 * BCM.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef BCM_H_
#define BCM_H_
#include "BCM_pbConfig.h"
#include "STD_Types.h"

typedef void (*BCM_ptrToFuncTX)(void);
typedef void (*BCM_ptrToFuncRX)(uint8 * ,uint16 ,uint8 *);

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

extern EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr );
extern EnmBCMError_t BCM_DeInit ( void ) ;
extern void BCM_RxDispatch(void);
extern void BCM_TxDispatch(void);
EnmBCMError_t BCM_Send(uint8 * COPY_ptrData,uint16 COPY_u16BufferSize, BCM_ptrToFuncTX COPY_BCM_ptrConsumerFunc);
extern EnmBCMError_t BCM_SetupRxBuffer(uint8* COPY_ptrRxBuffer,uint16 COPY_u16BufferSize,BCM_ptrToFuncRX COPY_BCM_ptrConsumerFunc);
extern void BCM_vidRxBufferUnlock(void);

#endif /* BCM_H_ */
