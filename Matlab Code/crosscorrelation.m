%% connect to serial port, only needs to be done once after the arduino is programmed

s=serialport('/dev/cu.usbmodem141101',2000000)  %check command window, make sure baud rate is correct
%% run this section once reset button on arduino has been pressed

flush(s)    %clear the serial port receiving the data
q=read(s,43194,'uint8');  %read the data, 43194 samples for a sampling duration of 1 second
p=q-127; %using the DC offset to bring the samples around 0 and then to normalize the samples
p=p./127; %originally the DC offset was 507, but we had to convert to an 8 bit number to maximize the serial baud rate
sr=43194; %sampling rate

cl=0.5; %chirplength in seconds
sf=100; %start frequency of the chirp
ef=1000; %end frequency of the chirp
t=0:1/(sr-1):1; %time we are listening for the chirp
f=(t.^2*(ef-sf)/cl/2)+(t.*sf); %frequency linearly increasing (frequency is the derivative of this wrt t)
ref=sin(f.*2*pi); %reference chirp signal
ref((cl*43194):sr)=0; %setting the rest of the reference signal to 0, because our t is a total of 1 sec, but our chirp is only 0.5 sec
X=fft(ref); %fft of the reference signal
Y=fft(p); %fft of the sampled signal
Z=conj(X).*Y; %multiplying them in frequency domain
z=ifft(Z); %ifft of the result to get back to the time domain
[m,i]=max(z); %finding the index of the peak
tof=i*(1/(sr-1)); %converting that index to a time
d=tof*343; %converting the tof to a distance by multiplying by the speed of sound

%%
tt=0:1/(sr-1):199/(sr-1);
l=zeros(1,1000);
l(:,1:200)=sin(1500*2*pi*tt);
figure
plot(l)
title('ref')

w=zeros(1,1000);
w(:,201:400)=p(:,101:300);
figure
plot(w);
title('sampled')

X=fft(l);
Y=fft(w);
Z=Y.*conj(X); %always use the conjugate of the reference signal fft
z=ifft(Z);
figure
plot(z)


