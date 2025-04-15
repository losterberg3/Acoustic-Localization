/**
 * Routine to send a radio signal and measure the latency in microseconds
 * purpose is to see how repeatable the specified 7ms latency is
 * */

// https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/
// needs the RadioHead package to use the radio

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
int start, end; 

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");

    const char *msg = "chirp";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    start = micros();
}

void loop()
{
    //wait for the sent message to be recieved 
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      end = micros();
      Serial.print("delay us: ");
      Serial.println(end-start); 

      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);  
       
    }
}




