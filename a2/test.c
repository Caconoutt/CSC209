#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "friends.h"

int main(){
    //User **large_array = NULL;

    User *user1 = malloc(sizeof(User));
    strcpy(user1->name, "Amy");

    User *user2 = malloc(sizeof(User));
    strcpy(user2->name, "Ben");

    User *user3 = malloc(sizeof(User));
    strcpy(user3->name, "Cinch");
    //user2 and user3 are friends to user 1
    user1->friends[0] = user2;
    user2->friends[0] = user1;
    user1->friends[1] = user3;
    user3->friends[0] = user1;
    for (int i = 0; i < MAX_FRIENDS; i++){
        User *temp = user1->friends[i];
        if(temp != NULL){
            printf("%s\n", temp->name);
        }
    }
    printf("After:\n");
    //delete user2 from user1 friend list
    for (int i = 0; i < MAX_FRIENDS; i++){
        User *temp = user2->friends[i];
        //printf("%s\n", temp->name);
        if (temp != NULL){
            int pos = 0;
            //printf("%d\n", pos);
            for (int j = 0; j < MAX_FRIENDS; j++){
                //temp is user1
                if (temp->friends[j] != NULL && strcmp(temp->friends[j]->name, user2->name) == 0){
                    pos = j;
                    //printf("%d\n", pos);
                    for(int k = pos; k < MAX_FRIENDS - 1; k++){
                        temp->friends[k] = temp->friends[k + 1];
                        //printf("%s\n", temp->friends[k]->name);
                    }
                }
                break;
            }
        }
        break;
    }

    for (int i = 0; i < MAX_FRIENDS; i++){
        User *temp = user1->friends[i];
        if(temp != NULL){
            printf("%s\n", temp->name);
        }
    }



}