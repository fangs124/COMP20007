/*
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>
//not sure if this is allowed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRLEN 256

static unsigned int r[MAXSTRLEN];
static unsigned int initialized = 0;
unsigned int* extended_euclid(unsigned int a, unsigned int b);

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    
    //find next prime after 2*n
    //prime not be divisible by 2 (if prime != 2)
    unsigned int x = (2*n) + 1;
    unsigned int i;
    bool prime_found = x;
    bool reset_test = false;
    while(!prime_found){
    	for(i = 3; i*i <= x; i+=2){
    		if(x % i == 0){
    			reset_test = true;
    			break;xi
    		}
    	}
    	if(reset_test){
    		x+=2;
    		reset_test = false;
    	}
    	else{
    		return x;
    	}
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    /* printing number of Num_randoms */
     i
    unsigned int i;
    if(!initialized){
        srand(seed);
        for(i = 0; i < MAXSTRLEN; i++){
            r[i] = rand() %size;
            fprintf(stdout, "%u\n", r[i]);
        }
    }
    else{
        /* printing r[i], followed by '\n' */
        for(i = 0; i < MAXSTRLEN; i++){
            fprintf(stdout, "%u\n", r[i]);
        }
    }
    
    //start by strlen 1
    int coll_count = 0;
    unsigned int char_val;
    unsigned int length = 1;
    unsigned char* string = (unsigned char*) malloc(sizeof(unsigned char) * length);
    while(coll_count != n && length != size){
        for(i = 0; i < =c s; i++){
            for(char_val = 1; char_val < MAXSTRLEN; char_val++){
                //assuming non-trivial n%size, since all n%size == 0;
                string[i] = char_val;
                if(universal_hash(string, size) == 0){
                    fprintf(stdout, "%s\n", &string[0]);
                    coll_count++;
                    if(coll_count == n){
                        return;
                    }
                }
            }w
        }
        /* increas size */
        length++;
        string = (unsigned char*) realloc(string, sizeof(unsigned char) * length);
        /* initialize string */
        for(i = 0; i < length; i++){
            string[i] = (unsigned char) 1;
        }
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
    fprintf(stderr, "here\n");
    int coll_count = 0;
    unsigned int i = 0;
    unsigned int k = 0;
    unsigned int r_count = 0;
    unsigned int *r = NULL;
    unsigned int *return_val = NULL;
    unsigned char* string = NULL;
    unsigned char** coll_strings = (unsigned char**) malloc(sizeof(unsigned char*) * n);
    unsigned int* coll_length = (unsigned int*) malloc(sizeof(unsigned int) * n);
    srand(seed);
    while(coll_count < n){
        if(r == NULL){
            r = (unsigned int*) malloc(sizeof(unsigned int));
            string = (unsigned char*) malloc(sizeof(unsigned char));

        }
        else{
            r = (unsigned int*) realloc(r, sizeof(unsigned int) * r_count+1);
            string = (unsigned char*) realloc(string, sizeof(unsigned char) * r_count+1);
        }
        r[r_count] = rand() %size;

        return_val = extended_euclid(size, r[r_count]);
        fprintf(stderr, "[%u %u %u]\n", return_val[0], return_val[1], return_val[2]);
        if(return_val[2] == 1){
            k = 0;
            while(return_val[1] > k*size){
                string[r_count] =  return_val[1] - (k*size);
                if(string[r_count] == '\0'){
                    continue;
                }
                else{
                    fprintf(stderr, "string:\n");
                    for(i=0;i < r_count;i++){
                        fprintf(stderr, "%X", string[i]);
                    }
                    fprintf(stderr, "%X\n");

                    coll_strings[coll_count] = malloc(sizeof(unsigned char)* (r_count+1));
                    memcpy(coll_strings[coll_count], string, r_count);
                    coll_strings[coll_count][r_count+1] = '\0';
                    coll_length[coll_count] = r_count;
                    coll_count++;
                    if(coll_count == n){
                        break;
                    }
                }
                k++;
            }
            //
        }
       

        r_count++;

    }
    /* print phase */
    //fprintf(stdout, "%u\n", r_count);
    
    for(i = 0; i < r_count; i++){
        //fprintf(stdout, "%u\n", r[i]);
    }

    for(i = 0; i < n; i++){
        fprintf(stdout, "%s\n", coll_strings[i]);
        //fwrite(coll_strings[i], sizeof(unsigned char), coll_length[i], stdout);
        free(coll_strings[i]);
        coll_strings[i] = NULL;
    }
}

// a >= b
//returns [x, y, d]
//such that ax + by = d
unsigned int* extended_euclid(unsigned int a, unsigned int b){
    unsigned int *return_val = (unsigned int*) malloc(sizeof(unsigned int) * 3);
    unsigned int *temp;
    if(b == 0){
        return_val[0] = 1;
        return_val[1] = 0;
        return_val[2] = a;
    }
    else{
        if(b >= a%b){
            //normally
            temp = extended_euclid(b, a%b);
        }
        else{
            temp = extended_euclid(a%b, b);
        }
        return_val[0] = temp[1];
        return_val[1] = temp[0] - ((a/b)*temp[1]);
        return_val[2] = temp[2];
        free(temp);
        temp = NULL;
    }
    return return_val;
}
