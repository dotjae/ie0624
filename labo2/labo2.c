#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_PIN PINB7

// Enum to represent the states
typedef enum {
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_D,
    STATE_E,
    STATE_F
} state_t;

state_t current_state = STATE_A, last_state = STATE_A;
uint16_t timer_ticks = 0; // Overflow counter
uint8_t A2B=0, B2C=0, C2D=0, D2E=0, E2F=0, F2D=0, D2A=0; // State transition variables
uint8_t BUTTON_PRESSED = 0;

// ISR for pin-change interrupt on PORTB
ISR(PCINT0_vect) {
    cli();
    BUTTON_PRESSED = 1;
    sei();
}

// ISR for Timer1 overflow
ISR(TIMER1_OVF_vect)
{
    timer_ticks++;  // Increment the overflow counter 

    // Check for state durations and transitions
    switch (current_state){
        case STATE_A:
            if (timer_ticks >= 10 && BUTTON_PRESSED) {   // 10 seconds passed
                if (A2B == 0) 
                {
                    A2B = 1; 
                    timer_ticks = 0;     // Reset timer 
                    BUTTON_PRESSED = 0;
                }
            }
            break;
        case STATE_B:
            if (timer_ticks >= 3)
            {  // 3 seconds 
                if (B2C == 0){
                    B2C = 1;
                    timer_ticks = 0;     // Reset timer
                }   
            }
            break;
        case STATE_C:
            if (timer_ticks >= 3) {  // 3 seconds 
                if (C2D == 0){
                    C2D = 1;
                    timer_ticks = 0;     // Reset timer
                }   
            }
            break;
        case STATE_D:
            if (timer_ticks >= 1) {  // 1 second
                switch (last_state) {
                    case STATE_C:
                        if (D2E == 0) {
                            D2E = 1;
                            timer_ticks = 0;
                        }
                        break;
                    case STATE_F:
                        if (D2A == 0) {
                            D2A = 1;
                            timer_ticks = 0;
                        }
                        break;
                }
            }
            break;
        case STATE_E:
            if (timer_ticks >= 10) {  // 10 seconds 
                if (E2F == 0){
                    E2F = 1;
                    timer_ticks = 0;     // Reset timer
                }   
            }
            break;
        case STATE_F:
            if (timer_ticks >= 3) {  // 3 seconds 
                if (F2D == 0){
                    F2D = 1;
                    timer_ticks = 0;     // Reset timer
                }   
            }
            break;
    }
}


int main(void) {
    DDRB = 0x1F; // Set B1-B7 as outputs
    DDRB &= ~(1 << BUTTON_PIN);   // Set B7 as input
    
    // Enable pin change interrupt for PORTB
    GIMSK |= (1 << PCIE0);  // Enable pin change interrupt
    PCMSK |= (1 << PCINT7); // Enable pin change interrupt for B7
    
    // Timer setup
    TCCR1B |= (1 << CS12);        // Set prescaler to 256
    TIMSK |= (1 << TOIE1);        // Enable Timer1 overflow interrupt
    sei();                        // Enable global interrupts
   
    while (1) {
        switch (current_state) {
            case STATE_A:
                PORTB |= (1 << 0) | (1 << 4);  // Turn on B0(PV) & B4(PD)  

                if (A2B) { 
                    A2B = 0;
                    PORTB = 0x00;
                    last_state = STATE_A;
                    current_state = STATE_B;  // Change to state B after delay
                }
                break;
            case STATE_B:
                PORTB |= (1 << 4);
                
                // ADD BLINKING BEHAVIOR
                PORTB |= (1 << 0) | (1 << 1) | (1 << 2);

                if (B2C) { 
                    B2C = 0;
                    PORTB = 0x00;
                    last_state = STATE_B;
                    current_state = STATE_C;  // Change to state C after delay
                }
                break;
            case STATE_C:
                PORTB |= (1 << 1) | (1 << 4);  // Turn on B1(VA) & B4(PD) 

                last_state = STATE_C;
                if (C2D) { 
                    C2D = 0;
                    PORTB = 0x00;
                    current_state = STATE_D;  // Change to state D after delay
                }
                break;
            case STATE_D:
                PORTB |= (1 << 2) | (1 << 4);  // Turn on B2(VD) & B4(PD)  
                
                if (D2E){
                    D2E = 0;
                    PORTB = 0x00;
                    current_state = STATE_E; // Change to state E after delay
                    last_state = STATE_D;
                }  
                else if (D2A){
                    D2A = 0;
                    PORTB = 0x00;
                    current_state = STATE_A; // Change to state A after delay
                }
                break;
            case STATE_E:
                PORTB |= (1 << 3) | (1 << 2);  // Turn on B3(PP) & B2(VD)  

                if (E2F) { 
                    E2F = 0;
                    PORTB = 0x00;
                    last_state = STATE_E;
                    current_state = STATE_F;  // Change to state F after delay
                }
                break;
            case STATE_F:
                PORTB |= (1 << 2);
               
                // ADD BLINKING BEHAVIOR
                PORTB |= (1 << 3) | (1 << 4);

                if (F2D) { 
                    F2D = 0;
                    PORTB = 0x00;
                    last_state = STATE_F;
                    current_state = STATE_D;  // Change to state D after delay
                }
                break;
            
            
        }
    }
}
