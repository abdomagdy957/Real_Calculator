


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_
#include "StdTypes.h"

#define		ROWS	4 
#define		COLS	4

#define		NO_KEY_PRESSED	'N'

#define		FIRST_OUTPUT	PINC5		//SUPPOSE ALL output pins located series behind PINC2
#define		FIRST_INPUT		PIND7		//SUPPOSE ALL input pins located series behind PIND3

const u8 KeysArr[ROWS][COLS+1] = {{'7','8','9',' ','/'},
								{'4','5','6',' ','*'},
								{'1','2','3',' ','-'},
								{'C','0','=',' ','+'}};

#endif /* KEYPAD_CFG_H_ */