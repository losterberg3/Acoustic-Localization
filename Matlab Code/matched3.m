%%% output the chirp signal
%%% read the chirp signal, turn into an array
%%% create reference signal array
%%% fft of both signals

%connect to arduino board
a=arduino

%chirp output (D5 is digital pin we connect the transducer to)
%read the chirp (A4 is analog pin we connect the microphone to)
sf=100;
ef=1000;
chirplength=0.5;
sig=zeros(1,10000);
for i=0:9999
    %playTone(a,'D5',sf+(ef-sf)*i/1000,chirplength/10000)
    sig(i+1)=readVoltage(a,'A4'); %may have to use bluetooth, think of some ways to fix this
end
%may have to account for DC offset of the readVoltage, check Oscilloscope

%creating the reference signal

T=chriplength*(1-1/10000);
t=0:(chirplength/10000):T;
f=(ef-sf)*(t.^2)/2/T+sf*t;
rs=sin(2*pi*f);

%% cross-correlation, FFT calculations
%invert the signal and fft them both
Rs=flipud(rs);
RS=fft(Rs);
SIG=fft(sig);

%convolute and ifft the result
Y=SIG.*RS;
y=ifft(Y);

%square the result to give more pronouced peaks
OUT=y.^2;
figure
plot(OUT)

%moving average filter
%N=length(sig);
%tap=20;
%for i=tap:N
    %temp=0;
    %for j=0:tap-1
        %temp=temp+sig(i-j);
    %end
    %x(i)=temp/tap;
%end



%% 

t=0:0.01:1;
y=sin(2*pi*4*t);
x=fft(y);
p=ifft(x);
plot(p)

