
# Makefile 
# Andrew Turpin
# April 2013

OBJ  = array.o hashtable.o listops.o main.o key.o MurmurHash3.o
SRC  = array.c hashtable.c listops.c main.c key.c MurmurHash3.c
EXE  = testHash

CC     = g++
CFLAGS = -Wall -O2 -m32

testHash:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

listops.o: listops.h key.h Makefile
array.o: array.h key.h Makefile
main.o: array.h listops.h key.h Makefile MurmurHash3.h
key.o: key.h Makefile

####################################################
# *nix command line for making random files
# file1 is random keys
# file3 is file1 in random order for searching
####################################################
    # creates a file of 25000 random 4-byte integers
# dd if=/dev/urandom  bs=4 count=100000 | od -t u4 | awk '{print $2}' > file1
# dd if=/dev/urandom  bs=4 count=100000 | od -t u4 | awk '{print $2}' > file2
    # sorts file1 in random order given by file2 
# paste file2 file1 | sort -n | cut -f 2-2 > file3


##########################
## This bit for documents, not for students.
##########################
tex: work9.tex
	pdflatex "\def\answerson{1} \input{work9}"
	\mv work9.pdf soln9.pdf
	pdflatex "\input{work9}"
	@echo "****************************"
	@echo "***** spell check **********"
	@echo "****************************"
	@ispell -t -p ./.dic -l < work9.tex | sort -u

# add words to .dic and them make list
list: 
	munchlist .dic > x
	\mv x .dic
	buildhash .dic /usr/local/Cellar/ispell/3.3.02/lib/ispell/english.aff .dic.hash
