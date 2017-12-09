/*
 * nordic_driver.c
 *
 *  Created on: 02-Dec-2017
 *      Author: Gunj Manseta
 */


#include <stdint.h>

#include "nordic_driver.h"
#include "spi.h"
#include "gpio.h"

//Commands Byte
#define NORDIC_TXFIFO_FLUSH_CMD	(0xE1)
#define NORDIC_RXFIFO_FLUSH_CMD	(0xE2)
#define NORDIC_W_TXPAYLD_CMD	(0xA0)
#define NORDIC_R_RXPAYLD_CMD	(0x61)
#define NORDIC_ACTIVATE_CMD		(0x50)
#define NORDIC_ACTIVATE_DATA	(0x73)
#define NORDIC_RXPAYLD_W_CMD	(0x60)

//Register Addresses
#define NORDIC_CONFIG_REG		(0x00)
#define NORDIC_STATUS_REG 		(0x07)
#define NORDIC_RF_SETUP_REG		(0x06)
#define NORDIC_RF_CH_REG		(0x05)
#define NORDIC_TX_ADDR_REG		(0x10)
#define NORDIC_TX_ADDR_LEN		(5)
#define NORDIC_FIFO_STATUS_REG	(0x17)


void NRF_gpioInit()
{

	//Enabling the GPIO PTD5 for Nordic CE pin
	GPIO_PORT_ENABLE(NORDIC_CE_PORT);
	GPIO_PinDir(NORDIC_CE_PORT,NORDIC_CE_PIN,gpio_output);
	GPIO_PinAltFuncSel(NORDIC_CE_PORT,NORDIC_CE_PIN,gpioAlt1_GPIO);
	GPIO_PinOutClear(NORDIC_CE_PORT,NORDIC_CE_PIN);

	//Enabling the GPIO PTA13 for Nordic IRQ pin
	GPIO_PORT_ENABLE(NORDIC_IRQ_PORT);
	GPIO_PinDir(NORDIC_IRQ_PORT,NORDIC_IRQ_PIN,gpio_input);
	GPIO_PinAltFuncSel(NORDIC_IRQ_PORT,NORDIC_IRQ_PIN,gpioAlt1_GPIO);
}


void NRF_moduleInit()
{
	NRF_gpioInit();

	SPI_init(SPI_0);
}

void NRF_moduleDisable()
{
	GPIO_PinAltFuncSel(NORDIC_CE_PORT,NORDIC_CE_PIN,gpioAlt0_Disabled);
	GPIO_PinAltFuncSel(NORDIC_IRQ_PORT,NORDIC_IRQ_PIN,gpioAlt0_Disabled);
	SPI_disable();
}

uint8_t NRF_read_register(uint8_t regAdd)
{
	//SPI_clear_RXbuffer(SPI_0);	//used to clear the previously value in the RX FIFO
	uint8_t readValue = 0;

	//CSN High to low for new command
	NRF_chip_disable();
	NRF_chip_enable();

	SPI_write_byte(SPI_0,regAdd);
	SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO
	SPI_write_byte(SPI_0,0xFF);
	readValue = SPI_read_byte(SPI_0);

	//Marking the end of transaction by CSN high
	NRF_chip_disable();

	return readValue;
}

void NRF_write_command(uint8_t command)
{
	//CSN High to low for new command
	NRF_chip_disable();
	NRF_chip_enable();

	SPI_write_byte(SPI_0,command);
	//SPI_clear_RXbuffer(SPI_0);	//used to clear the previously value in the RX FIFO
	SPI_read_byte(SPI_0);

	//Marking the end of transaction by CSN high
	NRF_chip_disable();
}

void NRF_write_register(uint8_t regAdd, uint8_t value)
{
	//SPI_clear_RXbuffer(SPI_0);	//used to clear the previously value in the RX FIFO

	//CSN High to low for new command
	NRF_chip_disable();
	NRF_chip_enable();

	SPI_write_byte(SPI_0,regAdd | 0x20);
	SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO
	SPI_write_byte(SPI_0,value);
	SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO

	//Marking the end of transaction by CSN high
	NRF_chip_disable();
}

uint8_t NRF_read_status()
{
	return  NRF_read_register(NORDIC_STATUS_REG);
}

void NRF_write_config(uint8_t configValue)
{
	NRF_write_register(NORDIC_CONFIG_REG, configValue);
}

uint8_t NRF_read_config()
{
	return NRF_read_register(NORDIC_CONFIG_REG);
}

uint8_t NRF_read_rf_setup()
{
	return NRF_read_register(NORDIC_RF_SETUP_REG);
}

void NRF_write_rf_setup(uint8_t rfSetupValue)
{
	NRF_write_register(NORDIC_RF_SETUP_REG, rfSetupValue);
}

uint8_t NRF_read_rf_ch()
{
	return NRF_read_register(NORDIC_RF_CH_REG);
}

void NRF_write_rf_ch(uint8_t channel)
{
	NRF_write_register(NORDIC_RF_CH_REG, channel);
}

void NRF_read_TX_ADDR(uint8_t *address)
{
	uint8_t i = 0;

	NRF_chip_disable();
	NRF_chip_enable();

	SPI_write_byte(SPI_0,NORDIC_TX_ADDR_REG);
	SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO
	//SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO
	while(i < NORDIC_TX_ADDR_LEN)
	{
		SPI_write_byte(SPI_0, 0xFF);	//Dummy to get the data
		*(address+i) = SPI_read_byte(SPI_0);
		i++;
	}

	NRF_chip_disable();
}

void NRF_write_TX_ADDR(uint8_t * address)
{
	NRF_chip_disable();
	NRF_chip_enable();

	SPI_write_byte(SPI_0,NORDIC_TX_ADDR_REG | 0x20);
	SPI_read_byte(SPI_0);	//used to clear the previously value in the RX FIFO
	SPI_write_packet(SPI_0,address,NORDIC_TX_ADDR_LEN);
	SPI_read_byte(SPI_0); //used to clear the previously value in the RX FIFO
	SPI_read_byte(SPI_0); //used to clear the previously value in the RX FIFO

	NRF_chip_disable();
}

uint8_t NRF_read_fifo_status()
{
	return NRF_read_register(NORDIC_FIFO_STATUS_REG);
}

void NRF_flush_tx_fifo()
{
	NRF_write_command(NORDIC_TXFIFO_FLUSH_CMD);
}

void NRF_flush_rx_fifo()
{
	NRF_write_command(NORDIC_RXFIFO_FLUSH_CMD);
}

void NRF_activate_cmd()
{
	NRF_write_register(NORDIC_ACTIVATE_CMD, NORDIC_ACTIVATE_DATA);
}

