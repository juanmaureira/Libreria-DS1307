# include "16F877a.h"
# use delay(Clock=20Mhz)

# FUSES NOWDT                 	//No Watch Dog Timer
# FUSES HS                 		//High speed oscillator
# FUSES NOBROWNOUT            	//No brownout reset
# FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O


#include"DS1307.c"

int dia=20, meses=4,ano=2012,hora=13,minutos=44,segundos=0;

// Ejemplo para setear hora utilizando la librería

void main(void){
		DS1307_init();
		delay_ms(5);
		DS1307_SetDatetime(dia,meses,ano,hora,minutos,segundos);
		while(true);
}

