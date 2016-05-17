#include <stdio.h>
#include <stdlib.h>

typedef unsigned char data_t;

typedef enum  {
	LEAF,
	INTERNAL,
	PARENT,
	EMPTY
} status_t;

typedef enum  {
	FIND_i,
	FIND_j,
	COMBINE
} stage_t;

typedef struct {
	data_t data;
	unsigned int count;
	status_t status : 8;
} bucket_t;

int main(int argc, char* argv[]){
	return 0;
}

//assumption:
//function in put is pointer to a bukect_t array with number of elements
//bucket_t contains data, and sorted count, with status set to leaf node
//return is pointer to an array of node leaf depth (corresponding to bitcode length)
//buckets is assume to be B = [0,1,..,n-1]. where n elements is stored.
bucket_t* encode(bucket_t* buckets, size_t n){
	assert(n >= 2);
	/* find smallest value as B[i] */
	stage_t stage = FIND_i;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int probe = 1;
	while(probe) <= n-2){
		/* linear search i */
		if(stage == FIND_i){
			/* update candidate i */
			if(buckets[i].count > buckets[probe].count){
				i = probe;
				probe++;
			}
			/* found i */
			else if(buckets[probe].count > buckets[i].count){
				stage = FIND_j;
				probe = j;
			}
			/*  */
			else {
				continue;
			}
		}
		/* linear search j */
		if(stage == FIND_j){
			/* skip i */
			if(probe == i || buckets[probe].status == EMPTY){
				probe++;
			}
			/* update candidate j */
			else if(buckets[j].count > buckets[probe].count){
				j = probe;
				probe++;
			}
			/* found j */
			else if(buckets[probe].count > buckets[j].count){
				stage = FIND_i;
				stage = combine(buckets, i, j);
			}
			else {
				continue;
			}

		}
			

	} 
	return;
}

combine(bucket_t* val1, bucket_t* val2){

}