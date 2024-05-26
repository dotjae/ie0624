#include "labo4.h"

void lcd_slope(uint8_t temperature, mems reading)
{
    char buf[8];

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
    gfx_puts("BATERIA: 00%");

    gfx_setCursor(15, 115);
    gfx_puts("TEMPERATURA: ");
    gfx_setCursor(105, 115);
    sprintf(buf, "%3d", temperature);
    gfx_puts(buf);

    gfx_setCursor(15, 130);
    gfx_puts("EJE X: ");
    gfx_setCursor(65, 130);
    sprintf(buf, "%3d", reading.x);
    gfx_puts(buf);

    gfx_setCursor(15, 145);
    gfx_puts("EJE Y: ");
    gfx_setCursor(65, 145);
    sprintf(buf, "%3d", reading.y);
    gfx_puts(buf);

    gfx_setCursor(15, 160);
    gfx_puts("EJE Z: ");
    gfx_setCursor(65, 160);
    sprintf(buf, "%3d", reading.z);
    gfx_puts(buf);

    gfx_setCursor(15, 175);
    gfx_puts("COMM SERIAL: OFF");
    
    // Update screen
    lcd_show_frame();   
}

void console_puts_slope(data xyzData)
{
    console_puts("\nAngulos:\n");
    snprintf(str, sizeof(str), "%3.3f", xyzData.angle.x);
    console_puts(str);
    console_puts("\t");
    snprintf(str, sizeof(str), "%3.3f", xyzData.angle.y);
    console_puts(str);
    console_puts("\t");
    snprintf(str, sizeof(str), "%3.3f", xyzData.angle.z);
    console_puts(str);
    console_puts("\n");
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
