#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/fuse.h>

// ISR for pin-change interrupt on PORTB
ISR(PCINT0_vect) {
    cli();
    if (PINB & (1 << PINB7)) {
        // Button pressed, turn on LEDs on B4 and B5, and turn off LEDs on B2, B3, and B6
        PORTB = (PORTB & ~((1 << PINB2) | (1 << PINB3) | (1 << PINB6))) | ((1 << PINB4) | (1 << PINB5));
        // reti();
    } else {
        // Button not pressed, turn on LEDs on B2, B3, and B6, and turn off LEDs on B4 and B5
        PORTB = (PORTB & ~((1 << PINB4) | (1 << PINB5))) | ((1 << PINB2) | (1 << PINB3) | (1 << PINB6));
        // reti();
    }
    sei();
}

// ISR for Timer1 compare with OCR1A
ISR(TIMER1_COMPA_vect) 
{   
    cli();

    sei();
}


int main(void) {
    // Timer1 setup
    // TIFR, TIMSK, OCR1A, OCR1B, TCCR1B
    OCR1A = 0x0F44;
    TIMSK |= (1 << OCIE1A);  // habilitar interrupciones para el timer1

    // Select clk source for timer1 and WGM = 4 for timer1 clear after compareA interrupt
    TCCR1B |= (1 << CS12)  | (1 << CS10) | (1 << WGM13) | (1 << WGM12);          
    TCCR1A |= (1 << WGM11) | (1 << WGM10);
    
    // Set B2-B7 as outputs, except B7 as input for the button
    DDRB = 0x7F; // Set all to output except B7
    PORTB |= (1 << PINB7); // Enable pull-up resistor for B7

    // Enable pin change interrupt for PORTB
    GIMSK |= (1 << PCIE0); // Enable pin change interrupt
    PCMSK |= (1 << PCINT7); // Enable pin change interrupt for B7
    

    // Enable global interrupts
    sei();
    // reti();
    unsigned int A = 0b000001;  // default value, vehicular light is green
    unsigned int B = 0b000010;  // vehicular light is blinking
    unsigned int C = 0b000100;  // yellow light
    unsigned int D = 0b001000;  // vehicular light is red and pedestrian light are red
    unsigned int E = 0b010000;  // pedestrian light is green
    unsigned int F = 0b100000;  // pedestrian light is blinking
    unsigned int state, next_state;
    
    state = A;
    // Main loop
    while (1) {
        switch(state){
            case 1: 
                PORTB = 0x04;
        }   

    }
}

