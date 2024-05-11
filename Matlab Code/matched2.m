clear;
%read the signal
%[sig , fs] = audioread('Speech_keys.wav');
%sig = sig(:,1);
fs=2000;
deltaT=.8;
pulselength=.3;
f=200;
PI=.2;
%%%%
t=(0:(1/fs):2*deltaT-(1/fs))';
tt=(0:(1/fs):2*deltaT-(1/fs));
%%%% signal with random noise on top of the sine wave
yy=[zeros(1,fs*deltaT-1) PI*sin(f*(tt(1,[round(deltaT*fs):round((deltaT+pulselength)*fs)]).^2)) zeros(1,round((deltaT-pulselength)*fs))];
figure
plot(tt,yy);
title 'reference signal'
sig=PI*sin(f*t.^2)+4*rand(1,length(t))-2;
sig1=PI*sin(f*tt.^2)+4*rand(1,length(tt))-2;
for i=1:(deltaT*fs)
    sig(i)=4*rand-2;
end
for i=1:(deltaT-pulselength)*fs
    sig(i+(deltaT+pulselength)*fs)=4*rand-2;
end
for i=1:(deltaT*fs)
    sig1(i)=4*rand-2;
end
for i=1:(deltaT-pulselength)*fs
    sig1(i+(deltaT+pulselength)*fs)=4*rand-2;
end
figure
plot(tt,sig1)
title 'received signal'
T=length(sig)/fs;
%moving average filter
N=length(sig);
tap=20;
x=zeros(1,2*deltaT*fs);
for i=tap:N
    temp=0;
    for j=0:tap-1
        temp=temp+sig(i-j);
    end
    x(i)=temp/tap;
end
%reference signal that I want to find and filter out the noise
h=zeros(1,pulselength*fs);
for i=1:round(pulselength*fs)
   h(i)=PI*sin(t(i+round(deltaT*fs)));
end
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
title 'deltaT peak'
%%%finding the peak
[max,index]=max(OUT);
%%%converting the index of the peak to an actual time
deltaTT=(index-pulselength*fs)/fs;