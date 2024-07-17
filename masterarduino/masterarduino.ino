int val=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); //check baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
delay(3000); //allow enough time to click run on matlab
while (millis()<=4000){ //sampling for 1 second
  val=analogRead(0)-380; //converting analog value to an 8-bit integer
  Serial.write(val); //writing the sampled value to the port
}
delay(60000);
}
