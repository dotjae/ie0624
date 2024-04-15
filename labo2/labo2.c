#include <avr/io.h>
#include <avr/interrupt.h>

// Parameters for button and LEDs
#define BUTTON PINB7
#define LDPV PINB0
#define LDVA PINB1
#define LDVD PINB2
#define LDPP PINB3
#define LDPD PINB4

// Enum to represent the states
typedef enum {
    STATE_A,    // VEHICULE GREEN
    STATE_B,    // VEHICULE GREEN BLINK 
    STATE_C,    // YELLOW
    STATE_D,    // WAIT RED
    STATE_E,    // PEDESTRIAN GREEN
    STATE_F     // PEDESTRIAN GREEN BLINK
} state_t;

// Global variables
state_t CURRENT_STATE = STATE_A, last_state = STATE_A;      // Current and Last State variables
uint16_t TIMER_OVERFLOWS = 0;                               // Overflow counter
uint16_t BLINK_COUNTER = 0;                                 // Blink counter
uint8_t BUTTON_PRESSED = 0;                                 // Button flag
uint8_t A2B=0, B2C=0, C2D=0, D2E=0, E2F=0, F2D=0, D2A=0;    // State transition variables


// ISR for pin-change interrupt on PORTB
ISR(PCINT0_vect) {
    BUTTON_PRESSED = 1;     // Set button flag to 1
}

// ISR for Timer 1 Compare Match A 
ISR(TIMER1_COMPA_vect)
{
    BLINK_COUNTER++;                 // Update blink counter

    switch (CURRENT_STATE)
    {
        case STATE_B: 
            PORTB ^= (1 << LDPV);   // LDPV = ~LDPV  
            break;
        case STATE_F:
            PORTB ^= (1 << LDPP);   // LDPP = ~LDPP
            break;
    }
}

// ISR for Timer1 Overflow
ISR(TIMER1_OVF_vect)
{
    TIMER_OVERFLOWS++;  // Update overflow counter 

    // Check for state durations and transitions
    switch (CURRENT_STATE){
        case STATE_A:
            if (TIMER_OVERFLOWS >= 8 && BUTTON_PRESSED) {   // ~=10 seconds AND BUTTON_PRESSED
                if (A2B == 0) 
                {
                    A2B = 1;                                // Activate transition state
                    TIMER_OVERFLOWS = 0;                    // Reset timer 
                    BUTTON_PRESSED = 0;                     // Reset button flag
                }
            }
            break;
        case STATE_B:
            
            TIMSK |= (1 << OCIE1A);     // Enable Compare A Interrupt for Timer 1 
            TCCR1B |= (1 << WGM12);     // Enable CTC Timer 1
             
            if (BLINK_COUNTER >= 7)     // Blink finished
            {
                if (B2C == 0)
                {
                    B2C = 1;
                    TIMSK ^= (1 << OCIE1A);     // Disable Compare A Interrupt for Timer 1 
                    TCCR1B ^= (1 << WGM12);     // Disable CTC Timer 1
                    BLINK_COUNTER = 0;         
                    TIMER_OVERFLOWS = 0;        
                }   
            }
            break;
        case STATE_C:
            if (TIMER_OVERFLOWS >= 3) {     // ~=3 seconds 
                if (C2D == 0){
                    C2D = 1;
                    TIMER_OVERFLOWS = 0;    
                }   
            }
            break;
        case STATE_D:
            if (TIMER_OVERFLOWS >= 1) {     // ~=1 second
                switch (last_state) {
                    case STATE_C:
                        if (D2E == 0) {
                            D2E = 1;
                            TIMER_OVERFLOWS = 0;
                        }
                        break;
                    case STATE_F:
                        if (D2A == 0) {
                            D2A = 1;
                            TIMER_OVERFLOWS = 0;
                        }
                        break;
                }
            }
            break;
        case STATE_E:
            if (TIMER_OVERFLOWS >= 8) {     // ~=10 seconds 
                if (E2F == 0){
                    E2F = 1;
                    TIMER_OVERFLOWS = 0;  
                }   
            }
            break;
        case STATE_F:
            TIMSK |= (1 << OCIE1A);     // Enable Compare A Interrupt for Timer 1 
            TCCR1B |= (1 << WGM12);     // Enable CTC Timer 1
             
            if (BLINK_COUNTER >= 7) {           // 3 seconds 
                if (F2D == 0){
                    F2D = 1;
                    TIMSK ^= (1 << OCIE1A);     // Disable Compare A Interrupt for Timer 1 
                    TCCR1B ^= (1 << WGM12);     // Disable CTC Timer 1
                    BLINK_COUNTER = 0;
                    TIMER_OVERFLOWS = 0;     
                }   
            }
            break;
    }
}


int main(void) {
    // GPIO setup
    DDRB |= (1 << LDPV) | (1 << LDVA) |  (1 << LDVD) |  (1 << LDPP) | (1 << LDPD); // Set LEDs pins as outputs
    DDRB &= ~(1 << BUTTON);                                                        // Set Button pin as input
    
    // Enable pin change interrupt for PORTB
    GIMSK |= (1 << PCIE0);                  // Enable pin change interrupt
    PCMSK |= (1 << BUTTON);                 // Enable pin change interrupt for B7
    
    // Timer setup
    TCCR1B |= (1 << CS11) | (1 << CS10);    // Set prescaler to 256
    TIMSK |= (1 << TOIE1);                  // Enable Timer1 overflow interrupt
    OCR1A = 0x7A12;                         // Set value to compare with

    // Enable global interrupts
    sei();                                  
   
    while (1) {
        switch (CURRENT_STATE) {
            case STATE_A:
                PORTB |= (1 << LDPV) | (1 << LDPD);  // LDPV & LDPD ON

                if (A2B) { 
                    A2B = 0;                         // Reset State Transition variable
                    last_state = STATE_A;            // Update Last State
                    CURRENT_STATE = STATE_B;         // Update Current State
                }
                break;
            case STATE_B:
                // No change in LEDs status needed

                if (B2C) { 
                    B2C = 0;       
                    last_state = STATE_B;      
                    CURRENT_STATE = STATE_C;    
                }
                break;
            case STATE_C:
                PORTB |= (1 << LDVA) | (1 << LDPD);  // LDVA & LDPD ON

                last_state = STATE_C;
                if (C2D) { 
                    C2D = 0;
                    PORTB &= (0 << LDVA);            // LDVA OFF
                    CURRENT_STATE = STATE_D; 
                }
                break;
            case STATE_D:
                PORTB |= (1 << LDVD) | (1 << LDPD);  // LDVD & LDPD ON
                
                if (D2E){
                    D2E = 0;
                    PORTB &= (0 << LDPD);            // LDPD OFF
                    CURRENT_STATE = STATE_E;
                    last_state = STATE_D;
                }  
                else if (D2A){
                    D2A = 0;
                    PORTB &= (0 << LDVD);           // LDVD OFF
                    CURRENT_STATE = STATE_A;
                }
                break;
            case STATE_E:
                PORTB |= (1 << LDPP) | (1 << LDVD);  // LDPP & LDVD ON

                if (E2F) { 
                    E2F = 0;
                    last_state = STATE_E;
                    CURRENT_STATE = STATE_F;
                }
                break;
            case STATE_F:
                // No changes to LEDs status needed
 
                if (F2D) { 
                    F2D = 0;
                    PORTB &= (0 << LDPP);   // LDPP OFF
                    last_state = STATE_F;
                    CURRENT_STATE = STATE_D;
                }
                break;
            
            
        }
    }
}
