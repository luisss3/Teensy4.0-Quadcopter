#define orangeLED 13
#define redLED 5
#define greenLED 6

void setup() {
  pinMode(orangeLED, OUTPUT);
  digitalWrite(orangeLED, HIGH);

  ledSensorCalibrationAcknowledgement();
}
void loop() { 
}

void ledSensorCalibrationAcknowledgement(){

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  digitalWrite(redLED, HIGH);
  delay(4000);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
}