#include <stdio.h>
#include <stdlib.h>

int populate_array(int, int *);
int check_sin(int *);


int main(int argc, char **argv) {
    // TODO: Verify that command line arguments are valid.
    if (argc != 2){return 2;}
    int sin_num = strtol(argv[1], NULL, 10);//a pointer to the int

    int *sin_array = malloc(sizeof(int) * 9);//initialize a ptr point to heap
    //not checking the check for now
    int result1 = populate_array(sin_num, sin_array);//put numbers into array
    if (result1 == 1){
        printf("Invalid SIN\n");
        return 1;
    }

    // TODO: Parse arguments and then call the two helpers in sin_helpers.c
    // to verify the SIN given as a command line argument.
    int result = check_sin(sin_array);
    free(sin_array);
    if (result != 0){
        printf("Invalid SIN\n");
        return 1;
    }
    printf("Valid SIN\n");
    return 0;
}
