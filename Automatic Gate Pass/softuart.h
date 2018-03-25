











#include <compat/deprecated.h>

#define SOFTUART_BAUD_RATE		9600	

#define SOFTUART_RXPIN   PINA
#define SOFTUART_RXDDR   DDRA
#define SOFTUART_RXBIT   PA0    

#define SOFTUART_TXPORT  PORTA
#define SOFTUART_TXDDR   DDRA
#define SOFTUART_TXBIT   PA2

#define SOFTUART_T_COMP_LABEL      TIMER2_COMP_vect
#define SOFTUART_T_COMP_REG        OCR2
#define SOFTUART_T_CONTR_REG       TCCR2
#define SOFTUART_T_CNT_REG         TCNT2
#define SOFTUART_T_INTCTL_REG      TIMSK

#define SOFTUART_CMPINT_EN_MASK    (1<<OCIE2)
#define SOFTUART_CTC_MASK          (1<<WGM21)

/* "A timer interrupt must be set to interrupt at three times 
   the required baud rate." */
#define SOFTUART_PRESCALE (8)

#if (SOFTUART_PRESCALE==8)
#define SOFTUART_PRESC_MASK           (1<<CS21)
#else 
#error "prescale unsupported"
#endif


#define SOFTUART_TIMERTOP ( F_CPU/SOFTUART_PRESCALE/SOFTUART_BAUD_RATE/3 -1)

#if (SOFTUART_TIMERTOP > 0xff)
#warning "Check SOFTUART_TIMERTOP"
#endif

#define SOFTUART_IN_BUF_SIZE     32

// Init the Software Uart
void softuart_init(void);

// disable the Software Uart
void softuart_disable();

// Clears the contents of the input buffer.
void softuart_flush_input_buffer( void );

// Tests whether an input character has been received.
unsigned char softuart_kbhit( void );

// Reads a character from the input buffer, waiting if necessary.
char softuart_getchar( void );

// To check if transmitter is busy
unsigned char softuart_can_transmit( void );

// Writes a character to the serial port.
void softuart_putchar( const char );

// Turns on the receive function.
void softuart_turn_rx_on( void );

// Turns off the receive function.
void softuart_turn_rx_off( void );

// Write a NULL-terminated string from RAM to the serial port
void softuart_puts( const char *s );

// Write a NULL-terminated string from program-space (flash) 
// to the serial port. i.e. softuart_puts_p(PSTR("test"))
void softuart_puts_p( const char *prg_s );

// Helper-Macro - "automaticly" inserts PSTR
// when used: include avr/pgmspace.h before this include-file
#define softuart_puts_P(s___) softuart_puts_p(PSTR(s___))

void softuart_gets(char*);
