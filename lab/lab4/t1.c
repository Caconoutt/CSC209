#include <stdio.h>
#include <string.h>

int main(){
    char s[] = "Apples?..?";
    int result = 0;
    int n = strlen(s); //n is the length of string without null character
    while(s[n - 1] == '?'){
        result++;
        n--;
    }
    printf("%d ", n);
    printf("%d \n", result);
    char new_s[n];
    strncpy(new_s, s, n);
    new_s[n] = '\0';
    printf("%s\n", new_s);
    // return 0;
}