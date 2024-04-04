#include <pic14/pic12f683.h> // Adjust this include for your specific PIC model
#include <stdint.h>

// Define configuration bits (this might need adjustment based on your PIC and requirements)
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF & _MCLRE_OFF);


// Define functions and logic as per your original code
uint8_t lfsr_random() {
    static uint16_t lfsr = 0xACE1u;
    unsigned lsb = lfsr & 1;
    lfsr >>= 1;
    if (lsb)
        lfsr ^= 0xB400u;
    return (uint8_t)(lfsr & 0x07);
}

void dec2bin(int num, int binary[3]) {
    for (int i = 0; i < 3; i++) {
        binary[2 - i] = (num >> i) & 1;
    }
}

void delay(unsigned int tiempo) {
    unsigned int i, j;
    for (i = 0; i < tiempo; i++) {
        for (j = 0; j < 1275; j++);
    }
}

void main() {
    TRISIO = 0x10;   // TRISIO4 = 1; Set GP4 as input (for the button)
    ANSEL = 0x00;
    GPIO = 0x00;      // Set all GPIOs as outputs
    // GP4 = 1;

    
    while (1) {
        // Wait for button press
        while (GP4 == 0) {
            // Do nothing, just wait here


            // GPIO = 0x01;
        }
            // GPIO = 0x04;


        // Button is pressed, generate random number and convert to binary
        uint8_t random_number = lfsr_random() % 6 + 1;
        int binary[3];
        dec2bin(random_number, binary);

        // Assign each bit to its corresponding pin
        // GP0 = binary[0];
        // GP1 = binary[1];
        // GP2 = binary[2];

        GPIO = 0x00 + 4*binary[2] + 2*binary[1] + 1*binary[0];

        delay(250);
        // Wait for button release
        while (GP4 == 1) {
            // Do nothing, just wait here
        }

        delay(250); // Optional delay
    }
}
