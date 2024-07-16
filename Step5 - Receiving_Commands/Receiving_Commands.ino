#include <PulsePosition.h>

PulsePositionInput ReceiverInput(RISING);

//Channel info
float ReceiverValue[]={0,0,0,0,0,0,0,0};
int ChannelNumber=0;

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
  ReceiverInput.begin(14);
}

void loop() {
  read_receiver();
  Serial.print("Number of channels: ");
  Serial.print(ChannelNumber);
  Serial.print(" Roll [µs]: ");
  Serial.print(ReceiverValue[0]);
  Serial.print(" Pitch [µs]: ");
  Serial.print(ReceiverValue[1]);
  Serial.print(" Throttle [µs]: ");
  Serial.print(ReceiverValue[2]);
  Serial.print(" Yaw [µs]: ");
  Serial.println(ReceiverValue[3]);
  delay(50);
}
