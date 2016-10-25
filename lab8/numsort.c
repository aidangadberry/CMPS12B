#include <stdio.h>
#include <stdlib.h>

#include "inssort.h"

int main (int argc, char **argv){
	(void) argc;
	(void) argv;
	double arr[1000];
	size_t index = 0;
	for (;;){
		double number;
		int rc = scanf ("%lg", &number);
		if (rc != 1){
			break;
		}
		if (sizeof (arr) == 1000){
			break;
		}
		arr[index] = number;
	}
	innsort (arr, index, sizeof (double), numcompare());
	for (size_t i=0; i<sizeof(arr); i++){
		printf("%20.15g\n", arr[i]);
	}
}

int numcompare (const void *a, const void *b){
	const double *x = a;
    const double *y = b;
    if (*x > *y){
    	return 1;
    }
    if (*y > *x){
    	return -1;
    }
    return 0;
}