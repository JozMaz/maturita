/**
 * @file   <nazev>.c
 * @author Jozue Dan Mazur
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/button.h"
#include "stm32_kit/keypad.h"
#include <stdio.h>
#include <stdbool.h>
#define SIZE 17
#ifndef KEYPAD_STYLE
	static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
			'1', '2', '3', //'A',
			'4', '5', '6', //'B',
			'7', '8', '9', //'C',
			'*', '0', '#', //'D'
	};
#endif
	
int position = 0;
char znak, znak1;
char text_cas_cykl[SIZE], text_cas_zbyvajici[SIZE];
int cyklus = 0;
int sec = 0, min = 0, celk_sec = 0, pom_vypocet = 0;
bool prace = false, vypocitano = false, vyprano = false, zamknuto = false, pauza = false;
char faze[4][17] = {"namaceni        ", "prani           ", "oplachnuti      ", "suseni          "};
char delka[3][17] = {"KR: 2m          ", "DL: 5m          ", "TEST: 1m        "};
int namaceni, prani, oplachnuti, suseni, i;
	
OS_TID id_task1;
OS_TID id_task2;
OS_TID id_task3;
OS_TID id_task4;
OS_TID id_task5;
OS_TID id_task6;
OS_TID id_task7;

__task void Program() {
		for (;;) {
			if(prace == false) {
				
				switch(position) {
					case 0:
						LCD_set(LCD_LINE1);
						LCD_print(delka[0]);
						min = 2;
						celk_sec = 0;
					break;
					case 1:
						LCD_set(LCD_LINE1);
						LCD_print(delka[1]);
						min = 5;
						celk_sec = 0;
						break;
					case 2:
						LCD_set(LCD_LINE1);
						LCD_print(delka[2]);
						min = 1;
						celk_sec = 0;
						break;
				}

				do{
					znak = KBD_read();
				}while(!znak);
				
				if(znak == '*')position--;
				if(znak == '#')position++;
				
				if(position > 2)position = 0;
				if(position < 0)position = 2;
				
				if(znak == '0') {
					prace = true;
				}
			}
		}
}

__task void Prace() {
		for (;;) {
			if(prace == true && vyprano == false && pauza == false) {
				if(vypocitano == false){
					celk_sec = min*60;
				
					prani = celk_sec * 0.6;
					oplachnuti = celk_sec * 0.2;
					suseni = celk_sec * 0.15;
					namaceni = celk_sec-prani-oplachnuti-suseni;
					vypocitano = true;
					celk_sec = 0;
				}
				
				
				sprintf(text_cas_cykl, "%02d:%02d           ", min, celk_sec);
				sprintf(text_cas_zbyvajici, "%02d:%02d           ", min, celk_sec);
				
				LCD_set(LCD_LINE1);
				LCD_print(faze[cyklus]);
				LCD_set(LCD_LINE2);
				LCD_print(text_cas_cykl);
				
				if(celk_sec == 0) {
					celk_sec = 59;
					if(min > 0) {
						min--;
					}
				} else {
					celk_sec--;
					pom_vypocet++;
				}
				
				if(cyklus == 0) {
					if(pom_vypocet == namaceni) {
						pom_vypocet = 0;
						cyklus++;
						LCD_set(LCD_CLR);
					}
				}
				if(cyklus == 1) {
					if(pom_vypocet == prani) {
						pom_vypocet = 0;
						cyklus++;
						LCD_set(LCD_CLR);
					}
				}
				if(cyklus == 2) {
					if(pom_vypocet == oplachnuti) {
						pom_vypocet = 0;
						cyklus++;
						LCD_set(LCD_CLR);
					}
				}
				if(cyklus == 3) {
					if(pom_vypocet == suseni) {
						pom_vypocet = 0;
						vyprano = true;
						LCD_set(LCD_CLR);
					}
				}
			}
			if(vyprano == true) {
				LCD_set(LCD_CLR);
				LCD_set(LCD_LINE1);
				LCD_print("Konec!                  ");
			}
		}
}

__task void EX_Led() {
		for (;;) {
			if(vyprano == false && prace == true){
				switch(cyklus) {
					case 0:
						io_set(LED_EX_0, 0);
						io_set(LED_EX_1, 1);
						io_set(LED_EX_2, 1);
						io_set(LED_EX_3, 1);
						break;
					case 1:
						io_set(LED_EX_1, 0);
						io_set(LED_EX_0, 1);
						io_set(LED_EX_2, 1);
						io_set(LED_EX_3, 1);
						break;
					case 2:
						io_set(LED_EX_2, 0);
						io_set(LED_EX_1, 1);
						io_set(LED_EX_3, 1);
						break;
					case 3:
						io_set(LED_EX_3, 0);
						io_set(LED_EX_0, 1);
						io_set(LED_EX_1, 1);
						io_set(LED_EX_2, 1);
						break;
				}
			} else {
				io_set(LED_EX_0, 1);
				io_set(LED_EX_1, 1);
				io_set(LED_EX_2, 1);
				io_set(LED_EX_3, 1);
			}
		}
}

__task void IN_Led() {
		for (;;) {
			if(zamknuto == false){
				io_set(LED_IN_0, 1);
				io_set(LED_IN_1, 0);
				io_set(LED_IN_2, 0);
				io_set(LED_IN_3, 0);
			}
			if(pauza == true){
				io_set(LED_IN_1, 1);
				io_set(LED_IN_0, 0);
				io_set(LED_IN_2, 0);
				io_set(LED_IN_3, 0);
			}
			if(zamknuto == true){
				io_set(LED_IN_2, 1);
				io_set(LED_IN_0, 0);
				io_set(LED_IN_1, 0);
				io_set(LED_IN_3, 0);
			}
			if(prace == false){
				io_set(LED_IN_3, 1);
				io_set(LED_IN_0, 0);
				io_set(LED_IN_1, 0);
				io_set(LED_IN_2, 0);
			}
		}
}

__task void Zamek() {
		for (;;) {
			if(cyklus == 3) {
				zamknuto = true;
			}
		}
}
		
__task void Pauza() {
		for (;;) {
			if(io_read(USER_BUTTON)){
				pauza = true;
			} else {
				pauza = false;
			}
		}
}

__task void Opakovani() {
		for (;;) {
			if(vyprano == true){
				do{
					znak = KBD_read();
				}while(!znak);
				if(znak == '1'){
					prace = false;
					vypocitano = false;
					vyprano = false;
					zamknuto = 1;
					cyklus = 0;
					znak = ' ';
				}
			}
		}
}



__task void setup() {
	LED_setup();
	LCD_setup();
	BTN_setup();
	KBD_setup();
	
	id_task1 = os_tsk_create(Program, 0);
	id_task2 = os_tsk_create(Prace, 0);
	id_task3 = os_tsk_create(EX_Led, 0);
	id_task4 = os_tsk_create(IN_Led, 0);
	id_task5 = os_tsk_create(Zamek, 0);
	id_task6 = os_tsk_create(Pauza, 0);
	id_task7 = os_tsk_create(Opakovani, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

