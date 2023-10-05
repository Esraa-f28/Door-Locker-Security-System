/******************************************************************************
 * File Name: pass.h
 * Author: Esraa Fawzy
 *******************************************************************************/
#include "application.h"





Timer1_ConfigType timerConfig={0,1000,pre1024,ctc};

uint8 Password1; /* store first password */
uint8 Password2; /* store second password  */
uint8 g_matchedflag=0; /* Flag to indicate if the two passwords match */
uint8 trials = 0; /* max no of trials to enter right password */
uint8 g_ticks = 0; /* Variable to store number of seconds */
uint8 g_keyPressed;


void Password_savePassword(void)
{
	uint8 key2,key;
	LCD_clearScreen();
	do
	{
		g_matchedflag= 0;

		LCD_displayStringRowColumn(0, 0, "Plz Enter pass:");
		LCD_moveCursor(1, 0);
		while(KEYPAD_getPressedKey() != ENTER_KEY){
			for(uint8 i = 0 ; i < 5 ; i++)
			{
				key = KEYPAD_getPressedKey();
				if(key <= 9 && key >= 0)
				{
					Password1=Password1*10+key;
					LCD_displayCharacter('*');
				}
				else
				{
					i--;
				}
				_delay_ms(500);
			}
		}


		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0," Re-Enter pass:");
		LCD_moveCursor(1, 0);
		while(KEYPAD_getPressedKey() != ENTER_KEY){
			for(uint8 i = 0 ; i < 5 ; i++)
			{
				key2 = KEYPAD_getPressedKey();
				if(key2 <= 9 && key2 >= 0)
				{
					Password2=Password2*10+key2;
					LCD_displayCharacter('*');
				}
				else
				{
					i--;

				}
				_delay_ms(500);
			}
		}
		LCD_clearScreen();

		if(Password1 == Password2)
		{
			g_matchedflag= 1;
			LCD_displayStringRowColumn(0, 4, "Matched");
			UART_sendByte(PASSWORDUPDATE);
			UART_sendByte(Password1);
			UART_sendByte((uint8)(Password1>>8));

		}

		else
		{
			LCD_displayStringRowColumn(0, 0, "UnMatched");

		}

		_delay_ms(1000);
		LCD_clearScreen();

	}while(g_matchedflag == 0);
}



uint8 menu(void)
{
	LCD_clearScreen();
	LCD_displayString("+ : OPen Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("- : Change Pass");
	g_keyPressed = KEYPAD_getPressedKey();
	_delay_ms(500);
	//UART_sendByte(g_keyPressed);
	return g_keyPressed;

}


uint8 PASSWORD_checkPass(void)
{

	//trials = 0;
	uint16 passwardtocheck;
	do
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Plz Enter Pass");
		LCD_moveCursor(1, 0);


		for(uint8 i = 0 ; i < 5 ; i++)
		{
			uint8 key = KEYPAD_getPressedKey();
			if(key <= 9 && key >= 0)
			{
				passwardtocheck=passwardtocheck*10+key;
				LCD_displayCharacter('*');
			}
			else
			{
				i--;
			}
			_delay_ms(500);
		}
		//while(KEYPAD_getPressedKey() != ENTER_KEY);

		UART_sendByte(CHECKPASSWORD);

		UART_sendByte((uint8)passwardtocheck);
		UART_sendByte((uint8)(passwardtocheck>>8));


		LCD_clearScreen();
		if(UART_recieveByte() ==  MATCHED)
		{
			LCD_displayStringRowColumn(0, 4, "Matched");
			_delay_ms(500);
			return MATCHED;
		}
		else
		{
			trials++;
			LCD_displayStringRowColumn(0, 2, "UnMatched");
			LCD_displayStringRowColumn(1, 0, "Trials = ");
			LCD_intgerToString(trials);
			_delay_ms(500);
		}
	}while((trials<3));
	return UNMATCHED;
}

void Alarm()
{

	g_ticks = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 4, "ERROR ");
	UART_sendByte(ALARM);
	Timer1_init(&timerConfig);
	Timer1_setCallBack(TIMER_ISR);
	while(g_ticks != 60);
	g_ticks = 0;
	Timer1_deInit();
	LCD_displayStringRowColumn(0, 4, "finished ");
	return;

}


void PASSWORD_changePassword(void)
{
	uint8 PasswordsCompare =PASSWORD_checkPass() ;
	if(PasswordsCompare == MATCHED)
	{
		Password_savePassword();
	}
	if(PasswordsCompare == UNMATCHED)
	{
		Alarm();
	}

}

void Door()
{

	uint8 Passwordtocheck ;
	Passwordtocheck=PASSWORD_checkPass();
	if(Passwordtocheck == MATCHED)
	{

		g_ticks = 0;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "DOOR UNLOCK");
		Timer1_init(&timerConfig);
		Timer1_setCallBack(TIMER_ISR);
		UART_sendByte(DOOR);
		while(g_ticks!=15);
		g_ticks = 0;
		LCD_clearScreen();
		while(g_ticks!=3);
		LCD_displayStringRowColumn(0, 0, "Door Is Locked");
		g_ticks = 0;
		while(g_ticks!=15);
		g_ticks = 0;
		Timer1_deInit();


	}
	else
	{
		Alarm();
	}
}
void TIMER_ISR()
{
	g_ticks++;
}
