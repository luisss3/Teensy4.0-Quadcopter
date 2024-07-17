//variables for battery monitoring
float Voltage, Current, BatteryRemaining, BatteryAtStart;
float CurrentConsumed=0;
//1300mAh
float BatteryDefault=1300;

void battery_voltage() {
  //measure voltage and current
  Voltage=(float)analogRead(15)/62;
  //pin21 * ((1023 / 3.3 V) x 0.036 V/A)
  Current=(float)analogRead(21)*0.089;
}

void setup() {
  digitalWrite(5, HIGH);
  battery_voltage();
  if (Voltage > 8.3) { digitalWrite(5, LOW);
    BatteryAtStart=BatteryDefault; }
  else if (Voltage < 7.5) {
    BatteryAtStart=30/100*BatteryDefault ;}
  else { digitalWrite(5, LOW);

  //The following linear approximation between voltage and capacity is valid for 
  //the 1300 mAh - 2S battery:
  //Remaining capacity [%] = 82 · Voltage − 580
    BatteryAtStart=(82*Voltage-580)/100*
    BatteryDefault; 
  }
}

void loop() {
  battery_voltage();

  //Since each iteration k in our main loop takes 0.004 seconds, the consumed
  //current can be calculated with the formula CurrentConsumed(k)[mAh] = 
  //CurrentMeasured(k)[A]·((1000mA/A)/(3600s/h))·0.004s+CurrentConsumed(k−1)[mAh]
  CurrentConsumed= Current*1000*0.004/3600 + CurrentConsumed;
  BatteryRemaining=(BatteryAtStart-CurrentConsumed)/BatteryDefault*100;
  
  //turn on red LED if battery below 30%
  BatteryRemaining<=30 ? digitalWrite(5, HIGH) : digitalWrite(5, LOW);
}
