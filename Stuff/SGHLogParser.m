function [ avgt, avgh ] = SGHLogParser( filepath,loopt )
%SGHLogParser SmartGreenHouse stat parser
%   Parser for log data

data=load(filepath);

samples=length(data);


%Time (In hour)
time=(1:samples)/3600*loopt;


temp=data(:,1);
humidity=data(:,3);
avgt=median(temp);
avgh=median(humidity);
%%%General state evolution-------------------------------------------------
figure('Name','Sistem evolution','NumberTitle','off')
axis(1)=subplot(2,1,1);
plot(time,temp)
legend('Temperature (°C)');
xlabel('Time (h)')
axis(2)=subplot(2,1,2);
plot(time,humidity)
legend('Relative Humidity (%RH)');
xlabel('Time (h)')

%Cool but only works on Matlab
%linkaxes(axis, 'x');

if(max(time)<12)
    Tmedian=median(temp)
    Hmedian=median(humidity)
else
    
    %%%Hourly statistics (Only if more than 12 hour)-----------------------
    i=0;
    while (i+1)*3600<samples
        datawindow=(i*3600+1:(i+1)*3600);
        htemp(i+1,1)=min(temp(datawindow));
        htemp(i+1,3)=max(temp(datawindow));
        htemp(i+1,2)=sum(temp(datawindow))/3600;
        hhumidity(i+1)=sum(humidity(datawindow))/3600;
 
        i=i+1;
    end
    htime=1:(i);
    figure('Name','State Variables','NumberTitle','off')
    axis(1)=subplot(2,1,1);
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
    
    %Same
    %linkaxes(axis, 'x');
    
    
    
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


end

