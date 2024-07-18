void setup() {
  // put your setup code here, to run once:
Serial.begin(2000000); //check baud rate
ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
//ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8, 153846 hz theoretically
ADCSRA |= bit (ADPS2);                               //  16, 76923 hz theoretically
//ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32, 38462 hz theoretically
//ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64, 19231 hz theoretically
//ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128, 9615 hz theoretically
}

void loop() {
  // put your main code here, to run repeatedly:
delay(3000); //allow enough time to click run on matlab
//Serial.println(micros()); //I found that it actually starts sampling at 3.000016 seconds.
while (micros()<=4000016){ //sampling for 1 second
  Serial.write(analogRead(0)/4); //writing the sampled value to the port, dividing by 4 to make an 8 bit value
}
delay(60000);
}


