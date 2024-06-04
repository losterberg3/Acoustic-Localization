// ReferenceSignal.h
#ifndef REFERENCE_SIGNAL_H
#define REFERENCE_SIGNAL_H

#define REFERENCE_SIGNAL_SIZE 128  // Define the size of the reference signal
#define SAMPLING_FREQUENCY 1000    // Sampling frequency in Hz

const double T = 0.125;  // Duration of the chirp signal in seconds
const double f0 = 50.0;  // Start frequency in Hz
const double f1 = 300.0;  // End frequency in Hz

// Generate the chirp signal
const double referenceSignal[REFERENCE_SIGNAL_SIZE] = [] {
  double signal[REFERENCE_SIGNAL_SIZE];
  for (int i = 0; i < REFERENCE_SIGNAL_SIZE; i++) {
    double t = (double)i / SAMPLING_FREQUENCY;  // Time variable
    double instantaneousFreq = f0 + (f1 - f0) * (t / T);
    signal[i] = sin(2.0 * PI * (f0 * t + (f1 - f0) * t * t / (2.0 * T)));
  }
  return signal;
}();

#endif
