/******************************************************************************
 * File Name: mcu2.h
 * Author: Esraa Fawzy
 *******************************************************************************/


#ifndef MCU2_H_
#define MCU2_H_

#define WRONG 1
#define RIGHT 2
#define UNMATCHED 3
#define MATCHED 4
#define OPEN 5
#define CLOSE 6


/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/
#define Password_Address			0x300 	/* Password Location in the EEPROM */
#define	Password_Is_Set_Address		0x304	 /* Password flag Location in the EEPROM */
#define PasswordSET					0xFF	/* To indicate whether the password is set or not */

/*******************************************************************************
*                        		Messages to UART                                 *
*******************************************************************************/
#define Matched					0x01 /* Message From MCU2 to MCU1 to inform it if the passwords match or not */
#define UnMatched				0x02 /* Message From MCU2 to MCU1 to inform it if the passwords match or not */
#define Ready				    0x03/* Message to indicate if the MCU is ready or not */
#define PasswordUpdate			0x04/* Message From MCU1 to MCU2 to inform it that it will send new password and replace the one you have with it */
#define Alarm				    0x05 /*user enter wrong pass 3 times*/
#define checkPassword			0x06 /* Message From MCU1 to MCU2 to inform it that it will send password from keypad to get checked */
#define TurnOnMotor			    0x07 /* Message From MCU1 to MCU2 to inform it the user entered the password right, open the door */


/*******************************************************************************
*                      		Functions Prototypes	             	           *
*******************************************************************************/
void MCU2_passwordIsSet();
void MCU2_passwordupdate();
void MCU2_passwordCheck();
void MCU2_PasswordRead();
void MCU2_alarm();
void MCU2_door();
void TIMER1_motor3SEC_ISR();
void TIMER1_motor15SEC_ISR();
void TIMER1_ALARM_ISR();

#endif /* MCU2_H_ */
