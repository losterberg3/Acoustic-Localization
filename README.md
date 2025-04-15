Acoustic Localization

Using a BeagleBone Blue, sound signals were sampled and analyzed for distance measurements. The libpruio library was used to speed up the ADC sampling rate on the BeagleBone by accessing its PRU. Sound was created using a speaker and sampled at a distance. Using the fftw library, a cross-correlation algorithm was implemented on the sampled sound signal, comparing it with the reference frequency-modulated signal. The combined sampling and cross correlation gives a distance measurement in localization.cpp. 

