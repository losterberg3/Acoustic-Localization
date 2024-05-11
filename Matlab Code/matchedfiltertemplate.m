T=randi(1000)/100;
t=0:0.01:10;
ref=sin(t.^2);
ref2=sin(t);
figure
plot(t,ref);
X=1+((10+T)/0.01);
noise=-1+2*rand(1,X);
tt=0:0.01:10+T;
ref=[zeros(1,X-size(t,2)) ref];
signal=noise+ref;
figure
plot(tt,signal);
syms X x
f=@X integral(sin(x^2)*h(X-x),-inf,inf);