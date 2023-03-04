#include <stdio.h>
#include <stdlib.h>

// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char *, char *);

int check_permissions(char *array1, char *array2){
    // use array2 to check array1
    // do not check if it's '-'
    for (int i = 0; i < 9; i++){
        if ((array2[i] != '-') && (array2[i] != array1[i])){
            return 1;
        }
    }
    return 0;
}


int main(int argc, char** argv) {
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE: count_large size [permissions]\n");
        return 1;
    }
    // TODO: Process command line arguments.
    
    //variable initialization;
    int cutoff = 0;//input cutoff
    char *array2;//input checker for permission
    int result = 0;//to return
    int size = 0; //size of given files
    char p[11] = "----------";//initialize the list of character for permission

    scanf("%*s %*s"); // Skip the first line of Total

    // case of only two argument
    if (argc == 2) {
        cutoff = strtol(argv[1], NULL, 10);

        while(scanf("%s %*s %*s %*s %d %*s %*s %*s %*s", p, &size) != EOF){
            if (p[0] == '-'){                
                if (size > cutoff){
                    result += 1;
                }
            }

        }

    }

    //case of three arguement
    else{
        cutoff = strtol(argv[1], NULL, 10);
        array2 = argv[2];
        while(scanf("%s %*s %*s %*s %d %*s %*s %*s %*s", p, &size) != EOF){
            if (p[0] == '-'){
                char *array1 = &p[1];
                int permission_check = check_permissions(array1, array2);
                if (permission_check == 0){
                    if (size > cutoff){
                        result += 1;
                    }
                }
            }

        }
    }
    
    printf("%d\n", result);

    return 0;
}
