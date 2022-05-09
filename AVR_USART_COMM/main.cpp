/*
 * AVR_USART_COMM.cpp
 *
 * Created: 03-05-2022 18:05:23
 * Author : yuann
 */ 
#define F_CPU 16000000
#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)
#define RX_BUFFER_SIZE 5

#include <avr/io.h>
#include <util/delay.h>

unsigned int tog = 0;


unsigned char dat[RX_BUFFER_SIZE];
unsigned char dat_single;
unsigned int numchar;

void usart_init(){
	UBRR0H |= (BAUDRATE >> 8);
	UBRR0L |= BAUDRATE;
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);
}

void serialTransmit(){
	unsigned int i = 0;
	
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = dat_single;
	
	/*while(i<RX_BUFFER_SIZE){
		while (!( UCSR0A & (1<<UDRE0))); 
		UDR0 = dat[i];
		i += 1;
		if(i==RX_BUFFER_SIZE){
			break;
		}
	}*/
		
}

int main(void)
{
	usart_init();
	
	DDRB = 0b00100000;
	PORTB = 0b00000000;
	
	numchar = 0;
	while(1){
		while(!((UCSR0A) & (1<<RXC0))); 
		//dat[numchar] = UDR0;
		//numchar += 1;
		
		dat_single = UDR0;
		
		if(numchar == 1){
			PORTB = 0b00100000;
			tog = 1;
		}
		else if(numchar == RX_BUFFER_SIZE){
			PORTB = 0b00000000;
			tog = 0;
		}
		serialTransmit();
		
		if(numchar == RX_BUFFER_SIZE){
			//serialTransmit();
			numchar = 0;
		}
	}
}

