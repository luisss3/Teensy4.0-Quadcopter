#include <PulsePosition.h>

PulsePositionInput ReceiverInput(RISING);

//Channel info
float ReceiverValue[]={0,0,0,0,0,0,0,0};
int ChannelNumber=0;

float InputThrottle;

void read_receiver(){
  //Receive value from each channel of the receiver
  ChannelNumber = ReceiverInput.available();
  if (ChannelNumber>0){
    for (int i=1; i<=ChannelNumber;i++){
      ReceiverValue[i-1]=ReceiverInput.read(i);
    }
  }
  else{
    Serial.print("No TX detected.");
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  //receive PPM signal on pin 14
  ReceiverInput.begin(14);

  //250Hz PWM frequency as per ESC. PWM resolution of 2^12 for better control
  analogWriteFrequency(1,250);
  analogWriteResolution(12);
  delay(250);

  //don't start motor unless throttle stick is in a low position
  while (ReceiverValue[2] < 1020 || ReceiverValue[2] > 1050) {
    read_receiver();
    delay(4);
  }
}

void loop() {
  read_receiver();
  InputThrottle = ReceiverValue[2];
  Serial.print(" Throttle [µs]: ");
  Serial.print(ReceiverValue[2]);
  //2^12-1=4095; 250Hz=4000 µs. Divide full pwm by total time: 4095/4000 = 1.024
  analogWrite(1,1.024*InputThrottle);

}
