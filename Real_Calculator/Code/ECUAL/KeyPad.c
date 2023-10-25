
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"



#define  F_CPU	8000000
#include <util/delay.h>


void KEYPAD_Init(void)
{
	for(u8 r=0; r<ROWS; r++)
	{
		DIO_WritePin(FIRST_OUTPUT-r,HIGH);
	}
}
u8 KEYPAD_GetKey(void)
{
	u8 r,c,key = NO_KEY_PRESSED;
	for(r=0; r<ROWS; r++)
	{
		DIO_WritePin(FIRST_OUTPUT-r,LOW);		//put on pin low to check on shared columns if pressed or not
		for(c=0; c<COLS+1; c++)
		{
			if(c==3)
			{
				continue;
			}
			if(DIO_ReadPin(FIRST_INPUT-c)==LOW)	//check on all columns that pressed or no
			{
				key = KeysArr[r][c];
				_delay_ms(10);			//debouncing problem
				while(DIO_ReadPin(FIRST_INPUT-c)==LOW);		//busy wait
				_delay_ms(10);
			}
		}
		DIO_WritePin(FIRST_OUTPUT-r,HIGH);	//return this pin to high again to check on another pin
	}
	return key;
}