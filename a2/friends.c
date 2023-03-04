#include "friends.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delete_post(User *);
void delete_friend(User *);

/*
 * Create a new user with the given name.  Insert it at the tail of the list
 * of users whose head is pointed to by *user_ptr_add.
 *
 * Return:
 *   - 0 if successful
 *   - 1 if a user by this name already exists in this list
 *   - 2 if the given name cannot fit in the 'name' array
 *       (don't forget about the null terminator)
 */
int create_user(const char *name, User **user_ptr_add) {
    //return 2: too long user name
    //name is an array, use string length to compare the value
    int name_length = strlen(name);
    if (name_length >= MAX_NAME){ 
        return 2;
    }

    //return 1: existed user name
    User *curr = *user_ptr_add;
    while (curr != NULL){
        //strcmp() returns 0 when two strings are equal, otherwise not equal
        if (strcmp(curr->name, name) == 0){
            return 1;
        }
        curr = curr->next;
    }

    //return 0: create new user
    User *new_user = malloc(sizeof(User));
    //error handling
    if (new_user == NULL){
        perror("malloc");
        exit(1);
    }
    //initialize user attribute
    strcpy(new_user->profile_pic, "");
    new_user->first_post = NULL;
    for (int i = 0; i < MAX_FRIENDS; i++){
        new_user->friends[i] = NULL;
    }
    new_user->next = NULL;
    

    strcpy(new_user->name, name);
    User *curr1 = *user_ptr_add;
    //first user in the linked list
    if (curr1 == NULL){
        user_ptr_add[0] = new_user;
    }
    //already exists some users
    else{
        while(curr1->next != NULL){
        curr1 = curr1->next;
        }
        curr1->next = new_user;
    }
    return 0;
}


/*
 * Return a pointer to the user with this name in
 * the list starting with head. Return NULL if no such user exists.
 *
 * NOTE: You'll likely need to cast a (const User *) to a (User *)
 * to satisfy the prototype without warnings.
 */
User *find_user(const char *name, const User *head) {
    while(head != NULL){
        if(strcmp(head -> name, name)==0){
            return (User *)head;
        }
        head = head->next;
    }
    return NULL;
}


/*
 * Print the usernames of all users in the list starting at curr.
 * Names should be printed to standard output, one per line.
 */
void list_users(const User *curr) {
    if (curr != NULL){
        printf("User List\n");
        while(curr != NULL){
        printf("\t%s\n", curr->name);
        curr = curr->next;
        }
    }
}


/*
 * Change the filename for the profile pic of the given user.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the file does not exist or cannot be opened.
 *   - 2 if the filename is too long.
 */
int update_pic(User *user, const char *filename) {
    FILE *output = NULL;
    int error = 0;

    //return 2: filename is too long
    if(strlen(filename) >= MAX_NAME){return 2;}

    //return 1: fail to open or not exist
    output = fopen(filename, "r");
    if (output == NULL){return 1;}
    //issue of closing file
    error = fclose(output);
    if (error != 0){return 1;}

    //return 0: succeed
    strcpy(user->profile_pic, filename);
    return 0;
}


/*
 * Make two users friends with each other.  This is symmetric - a pointer to
 * each user must be stored in the 'friends' array of the other.
 *
 * New friends must be added in the first empty spot in the 'friends' array.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the two users are already friends.
 *   - 2 if the users are not already friends, but at least one already has
 *     MAX_FRIENDS friends.
 *   - 3 if the same user is passed in twice.
 *   - 4 if at least one user does not exist.
 *
 * Do not modify either user if the result is a failure.
 * NOTE: If multiple errors apply, return the *largest* error code that applies.
 */
int make_friends(const char *name1, const char *name2, User *head) {
    
    //return 4: at least one user does not exist
    int exist1 = 0;
    int exist2 = 0;
    User *curr = head;
    User *user1 = NULL;
    User *user2 = NULL;
    while (curr != NULL){
        if (strcmp(curr->name, name1) == 0){
            exist1 = 1;
            user1 = curr;
        }
        if (strcmp(curr->name, name2) == 0){
            exist2 = 1;
            user2 = curr;
        }
        curr = curr->next;
    }
    if (exist1 == 0 || exist2 == 0){return 4;}

    //return 3: same name
    if (strcmp(name1, name2) == 0){return 3;}

    //return 2: not friend, but one has max friend
    int user1_f_check = 0;
    int user1_last_indext = 0;
    int user2_f_check = 0;
    int user2_last_indext = 0;

    for(int i = 0; i < MAX_FRIENDS; i++){
        if(user1->friends[i] == NULL){
            user1_last_indext = i;
            user1_f_check = 1;
        }
    }
    for(int i = 0; i < MAX_FRIENDS; i++){
        if(user2->friends[i] == NULL){
            user2_last_indext = i;
            user2_f_check = 1;
        }
    }
    if(user1_f_check == 0 || user2_f_check == 0){return 2;}


    //return 1: two users are already friend
        //check if user2 is user1's friend
    
    for(int i = 0; i < MAX_FRIENDS; i++){
        if(user1->friends[i] != NULL && strcmp(user1->friends[i]->name, name2) == 0){
            return 1;
        }
    }
        //if user2 is user1's friend, then user1 must be user2's friend and added in,
        //so we only check one side

    //return 0: succeed !!
    user1->friends[user1_last_indext] = user2;
    user2->friends[user2_last_indext] = user1;
    return 0;
}


/*
 * Print a user profile.
 * For an example of the required output format, see the example output
 * linked from the handout.
 * Return:
 *   - 0 on success.
 *   - 1 if the user is NULL.
 */
int print_user(const User *user) {
    if (user == NULL){return 1;}
    //profile pic
    FILE *input = NULL;
    int error = 0;
    
    //case of user doesn't upload the pic, or the file of pic no long existed
    if (strlen(user->profile_pic) != 0){
        input = fopen(user->profile_pic, "r");
    }
    
    //only read the pic if the file is opened successfully
    if (input != NULL){
        char string[100];
        while(fgets(string, 100, input)){
        printf("%s", string);
        }
        printf("\n");

        error = fclose(input);
        if (error != 0){
        fprintf(stderr, "Error closing file!");
        return 1; //error of closing file
        }
    }

    printf("Name: %s\n", user->name);
    printf("------------------------------------------\n");
    printf("Friends:\n");
    for (int i = MAX_FRIENDS - 1; i >= 0 ; i--){
        if (user->friends[i] != NULL){
            printf("%s\n", user->friends[i]->name);
        }
    }
    
    printf("------------------------------------------\n");
    printf("Posts:\n");
    Post *first_post = user->first_post;
    while(first_post != NULL){
        printf("From: %s\n", first_post->author);
        printf("Date: %s\n", ctime(first_post->date));
        printf("%s\n", first_post->contents);
        if (first_post->next != NULL){printf("\n===\n\n");}
        first_post = first_post->next;
    }
    printf("------------------------------------------\n");


    return 0;
}


/*
 * Make a new post from 'author' to the 'target' user,
 * containing the given contents, IF the users are friends.
 *
 * Insert the new post at the *front* of the user's list of posts.
 *
 * 'contents' is a pointer to heap-allocated memory - you do not need
 * to allocate more memory to store the contents of the post.
 *
 * Return:
 *   - 0 on success
 *   - 1 if users exist but are not friends
 *   - 2 if either User pointer is NULL
 */
int make_post(const User *author, User *target, char *contents) {
    //return 2: either pointer is NULL
    if (author == NULL || target == NULL){
        return 2;
    }

    //return 1: not friend
    int friend_checker = 0;
    for (int i = 0; i < MAX_FRIENDS; i++){
        if (author->friends[i] != NULL && strcmp(author->friends[i]->name, target->name) == 0){
            friend_checker = 1;
        }
    }
    if (friend_checker == 0){return 1;}
    
    //return 0: add the post
    Post *new_post = malloc(sizeof(Post));
    //error handling
    if (new_post == NULL){
        perror("malloc");
        exit(1);
    }
    new_post->contents = NULL;
    new_post->date = NULL;
    new_post->next = NULL;
    strcpy(new_post->author,author->name);
    new_post->contents = contents;
    //need to malloc the time
    time_t *new_date = malloc(sizeof(time_t));
    //error handling
    if (new_date == NULL){
        perror("malloc");
        exit(1);
    }
    *new_date = time(NULL);
    new_post->date = new_date; //get system current time
    new_post->next = target->first_post;
    target->first_post = new_post;
    return 0;
}


/*
 * From the list pointed to by *user_ptr_del, delete the user
 * with the given name.
 * Remove the deleted user from any lists of friends.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if a user with this name does not exist.
 */
int delete_user(const char *name, User **user_ptr_del) {
    User *head = *user_ptr_del;
    User *d_user = NULL;

    //return 1: user not exists
    while (head != NULL){
        if (strcmp(head->name, name) == 0){
            d_user = head;
            break;
        }
        head = head->next;
    }
    if (d_user == NULL){return 1;}

    //return 0: user exists and we need to delete it

    //delete the post
    delete_post(d_user);
    
    //delete the user name in their friends
    delete_friend(d_user);
    

    //delete the user in the whole linked list
    User *head1 = *user_ptr_del; //the first node
    User *head2 = *user_ptr_del;
    //case1: d_user is the head
    if (strcmp(head1->name, name) == 0){
        user_ptr_del[0] = (user_ptr_del[0])->next;
        //*user_ptr_del = (*user_ptr_del)->next;
        free(d_user);
        return 0;
    }
    //case2: d_user is the end
    User *head3 = *user_ptr_del; //the last node
    User *prev = NULL;
    while ((head3->next) != NULL){
        prev = head3;
        head3 = head3->next;
    }
    if (strcmp(head3->name, name) == 0){
        prev->next = NULL;
        free(d_user);
        return 0;
    }
    //case3: d_user is the middle
    else{
        User *duser_front = NULL;
        User *duser_back = d_user->next;
        while(head2->next != NULL){
            if (strcmp(head2->next->name, name) == 0){
            duser_front = head2;
            break; 
            }
        head2 = head2->next;
        }
        duser_front->next = duser_back;
    }
    //free the d_user
    free(d_user);
    return 0;
}

/*
 * This helper function is intended to help delete_user about post
 * It will free the post->date, post->content, post in heap memorry
 */
void delete_post(User *d_user){
    Post *first_post = d_user->first_post;
    //check the user has post
    if (first_post != NULL){
        //to free the post->content, and post->date
        //case: only 1 post
        if (first_post->next == NULL){
            free(first_post->contents);
            free(first_post->date);
            Post *previous_post = first_post;
            first_post = NULL;
            free(previous_post);
        }

        //case: more than 1 post
        while(first_post != NULL){
            free(first_post->contents);
            free(first_post->date);
            Post *previous_post = first_post;
            first_post = first_post->next;
            free(previous_post);
        }
    }
}

/*
 * This helper function is intended to help delete_user about friends array
 * It will delete the d_user pointer from all users that are in d_user's friends array
 * The deleted pointer will be replaced by NULL
 * The order of friend will be different
 */

void delete_friend(User *d_user){
    for (int i = 0; i < MAX_FRIENDS; i++){
        User *temp = d_user->friends[i]; //temp is user in d_user's friends array
        if (temp != NULL){
            for (int j = 0; j < MAX_FRIENDS; j++){
                if (temp->friends[j] != NULL && strcmp(temp->friends[j]->name, d_user->name) == 0){
                    temp->friends[j] = NULL;
                    break;
                }
            }
        }
    }
}