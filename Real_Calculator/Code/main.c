#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"

#include "Calculator.h"

#define  F_CPU	8000000
#include <util/delay.h>

int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	Calculator_Init();


    while(1) 
    {
		Calculator_Operation();
	}
}
