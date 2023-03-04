#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *basename(char *path){
        int size = strlen(path);
        char result[size];
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            if (path[i] == '/'){index = 0;}
            else{
                result[index] = path[i];
                index++;
            }
        }
        result[index] = '\0';
        char *res = malloc(sizeof(char)*index);
        strncpy(res, result, index);
        return res;
}
int main() {
    // char name[30];
    // printf("Hello CSC209 students!\n");
    // fgets(name, 30, stdin);
    // printf("Hi %s\n", name);
    
    //============
   
    char *path1 = "/user/include/";
    char *result1 = basename(path1);
    
    // char result1[10];
    // result1[0] = path1[0];
    printf("%s\n", result1);

}
