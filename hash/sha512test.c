#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
int main(int argc, char *argv[]) {
int i, length;
unsigned char data[] = "test data";
unsigned char hash[SHA512_DIGEST_LENGTH];
length = strlen((char *) data);
SHA512(data, length, hash);
for(i=0 ; i < SHA512_DIGEST_LENGTH ; i++) {
printf("%02x", hash[i]);
}
putchar('\n');
return 0;
}