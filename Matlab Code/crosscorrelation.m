%% connect to serial port, only needs to be done once after the arduino is programmed

s=serialport('/dev/cu.usbmodem141101',2000000)  %check command window, make sure baud rate is correct
%% run this section once reset button on arduino has been pressed

flush(s)    %clear the serial port receiving the data
q=read(s,41377,'uint8');  %read the data, 43194 samples for a sampling duration of 1 second
%% 
dc=127; %DC offset
p=q-dc; %using the DC offset to bring the samples around 0 and then to normalize the samples
p=p./dc; %originally the DC offset was 507, but we had to convert to an 8 bit number to maximize the serial baud rate
sr=41377; %sampling rate

cl=0.5; %chirplength in seconds
sf=1000; %start frequency of the chirp
ef=1000; %end frequency of the chirp
t=0:1/(sr-1):1; %time we are listening for the chirp
f=(t.^2*(ef-sf)/cl/2)+(t.*sf); %frequency linearly increasing (frequency is the derivative of this wrt t)
ref=sin(f.*2*pi); %reference chirp signal
ref(1001:sr)=0; %setting the rest of the reference signal to 0, because our t is a total of 1 sec, but our chirp is only 0.5 sec
sig=zeros(1,sr);
sig(:,101:1100)=-p(:,1:1000); %setting the negative of the samples gives better results, it seems like the microphone receives inverted of the reference
X=fft(ref); %fft of the reference signal
Y=fft(sig); %fft of the sampled signal
Z=Y.*conj(X); %multiplying them in frequency domain
z=ifft(Z); %ifft of the result to get back to the time domain
[m,i]=max(z); %finding the index of the peak
tof=(i-100)*(1/(sr-1)); %converting that index to a time
d=tof*343; %converting the tof to a distance by multiplying by the speed of sound
plot(z(1,1:1000))

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
%% 
plot(p(:,1:100))
%% 
mean(q)

