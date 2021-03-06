require(graphics)
library(smooth)
library(fpp)
library(fUnitRoots)
ds=fpp::cafe
plot(ds, xlab="���", ylab="������� ������� �� ����",
     las=1, main="������� ��� � �������� ��� ����")

sma(ds, order=3, silent=F)
sma(ds, order=5, silent=F)
sma(ds, order=7, silent=F)

# 3. Decomposition
plot(decompose(ds))

# 4. Correlogram and partial correlogram
ds1 = diff(ds, lag=4)
adf.test(ds)
adf.test(ds1)
plot(ds1, xlab="���", ylab="������� ������� �� ����",
     main="����� ������������ ���������������")
ds1 %>% ggtsdisplay()

# 5. Forecast (triple exponential smoothing), ARIMA forecast
hw <- HoltWinters(ds)
p = predict(hw, 50, prediction.interval = F)
plot(hw, p, xlab="г�",ylab="������� ������� �� ����",
     main="������� �� ������� �����-³������")

ds %>% Arima(order=c(0,1,1), seasonal=c(0,1,1)) %>%
  residuals() %>% ggtsdisplay()
ds %>% Arima(order=c(0,1,5), seasonal=c(0,1,1)) %>%
  residuals() %>% ggtsdisplay()
ds %>% Arima(order=c(0,1,18), seasonal=c(0,1,1)) %>%
  residuals() %>% ggtsdisplay()
fit <-Arima(ds,order=c(0,1,18), seasonal=c(0,1,1))

library(forecast)
plot(forecast(fit$x), xlab="г�", ylab="������� ������� �� ����",
     main="������� �� ������� ARIMA")

# 6. Residuals' diagrams
library(astsa)
sarima(ds,0,1,5,0,1,1,4)
sarima(ds,0,1,18,0,1,1,4)
