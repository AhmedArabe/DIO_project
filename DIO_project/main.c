/*
 * main.c
 *
 *  Created on: Oct 27, 2021
 *      Author: ahmed17039
 */


#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/KPD/KPD_Interface.h"
#include "avr/delay.h"

void main(void)
{
	u8 Local_u8Key=0;
	u8 Password=0;
	u8 Flag_led=0;
	u8 Flag_Motor=0;
	u8 Flag_star=0;
	HLCD_VoidInit();
	DIO_u8SetPinDirection(DIO_u8_PORTD,DIO_u8_PIN5,DIO_u8_PIN_OUTPUT);

	DIO_u8SetPinDirection(DIO_u8_PORTD,DIO_u8_PIN6,DIO_u8_PIN_OUTPUT);
	HLCD_VoidSendString("Welcome Back");
	_delay_ms(1000);
	HLCD_VoidSendCommand(DISPLAYCLEAR);

	HLCD_VoidSendString("Enter Password");
	_delay_ms(1000);
	HLCD_VoidSendCommand(DISPLAYCLEAR);




	while(Local_u8Key !='=')
	{
		Password= Password*10+Local_u8Key;
		if(Flag_star!=0)
		{
		HLCD_VoidSendChar('*');
		}
		do
		{
			Local_u8Key=KPD_u8GetPressedKey();
			Flag_star=1;
		}while(Local_u8Key==KPD_NO_PRESSED_KEY );

	}
	if(Password == 123)
	{
		HLCD_VoidSendCommand(DISPLAYCLEAR);
		HLCD_VoidSendString("Welcome Ahmed ");
		_delay_ms(1000);
		while(1)
		{
		HLCD_VoidSendCommand(DISPLAYCLEAR);

			if(Flag_led ==0)
			{

				HLCD_VoidSendString("1-Turn on Led");
			}
			else if( Flag_led ==1)
			{
				HLCD_VoidSendString("1-Turn off Led");

			}
			HLCD_VoidGotoXY(1,0);
			if(Flag_Motor ==0)
			{

				HLCD_VoidSendString("2-Turn on motor");
			}
			else
			{

				HLCD_VoidSendString("2-Turn off motor");
			}
			do
			{
				Local_u8Key=KPD_u8GetPressedKey();

			}while(Local_u8Key==KPD_NO_PRESSED_KEY );

			if(Local_u8Key ==1)
			{
				switch (Flag_led)
				{
				case 0 : DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN5,DIO_u8_PIN_HIGH); Flag_led =1; break;
				case 1 : DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN5,DIO_u8_PIN_LOW); Flag_led =0; break;
				}
			}
			else if(Local_u8Key ==2)
			{
				switch (Flag_Motor)
				{
				case 0 : DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN6,DIO_u8_PIN_HIGH); Flag_Motor =1; break;
				case 1 : DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN6,DIO_u8_PIN_LOW);  Flag_Motor =0; break;
				}
			}

		}
	}
	else
	{
		HLCD_VoidSendCommand(DISPLAYCLEAR);
		HLCD_VoidSendString("Wrong password");

	}




}
