clear;
fs=20000;
T=length(sig)/fs;
%%sig is what the receiver picks up at each value of t
%%Fs is the sampling rate at which we sample to get the received signal


%moving average filter
N=length(sig);
tap=20;
for i=tap:N
    temp=0;
    for j=0:tap-1
        temp=temp+sig(i-j);
    end
    x(i)=temp/tap;
end







%reference signal that I want to find and filter out the noise
%reference signal is sampled at fs as well
h=referencesignal
x=recievedsignal

%the time domain signals must be the same length - so pad them with zeros
lh=length(h);
lx=length(x);

h=[h zeros(1,lx)];
x=[x zeros(1,lh)];

%invert the signal and fft them both
w=flipud(h);
W=fft(w);
X=fft(x);

%convolute and ifft the result
Y=X.*W;
y=ifft(Y);

%square the result to give more pronouced peaks
OUT=y.^2;
figure
plot(OUT)
