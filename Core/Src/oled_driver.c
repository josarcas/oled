/*
 * oled_driver.c
 *
 *  Created on: Jan 12, 2022
 *      Author: JoseCarlos
 */

/*INCLUDES********************************************************************/
#include "oled_driver.h"

/*GLOBAL VARIABLES************************************************************/
static uint8_t matrix[NUM_PAGES][NUM_ROWS];

/*PROTOTYPES******************************************************************/
static void write_command_oled(uint8_t command);
static void write_page_oled(uint8_t num_pag, uint8_t *data, uint16_t size);
static void set_bit(uint8_t x, uint8_t y);
static void reset_bit(uint8_t x, uint8_t y);

/*FUNCTIONS*******************************************************************/
static void write_command_oled(uint8_t command)
{
	uint8_t buffer[2] = {0x00, command};

	HAL_I2C_Master_Transmit(I2C_BUS, OLED_DIR, buffer, 2, TIMEOUT);
}

static void write_page_oled(uint8_t num_pag, uint8_t *data, uint16_t size)
{
	uint8_t buffer[size+1];

	buffer[0] = 0x40;

	for(uint8_t i=0; i<size; i++)
		buffer[i+1] = data[i];

	write_command_oled(0xb0 + num_pag);
	write_command_oled(0x00);
	write_command_oled(0x10);

	//HAL_I2C_Master_Transmit(I2C_BUS, OLED_DIR, (uint8_t *)0x40, 1, TIMEOUT);
	HAL_I2C_Master_Transmit(I2C_BUS, OLED_DIR, buffer, size+1, TIMEOUT);
}

static void set_bit(uint8_t x, uint8_t y)
{
	if(x>WIDTH || y>HEIGHT)
		return;

	matrix[y/8][x] |= 0x01 << (y%8);
}

static void reset_bit(uint8_t x, uint8_t y)
{
	if(x>WIDTH || y>HEIGHT)
		return;
	matrix[y/8][x] = matrix[y/8][x] ^(matrix[y/8][x] & (0x01<<y%8));
}

void init_oled()
{
	write_command_oled(0xa8);
	write_command_oled(0x3f);
	write_command_oled(0xd3);
	write_command_oled(0x00);
	write_command_oled(0x40);
	write_command_oled(0xa1);
	write_command_oled(0xc8);
	write_command_oled(0xad);
	write_command_oled(0x02);
	write_command_oled(0x81);
	write_command_oled(0x7f);
	write_command_oled(0xa4);
	write_command_oled(0xa6);
	write_command_oled(0xd5);
	write_command_oled(0x80);
	write_command_oled(0x8d);
	write_command_oled(0x14);
	write_command_oled(0xaf);

	clear_oled();
}

void set_pixel_oled(uint8_t x, uint8_t y)
{
	set_bit(x, y);
	write_page_oled(y/8, matrix[y/8], NUM_ROWS);
}

void reset_pixel_oled(uint8_t x, uint8_t y)
{
	reset_bit(x, y);
	write_page_oled(y/8, matrix[y/8],NUM_ROWS);
}

void refresh_oled()
{
	for(uint16_t i=0; i<NUM_PAGES; i++)
	{
		write_page_oled(i, matrix[i], NUM_ROWS);
	}
}

void clear_oled()
{
	for(uint16_t i=0; i<NUM_PAGES; i++)
	{
		for(uint16_t j=0; j<NUM_ROWS; j++)
			matrix[i][j] = 0;
	}

	refresh_oled();
}

void draw_bitmap_oled(const uint8_t *bitmap, uint8_t x, uint8_t y,
		uint16_t width, uint16_t height)
{
	uint16_t len = (width*height)/8;
	uint16_t k=0;

	while(k < len)
	{
		for(uint16_t l=0; l<width; l++)
		{
			for(uint16_t i=0; i<8; i++)
			{
				if(bitmap[k]>>i & 0x01)
					set_bit(x+l, y+i);
					//set_pixel_oled(x+l, y+i);
				else
					reset_bit(x+l, y+i);
					//reset_pixel_oled(x+l, y+i);
			}

			k++;
		}

		y+=8;
	}

	refresh_oled();
}
