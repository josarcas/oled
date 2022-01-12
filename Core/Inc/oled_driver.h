/*
 * oled_driver.h
 *
 *  Created on: Jan 12, 2022
 *      Author: JoseCarlos
 */

#ifndef INC_OLED_DRIVER_H_
#define INC_OLED_DRIVER_H_

/*INCLUDES********************************************************************/
#include "main.h"

/*DEFINES*********************************************************************/
extern I2C_HandleTypeDef hi2c1;
#define I2C_BUS			(I2C_HandleTypeDef *)&hi2c1
#define OLED_DIR		0x78

#define TIMEOUT			100

#define DISPLAY_OFF		0xae
#define DISPLAY_ON		0xaf
#define INVERT_COLOR	0xa7
#define NORMAL_COLOR	0xa6

#define NUM_PAGES		8
#define NUM_ROWS		128
#define SIZE_OLED		NUM_PAGES*NUM_ROWS

#define WIDTH			128
#define HEIGHT			64

#define FRAMES_5		0x00
#define	FRAMES_64       0x01
#define	FRAMES_128      0x02
#define	FRAMES_256      0x03
#define	FRAMES_3        0x04
#define	FRAMES_4        0x05
#define	FRAMES_25       0x06
#define	FRAMES_2        0x07

#define	PAGE_0    		0x00
#define	PAGE_1    		0x01
#define	PAGE_2    		0x02
#define	PAGE_3    		0x03
#define	PAGE_4    		0x04
#define	PAGE_5    		0x05
#define	PAGE_6    		0x06
#define	PAGE_7    		0x07

#define	HORIZONTAL_RIGHT  	0x26
#define	HORIZONTAL_LEFT   	0x27
#define	VERTICAL_RIGHT  	0x29
#define	VERTICAL_LEFT  		0x2A

/*TYPEDEFS********************************************************************/

/*PROTOYPES*******************************************************************/
void init_oled();
void set_pixel_oled(uint8_t x, uint8_t y);
void reset_pixel_oled(uint8_t x, uint8_t y);
void refresh_oled();
void set_contrast_oled(uint8_t contrast);
void horizontal_scroll_oled(uint8_t direction, uint8_t page_start,
		uint8_t page_end, uint8_t frame_rate, uint8_t offset);
void clear_oled();
void draw_bitmap_oled(const uint8_t *bitmap, uint8_t x, uint8_t y,
		uint16_t width, uint16_t height);


#endif /* INC_OLED_DRIVER_H_ */
