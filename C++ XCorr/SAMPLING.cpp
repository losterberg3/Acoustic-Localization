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
    uint32 tmr = 20000;  // Sampling rate: 50 kHz (20000 ns)
    uint32 mask = 1 << 9;  // Active step: step 10 for AIN-1
    uint32 samp = 1000;  // Number of samples
    int samples[samp];
    if (pruio_config(io, samp, mask, tmr, 0)) {
        printf("Configuration failed: %s\n", io->Errr);
        return 1;
    }
    // Start mm mode, this is when it actually starts sampling
    if (pruio_mm_start(io,0,0,0,0)) {
        printf("MM mode start failed: %s\n", io->Errr);
        return 1;
    }
    while (io->DRam[0] < samp) {
        usleep(1000);  // Sleep briefly to avoid a tight loop
    }
    // Process the first half of the buffer (AIN-0)
    for (uint32 i = 0; i < samp; i++) {
        samples[i]=io->Adc->Value[i];
        printf("%u\n", samples[i]);
    }
    pruio_destroy(io);
    return 0;
}

