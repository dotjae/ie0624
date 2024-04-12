#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/fuse.h>

FUSES = 
{   
    .low = (FUSE_CKSEL3 & FUSE_CKSEL2 & FUSE_CKSEL0),
    .high = (FUSE_CKSEL1)
};

// ISR for Timer1 overflow
ISR(TIMER1_OVF_vect) 
{   
    cli();
    PORTB = ~PORTB;
    sei();
}


int main(void) {
    // Timer1 setup
    // TIFR, TIMSK, OCR1A, OCR1B, TCCR1B
    TIMSK |= (1 << TOIE1);
    TIMSK = 0x80;
    TCCR1B |= ((1 << CS12)  | (1 << CS10));
    
    // Set B2-B7 as outputs, except B7 as input for the button
    DDRB = 0x7F; // Set all to output except B7
    PORTB |= (1 << PINB7); // Enable pull-up resistor for B7

    // Enable global interrupts
    sei();
    // reti();

    // Main loop
    while (1) {
        // The main loop is empty as the ISR handles the button press and LED control
    }
}

