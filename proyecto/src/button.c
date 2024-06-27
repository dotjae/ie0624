#include "button.h"

// TODO: change this doc
/**
 * @brief Initializes the GPIO settings for buttons and LEDs.
 *
 * This function enables the clocks for GPIO ports G and A. It sets up GPIO pins 13 and 14 on port G as output push-pull for LEDs and sets up GPIO pin 0 on port A as input open-drain for button input.
 *
 * @param void This function does not take any parameters.
 * @return void This function does not return any values.
 */
void button_init(void)
{
	/* Enable GPIOG clock. */
	rcc_periph_clock_enable(RCC_GPIOG);

	/* Set GPIO13 (in GPIO port G) to 'output push-pull'. */
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);

	/* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);
    
    /*      Paddle controls 
     *                  UP      DOWN
     * Left paddle      PA0     PA1
     * Right paddle     PA5    PA7
     * */
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN,
            GPIO0 | GPIO1 | GPIO5 | GPIO7); 
}

