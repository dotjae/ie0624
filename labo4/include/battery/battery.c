#include "battery.h"
#include <libopencm3/stm32/rcc.h>

void adc_setup(void)
{
	rcc_periph_clock_enable(RCC_ADC1);
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO5);
	adc_power_off(ADC1);
	adc_disable_scan_mode(ADC1); 
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);
	adc_power_on(ADC1);
}

uint16_t read_adc_naiive(uint8_t channel)
{
	uint8_t channel_array[16];
	channel_array[0] = channel;
	adc_disable_external_trigger_regular(ADC1);
	adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	uint16_t reg16 = adc_read_regular(ADC1);
	return reg16;
}


double get_battery(uint8_t channel)
{
    return (double)read_adc_naiive(channel) * (9.0/4096.0);
}

/**
 * @brief Toggles an alert if the battery level is low.
 *
 * This function checks if the battery level is below 20% and toggles a GPIO pin to signal a low battery alert.
 *
 * @param battery The current battery level.
 * @return void This function does not return any values.
 */
void low_battery_alert(double battery)
{
        if (battery < 7.0)
        {
		    gpio_toggle(GPIOG, GPIO14);
        }
        else {
            gpio_clear(GPIOG, GPIO14);
        }
}
