/**
 * @file   <nazev>.c
 * @author <Jmeno Prijmeni>
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/button.h"
#define MAX 17


BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000);
	
	LCD_setup();
	LED_setup();
	BTN_setup();
	KBD_setup();
}

char mody[6][17] = {"<KM-ML>        ", "<KG-ST>        ", "<ST-IT>        "};
char mody_naopak[6][17] = {"<ML-KM>        ", "<ST-KG>        ", "<IT-ST>        "};
char text1[17], text2[17];
int position = 0;
bool vyber_modu = false, naopak = false;
char znak, znakx, znaky;
int cislo, cisloN, cisloS, prevod, citac_znaku = 0;
#ifndef KEYPAD_STYLE
  static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
  };
#endif

int main(void) {
	while (1) {
		LCD_set(LCD_CLR);
		LCD_set(LCD_LINE1);
		LCD_print("Vyber            ");
		if(naopak == false) {
			LCD_set(LCD_LINE2);
			LCD_print(mody[position]);
		} else {
			LCD_set(LCD_LINE2);
			LCD_print(mody_naopak[position]);
		}
		
		do{
			znak = KBD_read();
		}while(!znak);
		delay_ms(100);
		
		if(znak == '*')position--;
		if(znak == '#')position++;
		if(znak == '1'){
			naopak = !naopak;
		}
		if(position > 2)position = 0;
		if(position < 0)position = 2;
		
		if(znak == '0'){
			vyber_modu = true;
			if(naopak == true){
				position = position + 3;
			}
		}
		
		if(vyber_modu == true) {
			switch (position) {
				case 0:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("KM:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 0.1574;
							sprintf(text1, "ML: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
				case 1:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("KG:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 0.1574;
							sprintf(text1, "ST: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
				case 2:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("ST:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 9;
							sprintf(text1, "IT: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
				case 3:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("ML:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 0.1574;
							sprintf(text1, "KM: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
				case 4:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("ST:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 0.1574;
							sprintf(text1, "KG: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
				case 5:
					LCD_set(LCD_CLR);
					for(int i=0;i<10;i++){
						LCD_set(LCD_LINE1);
						LCD_print("IT:                 ");
						do{
							znakx = KBD_read();
						}while(!znakx);
						
						if(znakx == 'A'){
							prevod = cisloN * 0.1574;
							sprintf(text1, "ST: %d                ", prevod);
							
							LCD_set(LCD_CLR);
							LCD_set(LCD_LINE1);
							LCD_print(text1);
							LCD_set(LCD_LINE2);
							LCD_print("Return - 'D'");
							do{
								znaky = KBD_read();
							}while(znaky != 'D');
							if(znaky == 'D'){
								cislo = 0;
								cisloN = 0;
								vyber_modu = false;
								citac_znaku = 0;
								znak = ' ';
								znakx = ' ';
								znaky = ' ';
								break;
							}
						}
						
						cislo = znakx - '0';
						if(citac_znaku >= 1) {
							cisloN = (cisloN*10)+cislo;
							citac_znaku++;
						} else {
							cisloN = cislo;
							citac_znaku++;
						}
						sprintf(text1, "%d                ", cisloN);
						LCD_set(LCD_LINE2);
						LCD_print(text1);
					}
					break;
			}
		}
	}
}

