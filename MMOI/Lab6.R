# 0. Preparing the dataset
library(cluster)
library(cluster.datasets)
library(factoextra)
library(dplyr)
library(fossil)
ds <- scale(birth.death.rates.1966[,c(2,3)])

# 1.1. Cluster analysis (hierarchical)
res.dist = dist(birth.death.rates.1966, method="euclidean")

res.ctr = hclust(d=res.dist, method="centroid")
plot(res.ctr, main="Centroid method")
res.coph = cophenetic(res.ctr)
cor(res.dist, res.coph)

res.med = hclust(d=res.dist, method="median")
plot(res.med, main="Median method")
res.coph = cophenetic(res.med)
cor(res.dist, res.coph)

res.wrd2 = hclust(d=res.dist, method="ward.D2")
plot(res.wrd2, main="Ward's method")
res.coph = cophenetic(res.wrd2)
cor(res.dist, res.coph)

res.avg = hclust(d=res.dist, method="average")
plot(res.avg, main="Average linkage")
res.coph = cophenetic(res.avg)
cor(res.dist, res.coph)

res.sgl = hclust(d=res.dist, method="single")
plot(res.sgl, main="Single linkage (nearest neighbor) method")
res.coph = cophenetic(res.sgl)
cor(res.dist, res.coph)

res.cpl = hclust(d=res.dist, method="complete")
plot(res.cpl, main="Complete linkage (furthest neighbor) method")
res.coph = cophenetic(res.cpl)
cor(res.dist, res.coph)

res.mcq = hclust(d = res.dist, method = "mcquitty")
plot(res.mcq, main="McQuitty method")
res.coph = cophenetic(res.mcq)
cor(res.dist, res.coph)

# 1.2. Cluster analysis (k-means)
res.km = kmeans(ds, 2, nstart = 20)
fviz_cluster(res.km, data=ds, palette="jco",
             choose.vars=c("birth","death"),
             ggtheme=theme_minimal())

# 2. Defining the optimal clusters' amount
fviz_nbclust(ds, kmeans, method="gap_stat")
fviz_nbclust(ds, kmeans, method="silhouette")
fviz_nbclust(ds, kmeans, method="wss")

# 3. Best clustering results
cut_avg = cutree(res.avg, k=2)
plot(res.avg, main="Average linkage method")
rect.hclust(res.avg , k=2, border=2:6)
fviz_cluster(list(data=ds, cluster=cut_avg),
             ggtheme=theme_minimal())

cut_cpl = cutree(res.cpl, k=2)
plot(res.cpl, main="Complete linkage (furthest neighbor) method")
rect.hclust(res.cpl , k=2, border=2:6)
fviz_cluster(list(data=ds, cluster=cut_cpl),
             ggtheme=theme_minimal())

# 4. Rand's index
true_label = c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2,   2, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1,    1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,    2, 2, 2, 2, 2, 2, 2, 2, 2, 2)
rand.index(true_label, cut_avg)
rand.index(true_label, cut_cpl)
