#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
	fprintf(stdout, "%ld\n", sizeof(bool));
	return 0;
}