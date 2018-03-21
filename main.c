# include "16F877a.h"
# use delay(Clock=20Mhz)
# use rs232(UART)

# FUSES NOWDT                 	//No Watch Dog Timer
# FUSES HS                 		//High speed oscillator
# FUSES NOBROWNOUT            	//No brownout reset
# FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

# DEFINE	MAXBUFFER	20

#include "stdlib.h"
#include "DS1307.c"

int data, next;
char BufferReceive[MAXBUFFER];
short FlagReceive=false;

char hr[3];
char min[3];
char seg[3];
char day[3];
char meses[3];
char year[3];

void InitializeComponents(void){
	DS1307_init();
	enable_interrupts(int_rda);
	enable_interrupts(global);
}

void ClearBuffer(void){
	memset(BufferReceive,0,MAXBUFFER);
	next=0;
}

char CopyMemory(char *data, char *str,int ini, int len){
int i;
	for(i=0;i<len;i++)
		str[i]=data[ini+i];
	return *str;
}

void SetRtc(void){
int hora,minutos,segundos,dia,mes,ano;

	CopyMemory(BufferReceive, hr,0, 2);
	CopyMemory(BufferReceive, min,2, 2);
	CopyMemory(BufferReceive, seg,4, 2);
	CopyMemory(BufferReceive, day,6, 2);
	CopyMemory(BufferReceive, meses,8, 2);
	CopyMemory(BufferReceive, year,10, 2);

	hora=atoi(hr);
	minutos=atoi(min);
	segundos=atoi(seg);
	dia=atoi(day);
	mes=atoi(meses);
	ano=atoi(year);

	DS1307_SetDatetime(dia,mes,ano,hora,minutos,segundos);
	ClearBuffer();
	FlagReceive=false;
	
}

void main(void){
		InitializeComponents();
		printf("Ingrese cadena para configurar reloj de la forma hhmmssddMMyy\r\n");
		while(true){
			if(FlagReceive)
				SetRtc();
		}
}

#int_rda
void IsrRda(void){
	data=putc(getc());
	if(data!=0x0D)
		BufferReceive[next++]=data;
	else
		FlagReceive=true;
}
