#include<stdio.h>
#include"prime.h"
#include<stdlib.h>

int main(int argc, char* argv[]) {
   for (int i=1; i<argc; i++){
	printf("%d is %s prime number.\n", atoi(argv[i]), check_prime(atoi(argv[i])) ? "a" : "not a");
   }
}
