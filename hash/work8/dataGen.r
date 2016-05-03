#
# COMP200007 Design of Algorithms 
# Data generation for test harness for various hash table implementations.
#
#
# Author: Andrew Turpin
# Thu  9 May 2013 06:27:22 EST
#

if (length(commandArgs()) != 8) {
    cat("\n")
    cat("Usage: R --slave --args nInsert nSearch p filename1 filename2 < dataGen.r \n")
    cat("where\n")
    cat("  nInsert   = number of keys to generate into filename1\n")
    cat("  nSearch   = number of keys to sample into filename2\n")
    cat("  p         = 0 for uniform sampling, otherwise < 1 for base of exponential\n")
    cat("  filename1 = name of file for nInsert random keys\n")
    cat("  filename2 = name of file for sample of nSearch keys from filename1\n")
    cat("\n")
    stop("Bad command line params")
}

nI <- commandArgs()[4]   # number of keys to genreate into f1
nS <- commandArgs()[5]   # number of keys to sample into f2
pp <- commandArgs()[6]   # type of search distribution: 0==uniform, other is param of exponential
f1 <- commandArgs()[7]   # filename of input keys
f2 <- commandArgs()[8]   # filename of search keys

pp <- as.numeric(pp)

d <- runif(nI) * (2^32-1)
write(d, file=f1, ncolumns=1)

if (pp == 0) {
    samp <- sample(d, nS, replace=TRUE)
} else {
    samp <- suppressWarnings(sample(d, nS, replace=TRUE, prob=dexp(1:nI, pp)))
}
write(samp, file=f2, ncolumns=1)

write(sprintf("dataGen.r: p=%f, number unique search keys %d",pp,
        length(unique(samp))), stderr())




