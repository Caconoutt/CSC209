#include <stdio.h>
#include <string.h>

/*
    Write the main() function of a program that takes exactly two arguments,
    and prints one of the following:
        - "Same\n" if the arguments are the same.
        - "Different\n" if the arguments are different.
        - "Invalid\n" if the program is called with an incorrect number of
          arguments.

    NOTE: Cut and paste these strings into your printf statements to
    ensure that they will be exactly the strings above.

    Your main function should return 0, regardless of what's printed.
*/
int main(int argc, char **argv){
    //make string literals
    char *str1 = argv[1];
    char *str2 = argv[2];

    if (argc != 3){printf("Invalid\n");}
    else{
        if (strlen(str1) != strlen(str2)){printf("Different\n");}
        else{
            int checker = 0; //it becomes 1 when one of char is different
            for (int i = 0; i < strlen(str1); i++){
                if (str1[i] != str2[i]){checker = 1;}
           }
           if (checker != 0){printf("Different\n");}
           else{printf("Same\n");}
        }
    }
    return 0;
}