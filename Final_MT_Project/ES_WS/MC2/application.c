/******************************************************************************
 * File Name: pass.h
 * Author: Esraa Fawzy
 *******************************************************************************/
#include "application.h"




Timer1_ConfigType timerConfig={0,1000,pre1024,ctc};

uint8 Password1; /* store first password */
uint8 Password2; /* store second password  */
uint8 g_matchedflag; /* Flag to indicate if the two passwords match */
uint8 trials = MAX_ALLOWED_TRIES; /* max no of trials to enter right password */
uint8 g_ticks = 0; /* Variable to store number of seconds */
uint8 StateOfPassword;


void TIMERR_ISR(void)
{
	(g_ticks)++;
}

void PASSWORD_PasswordIsSet()
{
	EEPROM_readByte(PasswordIsSetAddress, &StateOfPassword);
	UART_sendByte(StateOfPassword);
}

void PASSWORD_storePass(void)
{
	uint8 pass11, pass12;


	pass11 = UART_recieveByte();
	pass12 = UART_recieveByte();

	EEPROM_writeByte( Password_Address, pass11);
	_delay_ms(50);

	EEPROM_writeByte( Password_Address+1, pass12);
	_delay_ms(50);

	EEPROM_writeByte( PasswordIsSetAddress, PasswordSET);
	_delay_ms(50);

}

void PASSWORD_checkPass(void)
{
	uint8 pass1, pass2 , repass1,repass2 ;

	//while(UART_recieveByte()==CHECKPASSWORD);
	repass1 = UART_recieveByte();
	repass2 = UART_recieveByte();
	EEPROM_readByte(Password_Address, &pass1);
	EEPROM_readByte(Password_Address+1, &pass2);
	if(( repass1!= pass1) && (repass2 !=pass2))
	{
		UART_sendByte(UNMATCHED);

	}
	else
	{
		UART_sendByte(MATCHED);
	}
}


void Door(void)
{
	g_ticks = 0;
	//while(UART_recieveByte()==DOOR);
	Timer1_init(&timerConfig);
	Timer1_setCallBack(TIMERR_ISR);
	DcMotor_Rotate(CLOCKWISE, 100);
	while(g_ticks != 15);
	g_ticks = 0;
	DcMotor_Rotate(	STOP,0);
	while(g_ticks != 3);
	g_ticks = 0;
	DcMotor_Rotate(ANTI_CLOCKWISE, 100);
	while(g_ticks != 15);
	g_ticks = 0;
	DcMotor_Rotate(STOP, 0);
	Timer1_deInit();
	return ;
}
void Alarm(void)
{
	g_ticks = 0;
	//while(UART_recieveByte()==ALARM);
	Timer1_init(&timerConfig);
	Timer1_setCallBack(TIMERR_ISR);
	Buzzer_on();
	while(g_ticks != 60);
	Buzzer_off();
	g_ticks = 0;
	Timer1_deInit();


	return;
}
