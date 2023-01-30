/*
 * keypad.c
 *
 * Created: 12/26/2022 10:24:46 PM
 *  Author: manal
 */ 
#include "../../HAL/includes/keypad.h"

int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3};//columns

void Keypad_init(){
	//DataDir_KEYPAD_PORT &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3)); //input
	// 	DataDir_KEYPAD_PORT |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3)); //output
	pinconfig.GPIO_PinNumber = R0;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = R1;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = R2;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = R3;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = C0;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = C1;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = C2;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	pinconfig.GPIO_PinNumber = C3;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(KEYPAD_PORT , &pinconfig);

	//KEYPAD_PORT = 0xFF;
	MCAL_GPIO_WritePORT(KEYPAD_PORT, 0xFF);

}

char Keypad_getkey(){
	int i,j;
	for (i = 0; i < 4; i++){
		//KEYPAD_PORT |= ((1<<Key_padCol[0]) | (1<<Key_padCol[1]) | (1<<Key_padCol[2]) | (1<<Key_padCol[3]));
		//KEYPAD_PORT &= ~(1<<Key_padCol[i]);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[0], GPIO_PIN_SET) ;
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[1], GPIO_PIN_SET) ;
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[2], GPIO_PIN_SET) ;
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[3], GPIO_PIN_SET) ;
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[i], GPIO_PIN_RESET) ;

		for(j = 0; j < 4; j++){
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0)
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0);
				switch(i){
				case (0):
							if (j == 0) return '7';
							else if (j == 1) return '4';
							else if (j == 2) return '1';
							else if (j == 3) return '?';
				break;
				case (1):
							if (j == 0) return '8';
							else if (j == 1) return '5';
							else if (j == 2) return '2';
							else if (j == 3) return '0';
				break;
				case (2):
							if (j == 0) return '9';
							else if (j == 1) return '6';
							else if (j == 2) return '3';
							else if (j == 3) return '=';
				break;
				case (3):
							if (j == 0) return '/';
							else if (j == 1) return '*';
							else if (j == 2) return '-';
							else if (j == 3) return '+';
				break;
				}
			}
		}
	}
	return 'A';
}
