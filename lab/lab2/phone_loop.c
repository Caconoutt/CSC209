#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char phone[11];
    scanf("%s", phone);
    int index;
    int error_check = 0;

    while (scanf("%d", &index) != EOF){
        if (index == -1){
        printf("%s\n", phone);
        }
        else if ((index > -1) && (index < 10)){
        printf("%c\n", phone[index]);
        }
        else{
        printf("ERROR\n");
        error_check = 1;
        }
    }
    if (error_check == 1){
        return 1;
    }
    return 0;
}