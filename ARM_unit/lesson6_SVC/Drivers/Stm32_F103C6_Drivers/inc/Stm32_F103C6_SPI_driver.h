/*
 * Stm32_F103C6_spi_driver.h
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"

struct S_IRQ_SRC
{
	uint8_t TXE:1 ;           // TX buffer empty Interrupt
	uint8_t RXNE:1 ;           // RX buffer not empty Interrupt
	uint8_t ERR:1 ;           // ERROR Interrupt
	uint8_t Reserved:5 ;
};
//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------
typedef struct
{
	uint16_t 				  Device_Mode ;               //Specifies the SPI operating mode @ref SPI_Device_Mode

	uint16_t  				  Communication_Mode ;        //Specifies the SPI bidirectional state @ref SPI_Communication_Mode

	uint16_t                  frame_format ;             //Specifies LSB or MSB @ref SPI_frame_format

	uint16_t                  Data_Size ;                // @ref SPI_Data_Size

	uint16_t                  CLKPolarity ;             // @ref SPI_CLKPolarity

	uint16_t                   CLKPhase ;               // @ref SPI_CLKPhase

	uint16_t                    NSS ;                   //Specifies whether the NSS signal is managed by
	//hardware(NSS Pin) or the software using the SSI bit enable
	//@ref SPI_NSS


	uint16_t                    SPI_BAUDRATEPrescaler ; //Specifies the Baud Rate prescaler value which will be used to
	//configure the transmit and receive SCK clock.
	// This parameter must be set based on @ref SPI_BAUDRATEPrescaler
	//@note the communication clock is derived from the master clock
	// the slave clock doesn't need to be set
	//take care you have to configure RCC to enter the correct clock to APB2>>>>SPI1

	uint16_t                    IRQ_Enable ;	        //@ref SPI_IRQ_Enable

	void(*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);    // Set the C Function which will be called once the IRQ Happen

}SPI_Config;
//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref Module_REF_NAME_define

//@ref SPI_Device_Mode
#define SPI_Device_Mode_Master                        (0x1U<<2)    //CR1>>bit2
#define SPI_Device_Mode_Slave                          (0x00000000U)


//@ref SPI_Communication_Mode
#define SPI_Communication_Mode_2LINES                                 (0x00000000U) // CR1 :Full dublex
#define SPI_Communication_Mode_2LINES_RXONLY                           (0x1U <<10) //bit 10 RXONLY Half dublex
#define SPI_Communication_Mode_1LINES_recieve_only                    (0x1U << 15) //bit15 bidirectional data mode enable
#define SPI_Communication_Mode_1LINES_transmit_only                   ( (0x1U << 15) | (0x1U << 14)) // bit14 bidirectional output mode

//@ref SPI_frame_format
#define  SPI_frame_format_LSB_transmitted_first                        (0x1U <<7) //CR1:Bit 7
#define  SPI_frame_format_MSB_transmitted_first                         (0x00000000U)

//@ref SPI_Data_Size
#define SPI_Data_Size_8BIT                                           (0x00000000U)
#define SPI_Data_Size_16BIT                                          (0x1U<<11) // CR1:Bit 11 DFF

// @ref SPI_CLKPolarity
#define SPI_CLKPolarity_Low_when_idle                                (0x00000000U)
#define SPI_CLKPolarity_High_when_idle                                (0x1U<<1) //bit1 CPOL

// @ref SPI_CLKPhase
#define SPI_CLKPhase_1stEDGE_first_data_capture_edge                      (0x00000000U)
#define SPI_CLKPhase_2ndEDGE_first_data_capture_edge                       (0x1U<<0) //bit0 CPHA

//@ref SPI_NSS
//hardware
#define SPI_NSS_Hard_Slave                                              (0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable                            (0x1U<<2)    //SPI_CR2 bit2
#define SPI_NSS_Hard_Master_SS_output_disable                            ~(0x1U<<2)   //SPI_CR2 bit2
//NSS is driven by SW (Master or slave)
#define SPI_NSS_Soft_NSSInternalSoft_Reset                              (0x1U<<9)
#define SPI_NSS_Soft_NSSInternalSoft_set                                ( (0x1U<<9) | (0x1U<<8))


//@ref SPI_BAUDRATEPrescaler
#define SPI_BAUDRATEPrescaler_2                                         (0x00000000U)
#define SPI_BAUDRATEPrescaler_4                                          (0b001 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_8                                          (0b010 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_16                                          (0b011 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_32                                          (0b100 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_64                                          (0b101 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_128                                         (0b110 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_256                                          (0b111 << 3)//Bits 5:3

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE                                             (uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE                                             (uint32_t)(1<<7) //CR2 Bit7 TXEIE
#define SPI_IRQ_Enable_RXNEIE                                             (uint32_t)(1<<6) //CR2 Bit6 RXNEIE
#define SPI_IRQ_Enable_ERRIE                                             (uint32_t)(1<<5) //CR2 Bit7 ERRIE




/*
 * ====================================================================================================
 *                          APIs Supported by "MCAL SPI DRIVER"
 * ====================================================================================================
 */
void MCAL_SPI_INIT(SPI_TypeDef * SPIx , SPI_Config* SPI_confg) ;
void MCAL_SPI_DeINIT(SPI_TypeDef * SPIx , SPI_Config* SPI_confg) ;

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef * SPIx) ;

void MCAL_SPI_SendData(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn) ;
void MCAL_SPI_ReceiveData(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn) ;
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn) ;






#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
