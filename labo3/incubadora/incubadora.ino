#include <PIDController.h>
PIDController pid;

void setup () 
{
  Serial.begin(9600);         	// Some methods require the Serial.begin() method to be called first
  pid.begin();               	// initialize the PID instance
  pid.tune(10, 10, 10);       	// Tune the PID, arguments: kP, kI, kD
  pid.limit(0, 255);           // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
  pinMode(3, OUTPUT);
  pid.setpoint(300);    		// The "goal" the PID controller tries to "reach"
}

void loop () {
  int sensorValue = analogRead(A0);         // Read the value from the sensor
  int output = pid.compute(sensorValue);    // Let the PID compute the value, returns the optimal output
  analogWrite(3, output);                   // Delay for 30 ms
  Serial.print("Valor del sensor: ");
  Serial.print(sensorValue);
  Serial.print("\n");
}

float simPlanta(float Q) {
    float h = 5;            // W/m2K coeficiente de conveccion termica para el Aluminio
    float Cps = 0.89;       // J/gC
    float area = 1E-4;      // m2 area por conveccion
    float masa = 10 ;       // g
    float Tamb = 25;        // Temperatura ambiente en C
    static float T = Tamb;  // Temperatura en C
    static uint32_t last = 0;
    uint32_t interval = 100;    // ms

    if(millis() - last >= interval)
    {
      last += interval;
      // 0-transferencia de calor
      T += Q*interval/1000/masa/Cps - (T - Tamb)*area*h;
    }
    return T;
}
