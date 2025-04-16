/**
 * @file   <nazev>.c
 * @author <Jmeno Prijmeni>
 * 
 */

#include <stdio.h>
#include "stm32_kit.h"
#include "stm32_kit/adc.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/uart.h"


BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000);
	
	ADC_setup();
	LCD_setup();
	UART_setup();
	LCD_set(LCD_CLR);
}

/*static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
};*/
uint16_t sample;
char text[9];

int main(void) {
	while (1) {
		sample = ADC_read();
		LCD_set(LCD_LINE1);
		sprintf(text, "%d  ", sample);
		LCD_print(text);
		delay_ms(100);
	}
}
