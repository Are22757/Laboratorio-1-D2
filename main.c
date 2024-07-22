///***************************
//Universidad del Valle de Guatemala
//Programación de Microcontroladores
//Archivo:Proyecto
//Hardware:ATMEGA328P
//Autor:Lisbeth Ivelisse Arévalo Girón
//Carnet:22757
//***************************

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t inicio =0;
volatile uint8_t B1 = 0;
volatile uint8_t B2 = 0;
volatile uint8_t i = 0;
volatile uint8_t StartF = 0;



uint8_t numero[6] = {0b01011110,  //5
					 0b01101100,  //4
					 0b01110110,  //3
					 0b00110111,  //2
					 0b01100000,  //1
					 0b01111011}; //0

int main(void){
	cli();
	
	//Configuración de los pines de entrada
	
	DDRC &=~ (1<<DDC3); //Botón en PC3 para inicio
	PORTC |= (1<<PORTC3);
	
	DDRC &=~ (1<<DDC4); //Botón en PC4 para jugador 1
	PORTC |= (1<<PORTC4);
	
	DDRC &=~ (1<<DDC5); //Botón en PC5 para jugador 2
	PORTC |= (1<<PORTC5);
	
	//Configuración de los pines de salida
	
	DDRD |= (1<<DDD0); 
	DDRD |= (1<<DDD1); 
	DDRD |= (1<<DDD2); 
	DDRD |= (1<<DDD3); 
	DDRD |= (1<<DDD4); 
	DDRD |= (1<<DDD5);
	DDRD |= (1<<DDD6);
	
	//Configuración de los pines de salida para LEDS AZULES J1
	DDRB |= (1<<DDB3); 
	DDRB |= (1<<DDB2); 
	DDRB |= (1<<DDB1); 
	DDRB |= (1<<DDB0); 
	
	
	//Configuración de los pines de salida para LEDS VERDES J2 
	DDRB |= (1<<DDB5);
	DDRC |= (1<<DDC2);
	DDRC |= (1<<DDC1);
	DDRC |= (1<<DDC0);
	
	
	

	
	//Configuración de interrupciones
	PCICR |= (1<<PCIE1);  //Activando la interrución, porque se usará el puerto c para los botones
	
				//PC3           PC4         PC5
	PCMSK1 |= (1<<PCINT11)|(1<<PCINT12)|(1<<PCINT13); //Declarando botones con interrupciones
	
	
	
	
	//PORTB = 0;
	//PORTC = 0;
	
	UCSR0B = 0;
	
	sei();

	while(1)
	{
		PORTD = numero[i];
		if(inicio == 1)
		{
			if(i!=5) {
				PORTD = numero[i];
				_delay_ms(1000);
				i++;
				StartF = 1;
					}
		}
		if (B1 == 0){
			PORTB &= ~(0<<PB3);
			PORTB &= ~(0<<PB2);
			PORTB &= ~(0<<PB1);
			PORTB &= ~(0<<PB0);
			}
		else if (B1 == 1){
			PORTB = (1 << PB3);
			}
		else if (B1 == 2){
			PORTB = (1 << PB3)| (1 << PB2);
			}
		else if (B1 == 3){
			PORTB = (1 << PB3)| (1 << PB2)| (1 << PB1);
			}
		else if (B1 == 4){
			PORTB = (1 << PB3)| (1 << PB2)| (1 << PB1)| (1 << PB0);
			}
		else if (B1 == 5){
			
			PORTD = 0b01100000;
			_delay_ms(10000);
			}
				
		else if (B2 == 0){
			//PORTB = (0<<PB5);
			PORTC = (0<<PC0);
			PORTC = (0<<PC1);
			PORTC = (0<<PC2);
			}
		else if (B2 == 1){
			PORTB = (1 << PC0);
		}
		else if (B2 == 2){
			PORTC = (1 << PC0);
		}
		else if (B2 == 3){
			PORTC = (1 << PC1);
			}
		else if (B2 == 4){
			PORTC = (1 << PC2);
			}
		else if (B2 == 5){
			PORTB = (1<<PB5);
			PORTC = (1<<PC0);
			PORTC = (1<<PC1);
			PORTC = (1<<PC2);
			}
			
	}
}


ISR(PCINT1_vect) {
	if ((PINC & (1 << PINC3)) == 0) {
		inicio = 1;
		B1 = 0;
		B2 = 0;
	}
	if (inicio == 1)
	{
		if(i==5){
			if ((PINC & (1 << PINC4)) == 0) {
				B1++;
			}
			if ((PINC & (1 << PINC5)) == 0) {
				B2++;
			}
		}
	}
}
