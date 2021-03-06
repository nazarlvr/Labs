library(model4you)
library(Metrics)
library(readxl)
library(corrplot)
library(qgraph)

x = read.csv("D:\\Sums\\MMOI\\Istanbul Weather Data.csv");

xHum<-x$AvgHumidity[1:300] / 100
xTemp<-x$MaxTemp[1:300]
plot(xTemp,xHum,main="ĳ������ ����������",xlab="����. �����������",ylab="��������")

a <- cov(xTemp,xHum)/var(xTemp)  # (������� ����������)
a
b <- mean(xHum)-a*mean(xTemp)  # (��� ������)
b
model<-lm(xHum~exp((82-xTemp)*xTemp/(xTemp+400)))
model

# Regression line
temp <-seq(0, 35, 0.1)[0:350]
humidityPredict <- predict(model,list(xTemp=temp))
lines(temp, humidityPredict, col='blue', lwd=2)
rse(xTemp,xHum-resid(model))   
1-mean((resid(model))^2)/mean((xHum-mean(xHum))^2)  


summary(model)

# Response vs prediction plot
resid<-resid(model)
resid
pred<-xHum-resid
pred
plot(pred,xHum,xlab="������������ ��������",ylab="�������� ������",main="ĳ������ �������-�����")
abline(0,1, col="red", lwd=2)

# Residuals vs prediction plot 
plot(pred,resid,xlab="�������� ������",ylab="�������",main="ĳ������ �����-�������")
abline(0,0,lwd=1)

mas<-c(1:300)
plot(mas,resid,xlab="����� �������������",ylab="�������",main="ĳ������ �����-�������")
abline(0,0,col="red", lwd=4)


# Q-Q diagram
plot(model)

