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
        printf("Step 9 configuration failed: %s\n", io->Errr);
        return 1;
    }

    // Configure the driver for ring buffer mode
    uint32 tmr = 20000;  // Sampling rate: 50 kHz (20000 ns)
    uint32 mask = 1 << 9;  // Active step: step 9 for AIN-0
    uint32 samp = 1000;  // Number of samples

    int samples[samp];

    if (pruio_config(io, samp, mask, tmr, 0)) {
        printf("Configuration failed: %s\n", io->Errr);
        return 1;
    }

    // Start ring buffer mode, this is when it actually starts sampling
    if (pruio_rb_start(io)) {
        printf("RB mode start failed: %s\n", io->Errr);
        return 1;
    }

    // Process data from the ring buffer
    uint16 *p0 = io->Adc->Value;  // Start of the ring buffer
    uint32 half = io->ESize >> 2;  // Half the buffer size

    struct timespec mSec;
    mSec.tv_nsec = 5000000;  // Sleep for 5 ms

    int j=0;

    while (j<1000) {
        // Wait for half the buffer to fill
        while (io->DRam[0] < samp) nanosleep(&mSec, NULL);

        // Process the first half of the buffer (AIN-0)
        for (uint32 i = 0; i < samp; i++) {
            printf("%u\n", p0[i]);
            samples[i]=p0[i];
	    j=j+1;
	}

        // Reset DRam counter after processing
        io->DRam[0] = 0;

        // Wait for the second half to fill
        //while (io->DRam[0] > half) nanosleep(&mSec, NULL);

        // Process the second half of the buffer (AIN-0)
        //for (uint32 i = half; i < io->ESize >> 1; i++) {
            //printf("%u\n", p0[i]);
        //}

        // Reset DRam counter again
        //io->DRam[0] = 0;
    }

    // Stop RB mode and clean up
    pruio_destroy(io);

    return 0;
}

