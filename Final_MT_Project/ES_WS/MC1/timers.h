/******************************************************************************
 * Module: Timers
 * File Name: timers.h
 * Description: Source file for the ATmega32 Timer driver
 * Author: Esraa Fawzy
 *******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

#include"std_types.h"
#define TIMER_NUMBER 0

typedef enum
{
	stopped,noPre,pre8,pre64,pre256,pre1024,externalclk_falling,externalclk_rising
}Timer1_Prescaler;

typedef enum
{
	normal,ctc
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMERS_H_ */
