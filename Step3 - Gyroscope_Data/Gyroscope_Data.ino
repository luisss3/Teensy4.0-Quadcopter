#include <Wire.h>
#include <WireIMXRT.h>
#include <WireKinetis.h>

float RateRoll, RatePitch, RateYaw;

//start I2C communication with slave adress 0x68 MPU6050

void gyro_signals(){
  // writes to configuration register 0x1A and sets Digital Low Pass Filter (DLPF)
  // to a bandwidth of 10Hz to account for motor interference
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();

  // writes to Gyroscope configuration register 0x1B and sets the full scale range
  // of the gyroscope outputs to 500 degrees per second
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  //request data from gyroscope data output registers.
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t GyroX = Wire.read()<<8 | Wire.read();
  int16_t GyroY = Wire.read()<<8 | Wire.read();
  int16_t GyroZ = Wire.read()<<8 | Wire.read();
  //divide output by LSB Sensitivity 65.6 LSB per degree per second
  RateRoll  = (float)GyroX/65.5;
  RatePitch = (float)GyroY/65.5;
  RateYaw   = (float)GyroZ/65.5;
}

void setup(){
  Serial.begin(57600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  //setup I2C 
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  //start gyro in power mode
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop(){
  gyro_signals();
  Serial.print("\nRoll rate [°/s]= ");
  Serial.print(RateRoll);
  Serial.print("\nPitch rate [°/s]= ");
  Serial.print(RatePitch);
  Serial.print("\nYaw rate [°/s]= ");
  Serial.print(RateYaw);
  Serial.print("\n");
  delay(50);
}