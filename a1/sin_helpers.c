// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    if (sin / 1000000000 != 0){return 1;}
    for (int i = 0; i < 9; i++){
        int divider = 1;
        for (int j = i; j < 8; j++){
            divider = divider * 10;
        }
        sin_array[i] = sin / (divider) % 10;
        
    }
    return 0;
}

// TODO: Implement check_sin
/*
 * Return 0 if the given sin_array is a valid SIN, and 1 otherwise.
 */
int check_sin(int *sin_array) {
    if (sin_array[0] != 0){//make sure not start from 0
        //to double each digit
        for (int i = 0; i < 9; i++){
            if (i % 2 != 0){
            sin_array[i] = sin_array[i] * 2;
            }
        }
        //to sum up total
        int sum = 0;
        for (int j = 0; j < 9; j++){
            if (sin_array[j]/10 == 0){ //case of single digit
                sum += sin_array[j];
            }
            else{
                sum += sin_array[j]/10;
                sum += sin_array[j]%10;
            }
        }        
        if (sum % 10 == 0){
            return 0;
        }
    }
    return 1;
}
