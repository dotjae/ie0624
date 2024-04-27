#include <PCD8544.h>
#include <PID_v1_bc.h> // https://github.com/drf5n/Arduino-PID-Library

double Setpoint, Entrada, Salida, x;
//double Kp = 2, Ki = 5, Kd = 1;
//double Kp = 17, Ki = .1, Kd = 2;
double Kp = 255, Ki = .0, Kd = 0; 
PID myPID(&Entrada, &Salida, &Setpoint, Kp, Ki, Kd, P_ON_E, DIRECT);

const int OUT_PIN = 10;  				
const int SETPOINT_PIN = A1;   	
static PCD8544 lcd;

void setup()
{
	Serial.begin(115200);
  	myPID.SetOutputLimits(0, 255);		// PID output in range 0-255
  	Setpoint = 36;					// 36 celsius as starting setpoint
  	myPID.SetMode(AUTOMATIC);
  	Entrada = simPlant(20.0 * (int)25/255); 	// start plant simulation at room temperature
  	Serial.println("Referencia Temperatura SalidaPID CalorQ");

	lcd.begin();
	lcd.clear();
}

void loop()
{
	float TempWatts = (int)Salida * 20.0 / 255;	// actuator
	float TempInc = simPlant(TempWatts); 		// plant simulation with desired heat input
	Entrada = TempInc;  					

	if (myPID.Compute())
	{
		x = analogRead(SETPOINT_PIN) / 4;		// read setpoint from pot in range 0-255
		Setpoint = 4 * x/85 + 30;				// setpoint normalized to 30-42 celsius range
	}							
	
	lcd.setCursor(0,0);
	lcd.print("Temp de Op: ");
	lcd.setCursor(0,1);
	lcd.print(TempInc);
	lcd.setCursor(30,1);
	lcd.print(" Celsius");
	lcd.setCursor(0,2);
	lcd.print("Senal de Ctrl:");
	lcd.setCursor(0,3);
	lcd.print(TempWatts);
	lcd.setCursor(30,3);
	lcd.print(" Watts");
	lcd.setCursor(0,4);
	lcd.print("Temp deseada:");
	lcd.setCursor(0,5);
	lcd.print(Setpoint);
	lcd.setCursor(30,5);
	lcd.print(" Celsius");
}

float simPlant(float Q) 
{ 
	// heat input in W (or J/s)
	// simulate a 1x1x2cm aluminum block with a heater and passive ambient cooling
	// float C = 237; // W/mK thermal conduction coefficient for Al
	float h = 5; 		// W/m2K thermal convection coefficient for Al passive
	float Cps = 0.89; 	// J/g°C
	float area = 1e-4; 	// m2 area for convection
	float mass = 10 ; 	// g
	float Tamb = 25; 	// °C
	static float T = Tamb;	// °C
	static uint32_t last = 0;
	uint32_t interval = 100; 	// ms

	if (millis() - last >= interval) 
	{
		last += interval;
		// 0-dimensional heat transfer
		T = T + Q * interval / 1000 / mass / Cps - (T - Tamb) * area * h;
	}
	return T;
}