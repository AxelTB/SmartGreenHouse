function [ HeaterOnTime ] = SGHStats( file )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

data=load(file);

fantocmph=16/(0.589*255);


pend=length(data);
pstart=1;

time=(pstart:pend)/3600;
temp=data(pstart:pend,1);
heat=data(pstart:pend,2);
humidity=data(pstart:pend,3);
humidifier=data(pstart:pend,4);
hcable=data(pstart:pend,5);

fhumidity=data(pstart:pend,8);
outf=data(pstart:pend,9);

%%%Caos
figure('Name','Temperature evolution','NumberTitle','off')
plot(time,temp,'g',time,heat.*10+15,'r',time,outf./20+15,'b')
figure('Name','Humidity evol','NumberTitle','off')
plot(time,humidity./100,'g',time,humidifier,'r',time,outf./255,'b')



%%%Hourly statistics
hactive=sum(heat)/pend*100;
i=ceil(pstart/3600);
hhactive=0;
while i*3600+pstart<pend
    datawindow=((i-1)*3600:i*3600)+pstart;
    hhactive(i)=sum(heat(datawindow))/3600;
    outfhmq(i)=sum(outf(datawindow))/3600*fantocmph;
    htemp(i,1)=min(temp(datawindow));
    htemp(i,3)=max(temp(datawindow));
    htemp(i,2)=sum(temp(datawindow))/3600;
    hhumidity(i)=sum(humidity(datawindow))/3600;
    hhcable(i)=sum(hcable(datawindow))/3600;
    
    i=i+1;
end
htime=1:(i-1);
figure('Name','Heater','NumberTitle','off')
subplot(2,1,1)
bar(hhactive,'r')
title('Heater active percentage')
subplot(2,1,2)
bar(hhcable)
title('Heat cable on time')

figure('Name','Other actuators','NumberTitle','off')
subplot(2,1,1)
bar(hhumidity)
title('Humidifier active percentage')
subplot(2,1,2)
bar(outfhmq)
title('Airflow m^3/h')

figure('Name','State Variables','NumberTitle','off')
subplot(2,1,1)
%bar(htemp)
plot(htime,htemp(:,1),'b*',htime,htemp(:,2),'g*',htime,htemp(:,3),'r*')
title('Temperature')
subplot(2,1,2)
bar(hhumidity)
title('Humidity median')

htime=0;
hdc=0;
hi=1;
start=0;

%%Daily-------------------------------
i=1;dhactive=0;
while i*24<length(hhactive)
    datawindow=(i-1)*24+1:i*24;
dhactive(i)=sum(hhactive(datawindow))/24;
i=i+1;
end
figure('Name','Daily Stats','NumberTitle','off')
bar(dhactive)
%Text statistic
HeaterOnTime=sum(htemp(:,2))/100


%%Data
%1. temp
%2. heater
%3. humidity
%4. humidifier
%5. heatcable
%6. light
%7. flight
%8. fhumidity
%9. outfan

end

