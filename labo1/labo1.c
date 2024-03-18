// #include <pic12f683.h>
#include <xc.h>

// typedef unsigned int word;
// word __at 0x2007 __CONFIG = (_BODEN_OFF); 
#pragma config BOREN = OFF  
int NUM = 4;


void dec2bin(int num, int binary[3]) {
    for (int i = 0; i < 3; i++) {
        binary[2 - i] = (num >> i) & 1;
    }
}

void delay(unsigned int tiempo) {
    unsigned int i, j;
    for(i = 0; i < tiempo; i++) {
        for(j = 0; j < 1275; j++);
    }
}




void main() {
    TRISIO = 0x00; // Set GPIOs as outputs.

    while(1) {
        // Get binary representation of NUM.
        int binary[3];
        dec2bin(NUM, binary);

        // Assign each bit to its corresponding pin.
        GP0 = binary[0];
        GP1 = binary[1];
        GP2 = binary[2];

    }
}


// void main(void) {
//     TRISIO = 0x10; // P5 = input, rest are outputs
//     // ANSEL = 0x48; // FOSC/4, P5 = AN3

    // while (1) {

    //     GPIO = 0x00;
    //     if (GP4 == 1) { // Check if P4 is high
            // GPIO = 0x04; // Set P0 high (turn LED on)
        // } else {
        //     GPIO = 0x01; // Set P0 low (turn LED off)
        // }

    //         GPIO &= 0x0F;

    //         delay(100);
    //         GPIO = 0x0F;

    //         delay(100);

    //     } else {
    //         GPIO = 0x00; // Keep LED off if button is not pressed
    //     }
    // }
    // while (1) {
    //     if (GPIO.0 == 1)
    //     {
    //         GPIO = 0x01; // Set P0 high (turn LED on)
    //         delay(100);  

    //         GPIO = 0x00; // Set P0 low (turn LED off)
    //         delay(100);  
    //     }
    // }
// }      
