#include "labo4.h"

void lcd_slope(uint8_t temperature, degree reading, uint16_t battery, bool USART_enable)
{
    char buf[21];

    // interface
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

    gfx_setCursor(15, 175);
    if (USART_enable)
        gfx_puts("COMM SERIAL: ON");
    else 
        gfx_puts("COMM SERIAL: OFF");

    // Update screen
    lcd_show_frame();   
}

// Ojo con el buffer str
void console_puts_slope(data xyzData)
{
    char buf[8];

    // console_puts("\nAngulos:\n");
    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.x);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.y);
    console_puts(buf);
    console_puts("\t");
    snprintf(buf, sizeof(buf), "%3.3f", xyzData.angle.z);
    console_puts(buf);
    console_puts("\n");
}

void console_puts_all(data xyzData, uint8_t temperature, uint16_t battery)
{
    char buf[21];
    // int TEST = 0;

    // console_puts("\nAngulos:\n");
    // snprintf(buf, sizeof(buf), "%d", TEST);
    // console_puts(buf);
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

void console_puts_temperature(uint8_t temperature)
{
    char buf[8];

    // console_puts("\nTemperatura:\n");
    snprintf(buf, sizeof(buf), "%d", temperature);
    console_puts(buf);
    console_puts("\n");
    console_puts("\t");

}

void console_puts_battery(uint16_t battery)
{
    char buf[8];

    // console_puts("\nBateria:\n");
    snprintf(buf, sizeof(buf), "%d", battery);
    console_puts(buf);
    console_puts("\n");
    console_puts("\t");

}


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

void delay(void)
{
    for (int i = 0; i < 6000000; i++) __asm__ ( "nop" );
}

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

void five_degree_alert(data xyzData)
{
        if (xyzData.angle.x > 5 || xyzData.angle.y > 5 || xyzData.angle.z > 5)
        {
		    gpio_toggle(GPIOG, GPIO13);
        }
}

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
