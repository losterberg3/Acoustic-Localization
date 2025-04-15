#include <fftw3.h>
#include <iostream>
#include <cmath>


int main() {

int shift=500; // how much signals are shifted by
int N=45000;  // Size of the FFT, and sampling rate in hz
double cl=0.5; //chirplength in seconds
int sf=500; // start frequency of the chirp
int ef=1200; // end frequency of the chirp
double t;
double f;
double soundSamples[N]; // the sampled sound signal
double referenceSignal[N]; // the reference chirp signal we'll be comparing to, created by the speaker

for (int i=0;i<N;++i){ // adding points to the reference signal, based on defined parameters above
    if (i<(cl*N)){
        t=static_cast<double>(i)/(N-1); 
        f=(t*t*(ef-sf)/cl/2)+(t*sf);
        referenceSignal[i]=sin(f*2*M_PI); //defining pi here 
    } else {
        referenceSignal[i]=0;
    }
}

// in this case, no data has been sampled and instead we are using a simulated chirp
for (int i=0;i<N;++i){ // adding to the sampled signal (just the ref signal shifted over)
    if (i<shift){
        soundSamples[i]=0;
    } else if (i>=((cl*N)+shift)) {
        soundSamples[i]=0;
    } else {
        t=static_cast<double>(i-shift)/(N-1);
        f=(t*t*(ef-sf)/cl/2)+(t*sf);
        soundSamples[i]=sin(f*2*M_PI); 
    } 
}
// now performing the cross-correlation using fftw
    
    fftw_complex refout[N];  // Output reference array (complex numbers)
    fftw_complex sampout[N]; // Output sampled array 
    fftw_complex out[N];
    double spectrum[N];
    
    fftw_plan plan_forwardsamp = fftw_plan_dft_r2c_1d(N, soundSamples, sampout, FFTW_ESTIMATE);
    fftw_plan plan_forwardref = fftw_plan_dft_r2c_1d(N, referenceSignal, refout, FFTW_ESTIMATE);
    fftw_plan plan_backward = fftw_plan_dft_c2r_1d(N, out, spectrum, FFTW_ESTIMATE);

    // Perform FFT
    fftw_execute(plan_forwardsamp);
    fftw_execute(plan_forwardref);

    // Multiply by complex conjugate
    for (int i = 0; i < N; ++i) {
        refout[i][1] = -refout[i][1];  // complex conjugate
        out[i][0]=(sampout[i][0]*refout[i][0])-(sampout[i][1]*refout[i][1]);
        out[i][1]=(sampout[i][0]*refout[i][1])+(sampout[i][1]*refout[i][0]);
    }

    int max=0;
    int index=0;
    double tof=0;
    double distance=0;

    // Perform IFFT
    fftw_execute(plan_backward);

    for (int i=0; i<N; ++i){ // finding the spike in the cross-correlated signal
        if (spectrum[i]>max){
            max=spectrum[i];
            index=i;
        }
    }

    tof=static_cast<double>(index)/(N-1); // converting the index to a time-delay value
    distance=tof*343; // converting the time-delay to distance

    // Print the results

    std::cout << "The time-of-flight is: " << tof << " seconds." << std::endl;
    std::cout << "The distance is: " << distance << " meters." << std::endl;

    //for (int i = 0; i < N; ++i) {
        //std::cout << "Frequency bin " << i << ": "
                 // << soundSamples[i] << " + " << refout[i][1] << "i" << std::endl;
    //}

    // Clean up
    fftw_destroy_plan(plan_forwardsamp);
    fftw_destroy_plan(plan_forwardref);
    fftw_destroy_plan(plan_backward);
    fftw_cleanup();

    return 0;
}
