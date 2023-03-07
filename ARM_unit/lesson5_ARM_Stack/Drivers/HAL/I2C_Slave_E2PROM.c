/*
 * I2C_Slave_E2PROM.c
 *
 *  Created on: Jan 29, 2023
 *      Author: manal
 */
#include "I2C_Slave_E2PROM.h"

void eeprom_init(void)
{
	//=============I2C INIT==============
	//PB6 :I2C1_SCL
	//PB7:I2C1_SDA

	I2C_InitTyeDef I2C1CFG ;

	//I2C Controller act as a Master
	I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable ;
	I2C1CFG.I2c_ACK_Control = I2C_ACK_Enable;
	I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100K ;
	I2C1CFG.I2C_Mode = I2C_Mode_I2C ;
	I2C1CFG.P_Slave_Event_CallBack = NULL;
	I2C1CFG.StretchMode = I2C_StrechMode_Enable;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_INIT(I2C1,&I2C1CFG);

}


unsigned char eeprom_write_Nbytes(unsigned int Memory_address , unsigned char* bytes , uint8_t Data_Length)
{

	uint8_t i=0 ;
	//bytes is the effective data that want to be written in the memory adddress
	// Start+(EEPROM add+ w)+A+ upper byte memory address +A + upper byte memory address +A +byte1........
	//(unsigned char*)malloc(data_length +2)
	//dynamic memory allocation violate MISRA rule

	uint8_t buffer[256];
	buffer[0] = (uint8_t)(Memory_address>>8);//upper byte memory address
	buffer[1] = (uint8_t)(Memory_address);//lower byte memory address

	for(i=2 ; i< (Data_Length +2); i++)
	{
		buffer[i] = bytes[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_address, buffer, (Data_Length+2), with_Stop, start);
	return 0 ;

}
unsigned char eeprom_read_bytes(unsigned int Memory_address , uint8_t* dataOut , uint8_t Data_Length)
{
	unsigned char buffer[2];
	buffer[0] = (uint8_t)(Memory_address>>8);//upper byte memory address
	buffer[1] = (uint8_t)(Memory_address);//lower byte memory address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_address, &buffer, 2, without_Stop, start);//write the address only
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_address, dataOut, Data_Length, with_Stop, repeated_start);//read data
	return 0 ;










}

