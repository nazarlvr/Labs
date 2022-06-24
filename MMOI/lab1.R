library(psych)
library(ggplot2)
library(moments)
library(gamlss)
library(EnvStats)

marksDataset = read.csv("D:\\Sums\\MMOI\\test_scores.csv");
pretestScore = marksDataset$pretest

#1

mean(pretestScore) #Середнє значення
median(pretestScore) #Медіана 

#2

var(pretestScore) #дисперсія
sd(pretestScore) #Стандартне відхилення
sd(pretestScore)/mean(pretestScore) #Коефіцієнт варіацій
max(pretestScore) - min(pretestScore) #розмах варіацій
IQR(pretestScore)  #Інтерквартильний розмах 

#3

boxplot(pretestScore,ylab = "Оцінка", outline = F) #Ящик з вусами

#4

summary(pretestScore)  #5-точкова Характеристика 

#5

quantile(pretestScore,seq(0,1,0.1))[2] #1-ий дециль
quantile(pretestScore,seq(0,1,0.1))[10] #9-ий дециль

#6

skew(pretestScore) #коефіцієнт асиметрії
kurtosis(pretestScore) #коефіцієнт ексцесу

#7

histDist(pretestScore, family = NO,density = T,ylab="Щільність",xlab="Оцінка",main="Стьоржеса")
histDist(pretestScore, family = NO,density = T,ylab="Щільність",xlab="Оцінка",nbin="Scott",main="Скотта")
histDist(pretestScore, family = NO,density = T,ylab="Щільність",xlab="Оцінка",nbin="FD",main="Фрідман-Діаконіс")

#8

qqnorm(pretestScore,xlab="Теоретичні квантилі",ylab="Вибіркові квантилі")
qqline(pretestScore, col="red", lwd=5)
#9

m <- mean(pretestScore) #Середнє значення
v <- var(pretestScore) #дисперсія
plot(pgamma(sort(pretestScore), shape = (m*m)/v, scale = v/m, lower.tail = TRUE,
            log.p = FALSE), (1:length(pretestScore))/length(pretestScore), xlab = "Теоретична функція розподілу",
     ylab="Емпірична функція розподілу",main="P-P plot")
abline(0, 1, col="black")

sd<-sd(pretestScore) #Стандартне відхилення
plot(pnorm(sort(pretestScore), m, sd), (1:length(pretestScore))/length(pretestScore), xlab = "Теоретична функція розподілу",
     ylab="Емпірична функція розподілу")
abline(0, 1, col="black")

#10

library(vsgoftest)
vs.test(x=pretestScore,densfun="dnorm",extend=T) #рівень значущості 0.05 за критерієм Vasisek-Song для норм розподілу 

