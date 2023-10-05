/******************************************************************************
 * File Name: pass.h
 * Author: Esraa Fawzy
 *******************************************************************************/
#include "application.h"


uint8 DataRec;

int main(void)
{
	Buzzer_init();
	UART_ConfigType uartConfig={ BITS_8,NO_PARITY,BIT_1,BAUD_RATE_9600};
	UART_init(&uartConfig);
	TWI_ConfigType twiConfig={0x01,400};
	TWI_init(&twiConfig);
	DcMotor_init();
	sei();
	//while( UART_recieveByte() != READY);
	UART_sendByte(READY);

	PASSWORD_PasswordIsSet();

	while(1)
	{
		DataRec= UART_recieveByte();
		switch(DataRec){
		case ALARM:
			Alarm();
			break;
		case DOOR:
			Door();
			break;
		case CHECKPASSWORD:
			PASSWORD_checkPass();
			break;
		case PASSWORDUPDATE:
			PASSWORD_storePass();
			break;
		}
	}


}

