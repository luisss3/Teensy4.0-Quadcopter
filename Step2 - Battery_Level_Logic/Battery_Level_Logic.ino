#define orangeLED 13
#define redLED 5
#define greenLED 6

float voltage;

void setup() {
  pinMode(orangeLED, OUTPUT);
  pinMode(15, INPUT);
  digitalWrite(orangeLED, HIGH);

  Serial.begin(57600);
  //ledSensorCalibrationAcknowledgement();
}
void loop() { 
  battery_voltage();
  Serial.print("Raw ADC Value: ");
  Serial.print(analogRead(15));
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  delay(50);
}

void battery_voltage() {
  // Read the analog value from pin 15
  int analogValue = analogRead(15);
  
  // Calculate the voltage at the ADC pin
  float V_adc = (analogValue / 1023.0) * 3.3;
  
  // Calculate the input voltage using the voltage divider formula
  voltage = V_adc * 5.5;
}

void ledSensorCalibrationAcknowledgement(){

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  
  digitalWrite(redLED, HIGH);
  delay(4000);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
}