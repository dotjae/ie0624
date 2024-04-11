#include <avr/io.h>
#include <avr/interrupt.h>

// ISR for pin-change interrupt on PORTB
ISR(PCINT0_vect) {
    if (PINB & (1 << PINB7)) {
        // Button pressed, turn on LEDs on B4 and B5, and turn off LEDs on B2, B3, and B6
        PORTB = (PORTB & ~((1 << PINB2) | (1 << PINB3) | (1 << PINB6))) | ((1 << PINB4) | (1 << PINB5));
        // reti();
    } else {
        // Button not pressed, turn on LEDs on B2, B3, and B6, and turn off LEDs on B4 and B5
        PORTB = (PORTB & ~((1 << PINB4) | (1 << PINB5))) | ((1 << PINB2) | (1 << PINB3) | (1 << PINB6));
        // reti();
    }
}

void main(void) {
    // Set B2-B7 as outputs, except B7 as input for the button
    DDRB = 0x7F; // Set all to output except B7
    PORTB |= (1 << PINB7); // Enable pull-up resistor for B7

    // Enable pin change interrupt for PORTB
    GIMSK |= (1 << PCIE0); // Enable pin change interrupt
    PCMSK |= (1 << PCINT7); // Enable pin change interrupt for B7

    // Enable global interrupts
    sei();
    // reti();

    // Main loop
    while (1) {
        // The main loop is empty as the ISR handles the button press and LED control
    }
}
