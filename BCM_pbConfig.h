/*
 * BCM_pbConfig.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef BCM_PBCONFIG_H_
#define BCM_PBCONFIG_H_
#include "STD_Types.h"

typedef struct
{
	uint8 u8Com_Id;
}BCM_ConfigType;

extern BCM_ConfigType * ST_ptrBcmInitConfigType;

#endif /* BCM_PBCONFIG_H_ */
