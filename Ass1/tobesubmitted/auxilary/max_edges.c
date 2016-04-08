#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 1000

void print_max_edge(unsigned int n);
int main(int argc, char* argv[]) {
	unsigned int n = 50;
	print_max_edge(n);
	return 0;
}

void print_max_edge(unsigned int n) {
	if(n > MAX_VERTEX) {
		fprintf(stderr, "E: MAX_VERTEX = 1000\n");
		exit(EXIT_FAILURE);
	}
	/* print vertex count */
	fprintf(stdout, "%ld\n", n);
	
	/* print vertex label */
	int i;
	for(i = 0; i < n; i++) {
		fprintf(stdout, "%c%03ld%c\n", 0x22, i, 0x22);
	}

	/* print vertex pair */
	int j;
	for(i = 0; i < n; i++) {
		for(j = i+1; j < n; j++) {
			fprintf(stdout, "%ld %ld\n", i, j);
		}
	}
	return;
}