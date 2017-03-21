//int coilOutPin = 10;
//int pulsePin = 7;

#define COIL_OUT_PIN      10
#define PULSE_SELECT_PIN  7
#define BATTERY_MID       A0
#define DEFAULT_LED       13

//#define COIL_DETECT_PIN  
// Baby Beast
#define COIL_POWER        50
//TFV12 Low
//#define COIL_POWER        150
//TFV12 High
//#define COIL_POWER        200

// Baby Beast Pulse
#define MAX_PULSE         50
#define MIN_PULSE         10

// TFV12 Pulse
//#define MAX_PULSE         150
//#define MIN_PULSE         75

int coilPwm = 0;
int maxPulse = 60;
int minPulse = 20;
int pulseDelay = 5;
int pulseSpacing = 5;
double batteryVoltage = 0;

void setup() {
  pinMode(COIL_OUT_PIN, OUTPUT);
  pinMode(PULSE_SELECT_PIN, INPUT);
  pinMode(DEFAULT_LED, OUTPUT);
  digitalWrite(DEFAULT_LED, LOW);

  // TESTING
  Serial.begin(9600);
}

void loop() {
  batteryVoltage = analogRead(BATTERY_MID) * 0.0048875;
  
  if((batteryVoltage >= 3.2))
  {
    int pulsePinValue = digitalRead(PULSE_SELECT_PIN);
    if(pulsePinValue == 0) {
      analogWrite(COIL_OUT_PIN, COIL_POWER);
    } else {
      pulse();
    }
  }
  else
  {
    blinkDefaultLed();
  }

  // TESTING
  //Serial.println(batteryVoltage);
}

void pulse() {
  countUp();
  countDown();
  delay(pulseSpacing);
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
  delay(500);
  digitalWrite(DEFAULT_LED, LOW);
  delay(500);
}
