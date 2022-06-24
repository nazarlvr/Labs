library(ggplot2)
library(dplyr)
library(skedastic)

ds = read.csv('D:\\Sums\\MMOI\\insurance.csv', header=TRUE)
attach(ds)
ds$children = as.factor(ds$children)
ds<-group_by(ds, ds$children)

stripchart(age ~ children, xlab="Вік", ylab="Кількість дітей", col=c("red", "green", "blue", "yellow", "brown", "purple"))
means<-tapply(age, children, mean)
means

ggplot(ds, aes(x = age)) + geom_histogram() + facet_wrap(~ children, ncol = 1)


boxplot(age~children, data = ds, varwidth = T, col = "lightblue")
white_lm(lm(age ~ children, data = ds))
model<-lm(age ~ children, data = ds)
anova(model)
summary(model)
kruskal.test(age ~ children, ds)

contrasts(ds$children)
contrasts(ds$children)<-contr.sum(n=6)
contrasts(ds$children)
model2<-lm(age~children, data=ds)
summary(model2)
