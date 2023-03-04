#include <stdlib.h>
#include <stdio.h>

/*
 * Define a function void fib(...) below. This function takes parameter n
 * and generates the first n values in the Fibonacci sequence.  Recall that this
 * sequence is defined as:
 *         0, 1, 1, 2, 3, 5, ... , fib[n] = fib[n-2] + fib[n-1], ...
 * The values should be stored in a dynamically-allocated array composed of
 * exactly the correct number of integers. The values should be returned
 * through a pointer parameter passed in as the first argument.
 *
 * See the main function for an example call to fib.
 * Pay attention to the expected type of fib's parameters.
 */

/* Write your solution here */
void fib(int **location, int n){
    //take in a location of pointer
    *location = malloc(sizeof(int)*n);
    int *arr = *location;

    int to_add = 0;    
    int last_1 = 1;
    int last_2 = 0;
    int count = 0;
    while (count < n){
        //only append the "to_add" each time
        if (count == 0){
            arr[count] = 0;
        }
        else if (count == 1){
            arr[count] = 1;
        }
        else{
            to_add = last_1 + last_2;
            arr[count] = to_add;
            last_2 = last_1;
            last_1 = to_add;
        }
        count++;
    }
}

int main(int argc, char **argv) {
    /* do not change this main function */
    int count = strtol(argv[1], NULL, 10);
    int *fib_sequence;

    fib(&fib_sequence, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", fib_sequence[i]);
    }
    free(fib_sequence);
    return 0;
}
