/*
 * CPU_Sleep.c
 * Module: CPU sleeping mood
 *
 * File Name: CPU_sleep.c
 *
 * Description: Source file for CPU sleep Driver
 *  Created on: Oct 22, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "CPU_Sleep.h"
#include "STD_Types.h"
#include "Utilize.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	CPU_Sleep
 *
 * Description: 	Select CPU Sleeping Mood
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void CPU_Sleep(void)
{
#if(IDLE==CPU_SLEEP_MODE)
	/*select idle mode*/
	CLR_BIT(MCUCR,CPU_SM0);
	CLR_BIT(MCUCR,CPU_SM1);
	CLR_BIT(MCUCR,CPU_SM2);

	/*select Adc noise reduction mode*/

#elif(ADC_NOISE_REDUCTION==CPU_SLEEP_MODE)
	SET_BIT(MCUCR,CPU_SM0);
	CLR_BIT(MCUCR,CPU_SM1);
	CLR_BIT(MCUCR,CPU_SM2);

	/*select Power down mode*/

#elif (POWER_DOWN==CPU_SLEEP_MODE)
	CLR_BIT(MCUCR,CPU_SM0);
	SET_BIT(MCUCR,CPU_SM1);
	CLR_BIT(MCUCR,CPU_SM2);

	/*select Power save mode*/

#elif(POWER_SAVE==CPU_SLEEP_MODE)
	SET_BIT(MCUCR,CPU_SM0);
	SET_BIT(MCUCR,CPU_SM1);
	CLR_BIT(MCUCR,CPU_SM2);

	/*select Standby mode*/

#elif (STANDBY==CPU_SLEEP_MODE)
	CLR_BIT(MCUCR,CPU_SM0);
	SET_BIT(MCUCR,CPU_SM1);
	SET_BIT(MCUCR,CPU_SM2);

	/*select Extended standby mode*/

#elif (EXTENDED_STANDBY==CPU_SLEEP_MODE)
	SET_BIT(MCUCR,CPU_SM0);
	SET_BIT(MCUCR,CPU_SM1);
	SET_BIT(MCUCR,CPU_SM2);
#endif

}



/*******************************************************************************
 * Function Name:	CPU_SleepEnable
 *
 * Description: 	Enable Selected CPU Sleeping Mood
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void CPU_SleepEnable(void)
{
	/*set sleep enable bit*/
	SET_BIT(MCUCR,CPU_SE);
}

/*******************************************************************************
 * Function Name:	CPU_SleepDisable
 *
 * Description: 	Disable Selected CPU Sleeping Mood
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void CPU_SleepDisable(void)
{
	/*clear sleep enable bit*/
	CLR_BIT(MCUCR,CPU_SE);
}


