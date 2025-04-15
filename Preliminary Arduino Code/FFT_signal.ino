#include "Arduino.h"
#include "Reference_Signal.h"
#include <arduinoFFT.h>


#define SAMPLES 512  // Must be a power of 2
#define SAMPLING_FREQUENCY 2048  // Hz, must be less than 10000 and power of 2 due to ADC limitations

unsigned long microseconds;
unsigned int sampling_period_us;
double soundSamples[SAMPLES];
double referenceSignal[SAMPLES];
double vReal[SAMPLES];
double vImag[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY); // FFT Object to perform FFT operations
const int window = 2048; // 2^11
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  // Get Reference Signal from external header file.

  
  // Multiply FFT(samples) and FFT(ref_signal).
  // Change it back to the time domain.
  // Find peak in the time domain.
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Collect the samples vector from the microphone
  double time = findPeakTime();
  double dist = 34300*time;
  Serial.println("Distance:");
  Serial.println(dist);

  delay(3000);  // Repeat every second
}

double findPeakTime(){
  for (int i =0; i<SAMPLES; i++){
    microseconds = micros();
    double val = analogRead(A0);
    soundSamples[i] = val; // Read from the electret microphone
    while(micros() < microseconds + sampling_period_us){
      // Waits to collect the next sample.
    }
  }

  // Perform FFT on the soundSamples
  for(int i=0; i< SAMPLES; i++){
    vReal[i] = soundSamples[i];
    vImag[i] = 0;
  }

  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);

  double soundReal[SAMPLES];
  double soundImag[SAMPLES];
  memcpy(soundReal,vReal,SAMPLES);
  memcpy(soundImag,vImag,SAMPLES);

  // Perform FFT on the ref Signal
  for(int i=0; i< SAMPLES; i++){
    vReal[i] = referenceSignal[i];
    vImag[i] = 0;
  }

  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);

  // Multiply the FFT results
  for(int i = 0; i<SAMPLES; i++){
    double real = soundReal[i]*vReal[i] - soundImag[i]*vImag[i];
    double imag = soundReal[i]*vImag[i] + soundImag[i]*vReal[i];
    soundReal[i] = real;
    soundImag[i] = imag;
  }

  // Perform inverse FFT
  FFT.compute(soundReal, soundImag, SAMPLES, FFT_REVERSE);
  FFT.complexToMagnitude(soundReal, soundImag, SAMPLES);

  // Find peak in the time domain
  double peak = -1;
  int peakIndex = -1;
  for (int i = 0; i < SAMPLES; i++) {
    if (soundReal[i] > peak) {
      peak = soundReal[i];
      peakIndex = i;
    }
  }

  double peakTime = peakIndex * (1.0 / SAMPLING_FREQUENCY);
  return peakTime;
}
