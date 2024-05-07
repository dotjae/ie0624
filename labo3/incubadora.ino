#include <PCD8544.h>   // https://github.com/carlosefr/pcd8544/tree/1.4.3
#include <PID_v1_bc.h> // https://github.com/drf5n/Arduino-PID-Library

double Setpoint, Entrada, Salida, x;
//double Kp = 2, Ki = 5, Kd = 1;
//double Kp = 15, Ki = .1, Kd = 3;
double Kp = 255, Ki = .0, Kd = 0; 
PID myPID(&Entrada, &Salida, &Setpoint, Kp, Ki, Kd, P_ON_E, DIRECT);
static PCD8544 lcd;

int LCDSwitch = 0;
const int OUT_PIN = 10;  				
const int SETPOINT_PIN = A1;   	
const int LCD_ENABLE = 2;
const int HI = 8;
const int OP = 9;
const int LO = 10;
const int SERIAL_ENABLE_PIN = 13;

void setup()
{
	Serial.begin(115200);
	// PID config
  	myPID.SetOutputLimits(-128, 128);		// PID output in range 0-255
  	Setpoint = 36;					// 36 celsius as starting setpoint
  	myPID.SetMode(AUTOMATIC);
  	Entrada = simPlant(20.0 * (int)25/128); 	// start plant simulation at room temperature
  	Serial.println("Referencia Temperatura SalidaPID CalorQ");
	
	// LCD config
	pinMode(LCD_ENABLE, INPUT);
	lcd.begin();
	lcd.clear();
	
	// LED alarms config
	pinMode(HI, OUTPUT);
	pinMode(OP, OUTPUT);
	pinMode(LO, OUTPUT);

  // PC communication config
  pinMode(SERIAL_ENABLE_PIN, INPUT);
}


void loop()
{
	float TempWatts = (int)Salida * 20.0 / 128;	// actuator
	float TempInc = simPlant(TempWatts); 		// plant simulation with desired heat input
	Entrada = TempInc;  					

	if (myPID.Compute())
	{
		x = analogRead(SETPOINT_PIN) / 8;		// read setpoint from pot in range 0-255
		Setpoint = map(x,0,128,20,80);		    // setpoint normalized to 30-42 celsius range
	}							
	
	LCDSwitch = digitalRead(LCD_ENABLE);
	
	// LCD screen switch
	if (LCDSwitch == 1)
	{
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
	else if (LCDSwitch == 0)
	{
		lcd.clear();
	}
	
	// LED alarms
	if (TempInc < 30)
	{
		digitalWrite(HI, LOW);
		digitalWrite(OP, LOW);
		digitalWrite(LO, HIGH);
	}
	else if (TempInc > 30 && TempInc < 42)
	{
		digitalWrite(HI, LOW);
		digitalWrite(OP, HIGH);
		digitalWrite(LO, LOW);
	}
	else if (TempInc > 42)
	{
		digitalWrite(HI, HIGH);
		digitalWrite(OP, LOW);
		digitalWrite(LO, LOW);
	}


	// Check if serial communication is enabled
	if (digitalRead(SERIAL_ENABLE_PIN) == HIGH) {
		Serial.print(Setpoint);
		Serial.print(",");
		Serial.print(Salida);
		Serial.print(",");
		Serial.print(Entrada);
		Serial.println("");
	}
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
