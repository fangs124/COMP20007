#
# COMP200007 Design of Algorithms 
# Plot output from run.hs
#
# Author: Andrew Turpin
# Thu  9 May 2013 06:55:54 EST
#

if (length(commandArgs()) != 4) {
    cat("\n")
    cat("Usage: R --slave --args filename < plotIt.r \n")
    cat("where\n")
    cat("  filename = name of file with results (8 columns)\n")
    cat("\n")
    stop("Bad command line params")
}

f1 <- commandArgs()[4]   # number of keys to genreate into f1

d <- read.table(f1, 
    colClasses=c("character","numeric", 
                 "character", "numeric",
                 "character", "numeric",
                 "character", "numeric"
))

l <- split(d, d[,1:2])
par(las=3)
boxplot(ll <- lapply(lapply(l, "[", 8), unlist), ylab="Time (ms)", outline=FALSE)
