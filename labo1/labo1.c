#include <pic14/pic12f683.h> 
#include <stdint.h>

// Define configuration bits.
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF);


// Define helper functions.

// Linear Feedback Shift Register algorithm.
uint8_t lfsr_random() {
    static uint16_t lfsr = 0xABCDu; // Define a static variable 'lfsr' (Linear Feedback Shift Register).
    unsigned lsb = lfsr & 1; // 'lsb' (Least Significant Bit) is assigned the last bit of 'lfsr'.
    lfsr >>= 1; // Right shift 'lfsr' by 1.
    if (lsb)
        lfsr ^= 0xEF01u; // If 'lsb' is 1, XOR 'lfsr' with the hexadecimal number 0xEF01 (chosen randomly).
    return (uint8_t)(lfsr & 0x07); // Return the lowest 3 bits of 'lfsr' as an 8-bit unsigned integer.
}

// Convert decimal number to binary and store each bit in array.
void dec2bin(int num, int binary[3]) {
    // Loop over the 3 bits of 'num'.
    for (int i = 0; i < 3; i++) {
        binary[2 - i] = (num >> i) & 1; // Shift 'num' right by 'i' and isolate the LSB, store it in 'binary' in reverse order.
    }
}

// Delay function.
void delay(unsigned int tiempo) {
    unsigned int i, j;
    for (i = 0; i < tiempo; i++) {
        for (j = 0; j < 1275; j++);
    }
}

void main() {
    TRISIO = 0x10;   // Set all pins as outputs, except GP4.
    ANSEL = 0x00;    // Set all pins as Digital inputs (if the pin is an input).
    GPIO = 0x00;     // Set all GPIOs as outputs.
   

    while (1) {

        // Wait for button press.
        while (GP4 == 0) {
            // Do nothing, just wait here.
        }

        // Button is pressed, generate random number between 1-6 and convert to binary.
        uint8_t random_number = lfsr_random() % 6 + 1;
        int binary[3];
        dec2bin(random_number, binary);

        // Assign corresponding bits to their respective GPIO pin.
        GPIO = 0x00 + 4*binary[2] + 2*binary[1] + 1*binary[0];

        // Turn off LEDs after some arbitrary time.
        delay(500);
        GPIO = 0x00;

    }
}
