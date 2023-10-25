#include "StdTypes.h"
#include "DIO.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"

#include "Calculator.h"
#include "Calculator_Cfg.h"

#define  F_CPU	8000000
#include <util/delay.h>
#define		NO_KEY_PRESSED	'N'

u8 sizeOfNumbers=0, sizeOfOperations = 0, operationsPriorityCheck=0;
s32 result=0;
u16 last_pressed = NULL;
s16 numArr[MAX_ARR_SIZE] = {0};
u8	operationArr[MAX_ARR_SIZE-1] = {0};

void Calculator_Init(void)
{
	LCD_Clear();
	LCD_WriteString_GoTo(0,4,"Welcome..!");
	LCD_GoTo(2,0);
}
void Calculator_Operation(void)
{
	u8 key = KEYPAD_GetKey();
	if(key!= NO_KEY_PRESSED)
	{
		switch(key)
		{
			case 'C':
			Calculator_Reset();
			break;
			
			case '*':
			if(last_pressed != NULL || last_pressed != '+' || last_pressed != '-' || last_pressed != '/')
			{
				operationArr[sizeOfOperations] = '*';
				LCD_WriteChar(key);
				sizeOfOperations++;
				sizeOfNumbers++;
				operationsPriorityCheck++;
				_delay_ms(30);
			}
			break;
			
			case '/':
			if(last_pressed != NULL || last_pressed != '+' || last_pressed != '-' || last_pressed != '*')
			{
				operationArr[sizeOfOperations] = '/';
				LCD_WriteChar(key);
				sizeOfOperations++;
				sizeOfNumbers++;
				operationsPriorityCheck++;
				_delay_ms(30);
			}
			break;
			
			case '+':
			if(last_pressed != NULL || last_pressed != '*' || last_pressed != '-' || last_pressed != '/')
			{
				operationArr[sizeOfOperations] = '+';
				LCD_WriteChar(key);
				sizeOfOperations++;
				sizeOfNumbers++;
				_delay_ms(30);
			}
			break;
			
			case '-':
			if(last_pressed != NULL || last_pressed != '*' || last_pressed != '+' || last_pressed != '/')
			{
				operationArr[sizeOfOperations] = '-';
				LCD_WriteChar(key);
				sizeOfOperations++;
				sizeOfNumbers++;
				_delay_ms(30);
			}
			break;
			case '=':
			Calculator_Running();
			break;
			
			default:
			if(numArr[sizeOfNumbers]==0)
			{
				/*this is the first input user can enter or any number after any operation */
				numArr[sizeOfNumbers] += (key-'0');
			}
			else
			{
				/*this is for any number has more than 1 digit*/
				numArr[sizeOfNumbers] = numArr[sizeOfNumbers]*10 + (key-'0');
			}
			LCD_WriteChar(key);
			_delay_ms(30);
			break;
		}
		last_pressed = key;
	}
}
void Calculator_Running()
{
	u8 index=0;
	if(sizeOfNumbers!=0 && sizeOfOperations!=0)
	{
		while(operationsPriorityCheck!=0)
		{
			for(index=0;index<sizeOfOperations;index++)
			{
				u8 IndexPrevNum=0, IndexNextNum=1;
				if(operationArr[index] == '*' || operationArr[index] == '/')
				{
					while(numArr[index-IndexPrevNum] == 'R')
					{
						IndexPrevNum++;
					}
					while(numArr[index+IndexNextNum] == 'R')
					{
						IndexNextNum++;
					}
					if(operationArr[index] == '*')
					{
						numArr[index] = numArr[index-IndexPrevNum]*numArr[index+IndexNextNum];
					}
					else
					{
						/*so, divison*/
						numArr[index] = numArr[index-IndexPrevNum]/numArr[index+IndexNextNum];
					}
					numArr[index+1] = 'R';
					if(IndexPrevNum !=0)
					{
						numArr[index - IndexPrevNum] = 'R';
					}
					operationArr[index]=0;
				}
			}
			operationsPriorityCheck--;
		}
		for(index=0;index<sizeOfOperations;index++)
		{
			u8 IndexPrevNum=0, IndexNextNum=1;
			if(operationArr[index] == '+' || operationArr[index] == '-')
			{
				while(numArr[index-IndexPrevNum] == 'R')
				{
					IndexPrevNum++;
				}
				while(numArr[index+IndexNextNum] == 'R')
				{
					IndexNextNum++;
				}
				if(operationArr[index] == '+')
				{
					numArr[index] = numArr[index-IndexPrevNum] + numArr[index+IndexNextNum];
				}
				else
				{
					/*so, subtraction*/
					numArr[index] = numArr[index-IndexPrevNum] - numArr[index+IndexNextNum];
				}
				numArr[index+1] = 'R';
				if(IndexPrevNum !=0)
				{
					numArr[index - IndexPrevNum] = 'R';
				}
				operationArr[index]=0;
			}
		}
		for(u8 index=0; index<sizeOfNumbers;index++)
		{
			if(numArr[index] != 'R')
			{
				result = numArr[index];
				break;
			}
		}
		//LCD_Clear();
		LCD_GoTo(3,0);
		LCD_WriteString("result = ");
		LCD_WriteNumber_2(result);
		LCD_GoTo(2,0);
		_delay_ms(100);
	}
}
void Calculator_Reset(void)
{
	for(u8 indexOfArray_Num=0; indexOfArray_Num<MAX_ARR_SIZE; indexOfArray_Num++)
	{
		numArr[indexOfArray_Num] = 0;
	}
	for(u8 indexOfArray_Operation=0; indexOfArray_Operation<MAX_ARR_SIZE-1; indexOfArray_Operation++)
	{
		numArr[indexOfArray_Operation] = 0;
	}
	LCD_Clear();
	LCD_WriteString_GoTo(0,4,"Welcome..!");
	LCD_GoTo(2,0);
	result =0;
	last_pressed = NULL;
	sizeOfOperations = 0;
	sizeOfNumbers = 0;
	operationsPriorityCheck = 0;
}
/*
char arr[20] = {'0'};
char str1[20];
char str2[20];
u8 size=0;
u8 key = NO_KEY_PRESSED;
u8 next,prev,flag=0,counter=0;
u8 flag_mult_div=0;
u8 k1=0, k2=0;
u8 num1, num2,res1=0,res2=0;

void Calculator_2(void)
{
	key = KEYPAD_GetKey();
	_delay_ms(30);
	if(key != NO_KEY_PRESSED)
	{
		_delay_ms(20);
		if(flag==0)
		{
			arr[size] = key;
			LCD_WriteChar(key);
			size++;
		}
	}
	if(key == 'C')
	{
		LCD_Clear();
		/ *for(u8 i=0; i<size;i++)
		{
			arr[i] = '0';
		}* /
	}
	if(key == '=')
	{
		flag=1;
		for(u8 i=0; i<size ;i++)
		{
			if(arr[i] == '*')
			{
				for(u8 j=i+1; j<size ; j++)
				{
					if((arr[j]>='0' && arr[j] <='9'))
					{
						str1[k1] = arr[j]-'0';
						k1++;
						/ *next=j;
						break;* /
					}
					else
					{
						break;
					}
				}
				str1[k1] = '\0';
				for(u8 j=i-1; j>0; j--)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						str2[k2] = arr[j]-'0';
						k2++;
					}
					else
					{
						break;
					}
				}
				stringReverse(str2);
				str2[k2] = '\0';
				num1 = stringToInt(str1);
				num2 = stringToInt(str2);
				res1 = num1*num2;
/ *				
				arr[prev]  = (arr[prev]) - '0';
				arr[next]  = (arr[next]) - '0';
				arr[i] = (arr[prev]*arr[next]) + '0';
				arr[prev] = 'R';
				arr[next] = 'R';
* /
				/ *LCD_GoTo(3,counter++);
				LCD_WriteChar(arr[i]);* /
			}
			else if(arr[i] == '/')
			{
				for(u8 j=i+1; j<size; j++)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						next=j;
						break;
					}
				}
				for(u8 j=i-1; j>0; j--)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						prev=j;
						break;
					}
				}
				arr[prev]  = (arr[prev]) - '0';
				arr[next]  = (arr[next]) - '0';
				arr[i] = (arr[prev]/arr[next]) + '0';
				arr[prev] = 'R';
				arr[next] = 'R';
			}
		}
		for(u8 i=0; i<size;i++)
		{
			if(arr[i] == '+')
			{
				for(u8 j=i+1; j<size; j++)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						next=j;
						break;
					}
				}
				for(u8 j=i-1; j>0; j--)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						prev=j;
						break;
					}
				}
				arr[prev]  = (arr[prev]) - '0';
				arr[next]  = (arr[next]) - '0';
				arr[i] = (arr[prev]+arr[next]) + '0';
				arr[prev] = 'R';
				arr[next] = 'R';
			}
			else if(arr[i] == '-')
			{
				for(u8 j=i+1; j<size; j++)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						next=j;
						break;
					}
				}
				for(u8 j=i-1; j>0; j--)
				{
					if(arr[j]>='0' && arr[j] <='9')
					{
						prev=j;
						break;
					}
				}
				arr[prev]  = (arr[prev]) - '0';
				arr[next]  = (arr[next]) - '0';
				arr[i] = (arr[prev]-arr[next]) + '0';
				arr[prev] = 'R';
				arr[next] = 'R';
			}
		}
	}
	for(u8 i=0;i<size;i++)
	{
		if(flag==1)
		{
			if(arr[i]>='0' && arr[i]<='9')
			{
				LCD_GoTo(0,16);
				LCD_WriteChar(arr[i]);
				flag = 0;
				break;
			}
		}
		//break;
	}
}
*/
/*
void Calculator(void)
{
	key = KEYPAD_GetKey();
	while((key >= '0') && (key <= '9'))
	{
		LCD_WriteChar(key);
		if(counter==0)
		{
			key1 =  key1*10 + (key-'0');
		}
		else if(counter == 1)
		{
			key2 =  key2*10 + (key-'0');
		}
		key = KEYPAD_GetKey();
	}

	operation = key;
	if(operation == '+')
	{
		flag_t = 1;
		LCD_WriteChar(operation);
		counter++;
	}
	else if(operation == '-')
	{
		flag_t =2;
		LCD_WriteChar(operation);
		counter++;
	}
	else if(operation == '/')
	{
		flag_t =3;
		LCD_WriteChar(operation);
		counter++;
	}
	else if(operation == '*')
	{
		flag_t =4;
		LCD_WriteChar(operation);
		counter++;
	}

	if(operation == '=')
	{
		if(flag_t == 1)
		{
			result = key1 + key2;
		}
		else if(flag_t == 2)
		{
			result = key1 - key2;
		}
		else if(flag_t == 3)
		{
			result = key1 / key2;
		}
		else if(flag_t == 4)
		{
			result = key1 * key2;
		}
		_delay_ms(100);
	
		LCD_GoTo(1,0);
		LCD_WriteNumber_2(result);
	}
	if(key == 'C')
	{
		LCD_Clear();
		key1 = 0, key2 = 0, result=0 ,counter=0;
	}
	
}*/