#Importing libaries:
library(epiDisplay)
library(modeest)

#Importing data from the dataset:
DataFrame <- read.csv("E:\\R\\DataBase.csv")

head(DataFrame)

fix(DataFrame)


tab1(DataFrame$Area, sort.group = "decreasing" , cum.percent = T)

#Bar graph:
tab1(DataFrame$Area,col = c("#8ee71b", "#00000b" , "#1f37d7" , "#8b008b"),cum.percent = T)


Area<-table(DataFrame$Area)

names(Area)<-c("Africa","America","Asia","Europe")

barplot(Area / length(DataFrame$Area),col = c("#d12828", "blue4" , "#1fd762" , "#e30cb8"))

#Pie graph:
Area<-table(DataFrame$Area)

pie(Area,clockwise = T , col = c("#28a1d1", "#8e2eb141" , "#25d71f5c" , "#848b00a2"))

#####################################################################################################

#Average, Median and Mode:

Avg_of_Birth <- mean(DataFrame$Birth_in_2020)

Avg_of_death <- mean(DataFrame$Death_in_2020)

Median_of_birth <- median(DataFrame$Birth_in_2020)

Median_of_death <- median(DataFrame$Death_in_2020)

Mode_of_birth <- mfv(DataFrame$Birth_in_2020)

Mode_of_death <- mfv(DataFrame$Death_in_2020) 


cat("\033[1;33m ",
  "Avg of Birth in 2020 : ",
  Avg_of_Birth,"\n Avg of Death in 2020 : ",
  Avg_of_death, '\n',"Median of birth : ",
  Median_of_birth,"\n Median of death : ",
  Median_of_death,'\n',"Mode of Birth : ", 
  Mode_of_birth , "\n  Mode of Death : ",
  Mode_of_death,
  "\033[0;0m")



#Min and Max:

Minimum_of_Birth <- min(DataFrame$Birth_in_2020)

Minimum_of_Death <- min(DataFrame$Death_in_2020)

Maximum_of_Birth <- max(DataFrame$Birth_in_2020)

Maximum_of_Death <- max(DataFrame$Death_in_2020)


cat("\033[1;36m ",
  "\n Maximum of Birth : ", Maximum_of_Birth,
  "\n Maximum of Death : " , Maximum_of_Death,
  "\n Minimum of Birth : ", Minimum_of_Birth,
  "\n Minimum of Death : ",Minimum_of_Death , 
  "\033[0;0m")



# Standard deviation and Variance:

Standard_dev_Birth <- sd(DataFrame$Birth_in_2020)

Standard_dev_death <- sd(DataFrame$Death_in_2020)

Variance_Birth <- var(DataFrame$Birth_in_2020)

Variance_Death <- var(DataFrame$Death_in_2020)


cat("\033[1;35m " ,
  "\n Variance of Birth : ",Variance_Birth ,
  "\n Variance of Death : ",Variance_Death ,
  "\nStandard deviation of Birth :  ",Standard_dev_Birth,
  "\n Standard deviation Death : " , Standard_dev_death, 
  "\033[0;0m")



# Domain:

Domain_of_Birth <- range(DataFrame$Birth_in_2020)

Domain_of_Death <- range(DataFrame$Death_in_2020)

cat("\033[1;31m ",
  "\n Birth in range ",
  Domain_of_Birth[1],
  "\t to \t",Domain_of_Birth[2],
  "\n","Death in range ",
  Domain_of_Death[1],
  "\t to \t",Domain_of_Death[2],
  "\n","\033[0;0m")



# Histograms:
hist(DataFrame$Birth_in_2020,breaks = seq(0,50,l = 10),
    xlim = c(0,50),ylim = c(0,42), col = c("#8ee71b", "#fa0000" , "#156d5bb0" , "#b23ab2"
    , "#8189109c","#fff700" , "#24156dfc" , "#b23ab2" , "#00e5ff" , "#11ff00"))


hist(DataFrame$Death_in_2020,breaks = seq(0,30,l = 10),
    xlim = c(0,30),ylim = c(0,50), col = c("#8ee71b", "#fa0000" , "#156d5bb0" , "#b23ab2"
    , "#8189109c","#fff700" , "#24156dfc" , "#b23ab2" , "#00e5ff" , "#11ff00"))


#Box Plot:

boxplot(DataFrame$Birth_in_2020,DataFrame$Death_in_2020,names = c("Birth","Death"), col = c("#ff0000"))


# Covariance and Correlation coefficient:

Covariance <- cov(DataFrame$Birth_in_2020,DataFrame$Death_in_2020)

cat("  Covariance is : ",Covariance)

CorrelationCoefficient <- cor(DataFrame$Birth_in_2020,DataFrame$Death_in_2020)

cat("\n CorrelationCoefficient is : ",CorrelationCoefficient)


############################################## End of part 1 ##############################################################


Min_Birth <- mean(DataFrame$Birth_in_2020)

Counter <- length(DataFrame$Birth_in_2020)

Standard_dev_of_Birth <- sd(DataFrame$Birth_in_2020)

standardError <- Standard_dev_of_Birth/sqrt(Counter)


Alpha <- 0.05

degrees.freedom <- Counter - 1

distribution_t <- qt(p=1-(Alpha/2), df=degrees.freedom,lower.tail=TRUE)


ERROR <- distribution_t * standardError

cat("\tμ ∈ (",Min_Birth - ERROR,
  ",",Min_Birth + ERROR,")")


Variance <- var(DataFrame$Birth_in_2020)

Lower_value <- qchisq(1-(Alpha/2), degrees.freedom ,lower.tail = TRUE)

Upper_value <- qchisq(Alpha/2, degrees.freedom ,lower.tail = TRUE)

cat("\tσ^2 ∈ (",
 (degrees.freedom*Variance)/Lower_value,
",",(degrees.freedom*Variance)/Upper_value,
")")


# H0 : u=u0
# H1 : u>u0

Alpha = 0.5

Average <- mean(DataFrame$Death_in_2020)

mu0 <- Average+10

Number <- length(DataFrame$Death_in_2020)

SD <- sd(DataFrame$Death_in_2020)

SE <- SD / sqrt(Number)

t_stat <- (Average - mu0) / SE

degree_of_freedom <- Number - 1

t_score <- qt(p=1-(Alpha), df=degree_of_freedom, lower.tail=TRUE)

if(t_stat >= t_score)
  cat("\033[1;32m " , "t_stat >= t_score  :  reject H0" , "\033[0;0m")
  
if(t_stat < t_score)
  cat("\033[1;32m " ,"t_stat < t_score  :  confirm H0", "\033[0;0m")
