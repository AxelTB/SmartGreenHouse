%   SmartGreenHouse stat parser

close all, clear all
%file='../SmartGreenHouse_data/last/TotTemp';
file='../SmartGreenHouse_data/Debug/T0';

data=load(file);

%Parameters
heaterD=3;
heaterT=18;
hcableD=5;
hcableT=25;
humidifierD=10;
humidifierT=35;


fantocmph=16/(0.589*255);


pend=length(data);
pstart=1;
% pstart=6*24*3600/2;
% pend=7*24*3600/2;
time=(pstart:pend)/3600*2;

%time=6*3600
temp=data(pstart:pend,1);
heat=data(pstart:pend,2);
humidity=data(pstart:pend,3);
humidifier=data(pstart:pend,4);
hcable=data(pstart:pend,5);

fhumidity=data(pstart:pend,8);
outf=data(pstart:pend,9);

%%%General state evolution-------------------------------------------------
figure('Name','Sistem evolution','NumberTitle','off')
axis(1)=subplot(2,1,1);
plot(time,temp,'g',time,heat.*heaterD*2-heaterD+heaterT,'r*',time,hcable*hcableD*2-hcableD+hcableT,'ob')
legend('Temperature', 'Heater','Heat Cable');
xlabel('Time (h)')
axis(2)=subplot(2,1,2);
plot(time,humidity./100,'g',time,humidifier,'b*',time,outf./255,'r*')
legend('Humidity', 'Humidifier', 'Fan');
xlabel('Time (h)')
linkaxes(axis, 'x');

if(max(time)<12)
    Tmedian=median(temp)
    Hmedian=median(humidity)
else
    
    %%%Hourly statistics (Only if more than 12 hour)-----------------------
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
    figure('Name','Heater Hourly Statistic','NumberTitle','off')
    subplot(2,1,1)
    bar(hhactive,'r')
    title('Heater active')
    xlabel('Time (h)')
    ylabel('%')
    subplot(2,1,2)
    bar(hhcable)
    title('Heat cable on time')
    xlabel('Time (h)')
    ylabel('%')
    
    figure('Name','Other actuators Hourly Statistic','NumberTitle','off')
    subplot(2,1,1)
    bar(hhumidity)
    title('Humidifier Active')
    xlabel('Time (h)')
    ylabel('%')
    subplot(2,1,2)
    bar(outfhmq)
    title('Airflow')
    xlabel('Time (h)')
    ylabel('m^3/h')
    
    figure('Name','State Variables','NumberTitle','off')
    axis(1)=subplot(2,1,1);
    %bar(htemp)
    plot(htime,htemp(:,1),'b*',htime,htemp(:,2),'g*',htime,htemp(:,3),'r*')
    title('Temperature')
    xlabel('Time (h)')
    ylabel('°C')
    legend('Min','Med','Max')
    axis(2)=subplot(2,1,2);
    bar(hhumidity)
    title('Humidity median')
    xlabel('Time (h)')
    ylabel('%')
    linkaxes(axis, 'x');
    
    if(max(time)/24>3)
        %%Daily Stat (If more than 3 days)-------------------------------
        i=1;dhactive=0;
        while i*24<length(hhactive)
            datawindow=(i-1)*24+1:i*24;
            dhactive(i)=sum(hhactive(datawindow));
            i=i+1;
        end
        figure('Name','Daily Heater On Time','NumberTitle','off')
        xlabel('Days')
        ylabel('%')
        bar(dhactive)
    end
    %Text statistic
    HeaterOnTime=sum(htemp(:,2))/100
    
end
%%Data
%1. temp
%2. heatercl
%3. humidity
%4. humidifier
%5. heatcable
%6. light
%7. flight
%8. fhumidity
%9. outfan

%end

