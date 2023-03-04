#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char phone[11];
    scanf("%s", phone);
    int index;
    scanf("%d", &index);

    if (index == -1){
        printf("%s", phone);
    }
    else if ((index > -1) && (index < 10)){
        printf("%c", phone[index]);
    }
    else{
        printf("ERROR");
        return 1;
    }

    return 0;
}