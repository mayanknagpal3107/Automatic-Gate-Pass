#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>

#include "uart.h"
#include "uart.c"
#include "lcd.c"
#include "lcd.h"
#include <avr/interrupt.h>

int data=0,data1=0;
char buff[20]={0};
char ab[20]={0};
char ac[20]={0};
unsigned int z,y,x,u,t,b;
int adc_val=0;

int readADC(int channel){
	
	int x;
	long val=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	
	//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running 4
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
	
	
	 //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   ADCSRA|=(1<<ADIF);	
	
	return ADCH;
}
/*void gate()
{
  int a=0;
  int enter=0;
  int leave=0;
  
  while(1)
   {
		if(bit_is_clear(PINA,2))
		{
			a=a+1;
		}
		
		if(bit_is_clear(PINA,3))
		{
			if(bit_is_clear(PINA,2))
			{
				a--;
				leave=1;
				PORTC=0X03;
			}
		}
		_delay_ms(1);
    }
}*/

void automatic()
{
		
	while(1)
	{
	
		if(bit_is_set(PINA,0))
		{
			PORTC=0XFF;
		}
        else
         PORTC=0X00;
	
	}
}
void transmit()
{
	cbi(PORTA,2);
	_delay_ms(2);
	sbi(PORTA,2);
	_delay_ms(2);
}
void Motor1_FORWARD(){

	cbi(PORTD,7);
	sbi(PORTD,6);
}

void Motor1_REVERSE(){

	sbi(PORTD,7);
	cbi(PORTD,6);
}
void STOP(){

	//sbi(PORTD,2);
	//sbi(PORTD,3);
	sbi(PORTD,7);
	sbi(PORTD,6);
}

	
void TON()
{
	z=500+80*(adc_val-88);  //us
	//t=(z);  //ms
}
void TOFF()
{
	y=(20000-z);
}
void TON1()
{
	x=2500+67*(adc_val-125);
	//b=(x/1000);
}
void TOFF1()
{
	u=(20000-b);
}
void Lcd()
{
	LCDInit(LS_BLINK | LS_ULINE);
	LCDWriteStringXY(0,0,"****WELCOME****");
	_delay_ms(1000);
	LCDClear();
	LCDWriteStringXY(0,0,"Accelormeter");
	_delay_ms(1000);
	
	
}				
	
void main()
{
   

	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	uart_puts("initialized");//uart_putc('f');
	int adc_val=0;
	int adc_val1=0;
	int adc_val2=0;
	int i=0;
	sbi(DDRC,3);
	//DDRC=0XFF;
	//PORTC=0X00;
	//motor
	sbi(DDRD,5);
	sbi(DDRD,6);
	sbi(DDRD,7);

	sbi(PORTD,5);
	sbi(DDRD,4);
	sbi(PORTC,3);
	sbi(DDRD,3);
	sbi(DDRD,2);
	
	
	Lcd();	
	//_delay_ms(50);
	//uart_puts("initialized");
		
	while(1)
	{
		//
		sbi(PORTC,3);
		adc_val=readADC(0);
		itoa(adc_val,ab,10);
		uart_puts(ab);
		LCDWriteStringXY(0,1,"x");
		LCDWriteIntXY(1,1,adc_val,4);
		//uart_puts("\n\r");
		//_delay_ms(500);
		
		/*adc_val1=readADC(1);
		itoa(adc_val1,ab,10);
	    adc_val2=readADC(2);
		itoa(adc_val2,ac,10);
		
		//transmit();
		
		/*uart_puts("-");
		uart_puts(ab);
		uart_puts("-");
		uart_puts(ac);
		uart_puts("\n");
		uart_puts("\r");
		//_delay_ms(5);
		*/
		//TON();
		//TOFF();
		//TON1();
		//TOFF1();
		
		/*z=500+80*(adc_val-88);  //us
		y=20000-z;
		sbi(PORTA,3);
		_delay_us(z);
		cbi(PORTA,3);
		_delay_us(y);
		_delay_ms(50);
		sbi(PORTA,3);
		_delay_us(x);
		cbi(PORTA,3);
		_delay_us(u);
	    _delay_ms(50);*/
	}
	
	
	
}
	/*uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	uart_puts("initialized");
	int a=0;
	int ENTER=0;
	//unsigned int c;
	//int D=0;
	//uart_putc('f');
	/*int adc_val=0;
	cbi(DDRA,2);
	cbi(DDRA,3);
	sbi(DDRA,0);
	sbi(DDRA,1);
	sbi(PORTA,0);
	sbi(PORTA,1);*/
	/*DDRC=0XFF;
	PORTC=0X00;
	sbi(DDRA,1);
	
	
	while(1)
	{
	   transmit();
		
	   if(bit_is_clear(PINA,2))
		{
		  ENTER=1;
		
		}
		
        if(ENTER==1)
        {	a=a+1;
			PORTC=0X03;
			uart_puts(a);
		}
		ENTER=0;

		/*c=uart_getc();
		if(c=='A')
		{
			PORTC=0XFF;
		}
		else
		    PORTC=0X01;*/
		
	
	
	
	
	



