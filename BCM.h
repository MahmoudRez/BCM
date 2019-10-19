/*
 * BCM.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef BCM_H_
#define BCM_H_

#include "STD_Types.h"
typedef enum
{
	HAMADA
}EnmBCMError_t;

typedef struct BSM_Init
{

}BCM_ConfigType;

EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr ) ;
EnmBCMError_t BCM_DeInit ( void ) ;
EnmBCMError_t BCM_RxDispatch(void);
EnmBCMError_t BCM_TxDispatch(void);
EnmBCMError_t BCM_Send(uint8 * COPY_ptrData,uint16 COPY_u16BufferSize);
EnmBCMError_t BCM_Receive(void);
#endif /* BCM_H_ */
