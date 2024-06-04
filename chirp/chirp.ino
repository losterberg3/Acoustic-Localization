#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

// Define chirp signal parameters
float startFreq = 1000; // Start frequency in Hz (20 kHz)
const float endFreq = 1500;   // End frequency in Hz (40 kHz)
const unsigned long duration = 1000; // Duration of the chirp in milliseconds
const int amplitude = 127;     // Amplitude of the chirp signal. Did not really matter for piezoelectric


unsigned long startTime;

// Define Oscil object for sine wave generation
Oscil<2048,32768> oscil(SIN2048_DATA);

const int transducerPin = 11; // Digital output pin connected to the transducer

void setup() {
  pinMode(transducerPin, OUTPUT);
  startMozzi(128); // 128 is the control rate - how often updates happen
  oscil.setFreq(startFreq);
  startTime = millis();
}

void updateControl(){
  float freq = min(endFreq,startFreq+ (millis()-startTime)*(endFreq - startFreq)/duration);
  oscil.setFreq(freq);
}

int updateAudio(){
  return oscil.next();
}

// void generateChirp() {
//   // Calculate time parameter [0, 1]
//   float t = float(millis() - startTime) / duration;

//   // Generate chirp signal using linear interpolation between startFreq and endFreq
//   float frequency = startFreq + t * (endFreq - startFreq);

//   // Generate sine wave with the calculated frequency and amplitude
//   int16_t output = amplitude * oscil.next();

//   // Output the signal to the transducer
//   analogWrite(transducerPin,output); // output should be between 0 (low) and 255 (high). Use Duty Cycle to adjust.

//   audioHook(); // Ensure Mozzi's audio processing is running
// }

void loop() {
  analogWrite(transducerPin,updateAudio());
  audioHook();
}
