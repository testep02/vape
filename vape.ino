#define COIL_OUT_PIN      10
#define PULSE_SELECT_PIN  7
#define BATTERY_MID       A0
#define DEFAULT_LED       13

double adcBitValue = 0.0048875;
double batteryVoltage = 0;
double batteryMinVoltage = 3.2;
int batteryLedBlinkOn = 500;
int batteryLedBlinkOff = 500;

/*************************  BABY BEAST SETTINGS  *************************/
/*
int coilPower = 50;
int maxPulse = 60;
int minPulse = 20;
int pulseDelay = 5;
int pulseSpacing = 5;
*/

/***************************  TFV12 SETTINGS  ***************************/
int coilPower = 200;
int maxPulse = 150;
int minPulse = 75;
int pulseDelay = 4;
int pulseSpacing = 4;

void setup() {
  pinMode(COIL_OUT_PIN, OUTPUT);
  pinMode(PULSE_SELECT_PIN, INPUT);
  pinMode(DEFAULT_LED, OUTPUT);
  digitalWrite(DEFAULT_LED, LOW);

  // TESTING
  Serial.begin(9600);
}

void loop() {  
  if(isBatteryDead())
  {
    blinkDefaultLed();
  }
  else
  {
    fireCoil();
  }

  // TESTING
  //Serial.println(batteryVoltage);
}

boolean isBatteryDead() {
  batteryVoltage = analogRead(BATTERY_MID) * adcBitValue;

  if(batteryVoltage < batteryMinVoltage) {
    return true;
  }
  else {
    return false;
  }
}

void fireCoil() {
  if(isPulseSelected()) {
    pulseCoil();
  }
  else {
    steadyCoil();
  }
}

void steadyCoil() {
  analogWrite(COIL_OUT_PIN, coilPower);
}

void pulseCoil() {
  countUp();
  countDown();
  delay(pulseSpacing);
}

boolean isPulseSelected() {
  int pulsePinValue = digitalRead(PULSE_SELECT_PIN);
  if(pulsePinValue == 0) {
    return false;
  }
  else {
    return true;
  }
}

void countUp()
{
  for(int i = minPulse; i <= maxPulse; i++)
  {
    analogWrite(COIL_OUT_PIN, i);
    delay(pulseDelay);
  }

  return;
}

void countDown()
{
  for(int i = maxPulse; i >= minPulse; i--)
  {
    analogWrite(COIL_OUT_PIN, i);
    delay(pulseDelay);
  }
}

void blinkDefaultLed()
{
  digitalWrite(DEFAULT_LED, HIGH);
  delay(batteryLedBlinkOn);
  digitalWrite(DEFAULT_LED, LOW);
  delay(batteryLedBlinkOff);
}
