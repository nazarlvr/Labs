library(corrplot)
library(qgraph)
x = read.csv("D:\\Sums\\MMOI\\Istanbul Weather Data.csv");
pairs(x[,c('MaxTemp', 'MinTemp','AvgHumidity', 'AvgWind')], main = "������������ �����")
c<-cor(x[,c('MaxTemp', 'MinTemp','AvgHumidity', 'AvgWind')])
corrplot.mixed(c)
corrplot(c, method="shade", order="hclust")
qgraph(cor(x[,c('MaxTemp', 'MinTemp','AvgHumidity', 'AvgWind')]))
cor.test(x$MaxTemp, x$MinTemp, method="pearson")
cor.test(x$MaxTemp, x$MinTemp, method="spearman")
cor.test(x$MaxTemp, x$MinTemp, method="kendall")
cor.test(x$MaxTemp, x$AvgHumidity, method="pearson")
cor.test(x$MaxTemp, x$AvgHumidity, method="spearman")
cor.test(x$MaxTemp, x$AvgHumidity, method="kendall")

