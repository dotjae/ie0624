#include "labo4.h"

/**
 * @brief Displays temperature, battery level, and sensor readings on the LCD.
 *
 * This function sets up the LCD screen interface, draws shapes and text for displaying the current temperature, battery level, and sensor readings. It also shows the status of serial communication.
 *
 * @param temperature The current temperature value to display.
 * @param reading The current readings of the XYZ axis.
 * @param battery The current battery level to display.
 * @param USART_enable Boolean indicating whether serial communication is enabled.
 * @return void This function does not return any values.
 */
void lcd_slope(uint8_t temperature, degree reading, uint16_t battery, bool USART_enable)
{
    char buf[21];

    // Interface 
    gfx_fillScreen(LCD_BLACK);
    gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_WHITE);
    gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
    gfx_fillCircle(20, 250, 10, LCD_RED);
    gfx_fillCircle(120, 250, 10, LCD_GREEN);
    gfx_fillCircle(220, 250, 10, LCD_BLUE);
    
    // Title
    gfx_setTextSize(2);
    gfx_setCursor(35, 25);
    gfx_puts("MONITOR DE");
    gfx_setCursor(35, 50);
    gfx_puts("PENDIENTES");

    // XYZ axis, temperature, battery level
    gfx_setTextSize(1);
    gfx_setCursor(15, 100);
    gfx_puts("BATERIA:");
    gfx_setCursor(105, 100);
    sprintf(buf, "%d", battery);
    gfx_puts(buf);

    gfx_setCursor(15, 115);
    gfx_puts("TEMPERATURA: ");
    gfx_setCursor(105, 115);
    sprintf(buf, "%3d", temperature);
    gfx_puts(buf);

    gfx_setCursor(15, 130);
    gfx_puts("EJE X: ");
    gfx_setCursor(65, 130);
    sprintf(buf, "%3f", reading.x);
    gfx_puts(buf);

    gfx_setCursor(15, 145);
    gfx_puts("EJE Y: ");
    gfx_setCursor(65, 145);
    sprintf(buf, "%3f", reading.y);
    gfx_puts(buf);

    gfx_setCursor(15, 160);
    gfx_puts("EJE Z: ");
    gfx_setCursor(65, 160);
    sprintf(buf, "%3f", reading.z);
    gfx_puts(buf);

    // Serial communication
    gfx_setCursor(15, 175);
    if (USART_enable)
        gfx_puts("COMM SERIAL: ON");
    else 
        gfx_puts("COMM SERIAL: OFF");

    // Update screen
    lcd_show_frame();   
}

/**
 * @brief Sends all sensor data to the console.
 *
 * This function formats and sends the XYZ axis readings, temperature, and battery level to the console.
 *
 * @param xyzData The current readings of the XYZ axis.
 * @param temperature The current temperature value.
 * @param battery The current battery level.
 * @return void This function does not return any values.
 */
void console_puts_all(data xyzData, uint8_t temperature, uint16_t battery)
{
    char buf[21];

    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.x);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.y);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.z);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%3d", temperature);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%4d", battery);
    console_puts(buf);
    console_puts("\n");
}

/**
 * @brief Toggles USART communication and sends data if enabled.
 *
 * This function checks if the button is pressed to toggle the USART communication state. If enabled, it sends all sensor data to the console.
 *
 * @param xyzData The current readings of the XYZ axis.
 * @param temperature The current temperature value.
 * @param battery The current battery level.
 * @param USART_enable Boolean indicating whether serial communication is enabled.
 * @return bool The updated state of the USART communication.
 */
bool console_usart_enable(data xyzData, uint8_t temperature, uint16_t battery, bool USART_enable)
{
    if (gpio_get(GPIOA, GPIO0))
    {
        USART_enable = !USART_enable;
        msleep(10);
    }
    if (USART_enable)
    {
        console_puts_all(xyzData, temperature, battery);
    }

    return USART_enable;
}

/**
 * @brief Introduces a delay in the program execution.
 *
 * This function implements a simple delay using a for loop and NOP instructions.
 *
 * @param void This function does not take any parameters.
 * @return void This function does not return any values.
 */
void delay(void)
{
    for (int i = 0; i < 6000000; i++) __asm__ ( "nop" );
}

/**
 * @brief Integrates the reading of a single axis over time.
 *
 * This function calculates the integral of the reading of a single axis over time to estimate the angle.
 *
 * @param reading The current reading of the axis.
 * @param angle The current angle of the axis.
 * @param lastSampleTime The time of the last sample.
 * @return integral The integrated angle and updated sample time.
 */
integral integrate_axis(double reading, double angle, double lastSampleTime)
{
    integral speed_integral;

    if (fabs(reading) > 1 && (mtime() - lastSampleTime) > SAMPLE_TIME) 
    {
        double deltaT = ((double)mtime() - lastSampleTime) / 1000.0; 
        angle += (double)fabs(reading) * deltaT;
        lastSampleTime = mtime();
    }
    
    speed_integral.angle = angle;
    speed_integral.lastSampleTime = lastSampleTime;
    return speed_integral;
}

/**
 * @brief Integrates the readings of all XYZ axes over time.
 *
 * This function calculates the integral of the readings of all XYZ axes over time to estimate the angles.
 *
 * @param xyzData The current readings and angles of the XYZ axes.
 * @return data The updated readings and angles of the XYZ axes.
 */
data integrate_xyz(data xyzData)
{
    integral xIntegral;
    integral yIntegral;
    integral zIntegral;

    xIntegral = integrate_axis(xyzData.reading.x, xyzData.angle.x, xyzData.lastTime.x); // x integration
    yIntegral = integrate_axis(xyzData.reading.y, xyzData.angle.y, xyzData.lastTime.y); // y integration
    zIntegral = integrate_axis(xyzData.reading.z, xyzData.angle.z, xyzData.lastTime.z); // z integration
    
    xyzData.angle.x = xIntegral.angle;
    xyzData.lastTime.x = xIntegral.lastSampleTime;

    xyzData.angle.y = yIntegral.angle;
    xyzData.lastTime.y = yIntegral.lastSampleTime;

    xyzData.angle.z = zIntegral.angle;
    xyzData.lastTime.z = zIntegral.lastSampleTime;

    return xyzData;
}

/**
 * @brief Toggles an alert if any axis exceeds a 5-degree angle.
 *
 * This function checks if any of the XYZ axis angles exceed 5 degrees and toggles a GPIO pin to signal an alert.
 *
 * @param xyzData The current angles of the XYZ axes.
 * @return void This function does not return any values.
 */
void five_degree_alert(data xyzData)
{
        if (xyzData.angle.x > 5 || xyzData.angle.y > 5 || xyzData.angle.z > 5)
        {
		    gpio_toggle(GPIOG, GPIO13);
        }
}

/**
 * @brief Toggles an alert if the battery level is low.
 *
 * This function checks if the battery level is below 20% and toggles a GPIO pin to signal a low battery alert.
 *
 * @param battery The current battery level.
 * @return void This function does not return any values.
 */
void low_battery_alert(uint16_t battery)
{
        if (battery < 20)
        {
		    gpio_toggle(GPIOG, GPIO14);
        }
        else {
            gpio_clear(GPIOG, GPIO14);
        }
}
