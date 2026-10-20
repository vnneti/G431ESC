#include <SimpleFOC.h>

// BLDC Motor Instanz (MT2213 hat typischerweise 7 Polpaare)
BLDCMotor motor = BLDCMotor(7);

// KORRIGIERTE PIN-NAMEN FÜR DEN AKTUELLEN STM32-CORE:
BLDCDriver6PWM driver = BLDCDriver6PWM(A_PHASE_UH, A_PHASE_UL, A_PHASE_VH, A_PHASE_VL, A_PHASE_WH, A_PHASE_WL);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("B-G431B-ESC1 SimpleFOC Test gestartet!");

  // Treiber-Konfiguration
  driver.voltage_power_supply = 12.0; // An dein Test-Netzteil anpassen (z.B. 12V)
  driver.init();
  
  motor.linkDriver(&driver);

  // Sicherheitseinstellungen für den ersten Test
  motor.voltage_limit = 3;   // Volt
  motor.velocity_limit = 20; // rad/s

  // Open-Loop Modus zum Testen ohne Sensor
  motor.controller = MotionControlType::velocity_openloop;

  motor.init();
  Serial.println("Motor initialisiert.");
}

void loop() {
  // Lässt den Motor mit konstanter Geschwindigkeit drehen (10 rad/s)
  motor.move(10.0);
}