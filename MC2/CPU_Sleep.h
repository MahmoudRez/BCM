/*
 * CPU_Sleep.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef CPU_SLEEP_H_
#define CPU_SLEEP_H_
/*******************************************************************************
 *                      Preprocessor Macros for Sleep Register                                  *
 *******************************************************************************/
#define MCUCR (*(( volatile uint8*)0x55))
#define CPU_SM0 4
#define CPU_SM1 5
#define CPU_SM2 6
#define CPU_SE 7
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define CPU_SLEEP_MODE IDLE
#define IDLE 0
#define ADC_NOISE_REDUCTION 1
#define POWER_DOWN 2
#define POWER_SAVE 3
#define STANDBY 6
#define EXTENDED_STANDBY 7

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
extern void CPU_Sleep(void);

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
extern void CPU_SleepEnable(void);

/*******************************************************************************
 * Function Name:	CPU_SleepDisable
 *
 * Description: 	Enable Selected CPU Sleeping Mood
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
extern void CPU_SleepDisable(void);



#endif /* CPU_SLEEP_H_ */
