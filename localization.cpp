// to compile: g++ -o localization localization.cpp -I/usr/local/include -L/usr/local/lib -lfftw3 -lm -lpruio -lpthread

#include <fftw3.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include "unistd.h"
#include "time.h"
#include "stdio.h"
#include "libpruio/pruio.h"

int main() {
    pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0);  // Initialize the driver
    if (io->Errr) {
        printf("Initialization failed: %s\n", io->Errr);
        return 1;
    }

    // Configure ADC step for AIN-0 (step 9)
    if (pruio_adc_setStep(io, 9, 0, 0, 0, 0)) {
        printf("Step 10 configuration failed: %s\n", io->Errr);
        return 1;
    }

    // Configure the driver for mm mode
    uint32 tmr = 100000;  // Sampling rate: 50 kHz (20000 ns)
    uint32 mask = 1 << 9;  // Active step: step 10 for AIN-1
    uint32 samp = 50000;  // Number of samples
    double samples[samp]; // Sampled sound signal
	
    if (pruio_config(io, samp, mask, tmr, 0)) { 
        printf("Configuration failed: %s\n", io->Errr);
        return 1;
    }

    while (true) { 
        // Get the start time 
        auto start = std::chrono::steady_clock::now();
 	
	// Start mm mode, this is when it actually starts sampling
	if (pruio_mm_start(io,0,0,0,0)) {
        	printf("MM mode start failed: %s\n", io->Errr);
        	return 1;
	}

	while (io->DRam[0] < samp) {
        usleep(1000);  // Sleep briefly to avoid a tight loop
	}

	// Process the buffer (AIN-0)
	for (uint32 i = 0; i < samp; i++) {
        	samples[i]=io->Adc->Value[i];
        	printf("%u\n", samples[i]);
	}

        // Reset DRam counter after processing
        io->DRam[0] = 0;

        for (uint32 i = 0; i < samp; i++) {
            samples[i]=samples[i]-2048;
	}

        double cl=0.5; //chirplength in seconds
        int sf=500; //start frequency of the chirp
        int ef=1200; //end frequency of the chirp
        double t;
        double f;
        double referenceSignal[samp]; // the reference signal

        for (int i=0;i<samp;++i){ // adding to the reference signal based on the sound produced
            if (i<(cl*samp)){
                t=static_cast<double>(i)/(samp-1);
                f=(t*t*(ef-sf)/cl/2)+(t*sf);
                referenceSignal[i]=sin(f*2*M_PI); //defining pi here 
            } else {
                referenceSignal[i]=0;
            }
        }

	// now performing cross-correlation of the sampled data with the reference
	
        fftw_complex refout[samp];  // Output reference array (complex numbers)
        fftw_complex sampout[samp]; // Output sampled array 
        fftw_complex out[samp];
        double spectrum[samp];
    
        fftw_plan plan_forwardsamp = fftw_plan_dft_r2c_1d(samp, samples, sampout, FFTW_ESTIMATE);
        fftw_plan plan_forwardref = fftw_plan_dft_r2c_1d(samp, referenceSignal, refout, FFTW_ESTIMATE);
        fftw_plan plan_backward = fftw_plan_dft_c2r_1d(samp, out, spectrum, FFTW_ESTIMATE);

        // Perform FFT
        fftw_execute(plan_forwardsamp);
        fftw_execute(plan_forwardref);

        // Multiply by complex conjugate
        for (int i = 0; i < samp; ++i) {
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

        for (int i=0; i<samp; ++i){ // finding the peak in the correlated signal
            if (spectrum[i]>max){
                max=spectrum[i];
                index=i;
            }
        }

        tof=static_cast<double>(index)/(samp-1); // using that peak to find a time delay
        distance=tof*343; // converting time to a distance measurement

        // Print the results

        std::cout << "The time-of-flight is: " << tof << " seconds." << std::endl;
        std::cout << "The distance is: " << distance << " meters." << std::endl;

        // Clean up
        fftw_destroy_plan(plan_forwardsamp);
        fftw_destroy_plan(plan_forwardref);
        fftw_destroy_plan(plan_backward);
        fftw_cleanup();

        if (pruio_config(io, samp, mask, tmr, 0)) {
            printf("Configuration failed: %s\n", io->Errr);
            return 1;
        }

        // Calculate how long the code execution took
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Calculate the remaining time to wait
        auto wait_time = std::chrono::seconds(4) - elapsed;
        
        // Ensure we wait exactly 4 seconds between samples, adjusting for the code execution time
        if (wait_time > std::chrono::seconds(0)) {
            std::this_thread::sleep_for(wait_time);
        }
    }
    //pruio_destroy(io);
    return 0;
}
