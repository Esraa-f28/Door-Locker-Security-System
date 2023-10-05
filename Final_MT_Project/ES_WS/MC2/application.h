/******************************************************************************
 * File Name: pass.h
 * Author: Esraa Fawzy
 *******************************************************************************/

#ifndef APPLICATION_H_
#define APPLICATION_H_


#include"uart.h"
#include"std_types.h"
#include "external_eeprom.h"
#include "timers.h"
#include"buzzer.h"
#include"twi.h"
#include"dc_motor.h"
#include<util/delay.h>
#include "avr/interrupt.h"


/*******************************************************************************
 *                        		Definitions                                    *
 *******************************************************************************/
#define ENTER_KEY					13		/* 13 is the "ON/C" button on the keypad */
#define Password_Address			0x300 	/* Password Location in the EEPROM */
#define	PasswordIsSetAddress		0x310 	/* Password flag Location in the EEPROM */
#define PasswordSET					0xFF 	/* To indicate whether the password is set or not */
#define MAX_ALLOWED_TRIES			3 		/* allow only 3 tries to enter the password right */

/*******************************************************************************
 *                        		MESSAGE OF UART                               *
 *******************************************************************************/
#define MATCHED				0x01 /* Message From MCU2 to MCU1 to inform it if the passwords match or not */
#define UNMATCHED			0x02 /* Message From MCU2 to MCU1 to inform it if the passwords match or not */
#define READY			    0x03/* Message to indicate if the MCU is ready or not */
#define PASSWORDUPDATE		0x04/* Message From MCU1 to MCU2 to inform it that it will send new password and replace the one you have with it */
#define ALARM			    0x05 /*user enter wrong pass 3 times*/
#define CHECKPASSWORD		0x06 /* Message From MCU1 to MCU2 to inform it that it will send password from keypad to get checked */
#define DOOR		        0x07 /* Message From MCU1 to MCU2 to inform it the user entered the password right, open the door */

/*******************************************************************************
 *                      		Functions Prototypes	             	           *
 *******************************************************************************/

void TIMER_ISR(void);
void PASSWORD_PasswordIsSet(void);

void PASSWORD_storePass(void);
void PASSWORD_checkPass(void);
void Alarm(void);
void Door(void);




#endif /* APPLICATION_H_ */
