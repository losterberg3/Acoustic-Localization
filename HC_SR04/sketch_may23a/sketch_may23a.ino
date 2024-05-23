#include <arduinoFFT.h>

#include <vector>
void setup() {
  // put your setup code here, to run once:
  int sampling_rate,T;
  // int T_ref;
  int size_samples = sampling_rate*T; // sampling_rate from the receiver specs and T is a dependent value.
  //int size_reference = sampling_rate*T_ref; // T_ref is time length of the reference signal
  vector<float> samples[size_samples];
  vector<float> ref_signal[size_samples];
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // 
}
