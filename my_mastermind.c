#include "my_mastermind.h"

int my_mastermind(char secret_code[]){

bool valid_input = false;//will be made true if the user input is valid
char valid_code[4];//the user input will be transcribed into this
while (valid_input == false) {
    // get user input
    char usr_input[10];
    int n_bytes = read(0, usr_input, 10);
    // validate input
    if (n_bytes != CODE_LENGTH + 1) {/*if number of characters is not 4 (valid secret code), read(0, input, 10)
                        is called again, and will be called until a valid input is entered.
                        ...n_bytes is 5 because of?? null terminator, enter key??
                        ...further checks are implemented below to determine if each of the 4 characters
                        are numbers (between ascii values 48 and 55-- digits 0-7)*/            
        printf("Wrong input!\n");
        continue;
    }
    /*if each of the 4 input characters are string versions of the digits 0-7, then the variable
        valid input will be made true, halting the execution of the while loop
        ...after while loop is terminated, the valid input (guess of the secret code) will be fed into the my_mastermind
            function to determine whether the guess matches the actual secret code*/
    if  ( 
           (usr_input[0] >= 48 && usr_input[0] <= 55) 
        && (usr_input[1] >= 48 && usr_input[1] <= 55)
        && (usr_input[2] >= 48 && usr_input[2] <= 55) 
        && (usr_input[3] >= 48 && usr_input[3] <= 55)
        )
        {
        valid_input = true; //if above conditions are true, valid input will be true
        //transfers usr_input to variable outside of while loop, which will be compared to actul secret code
        for(int i = 0;i < CODE_LENGTH;i++){
            valid_code[i] = usr_input[i];
        }
        }
    else{
        printf("Wrong input!\n"); /*if one or more conditions  is false, "Wrong Inpiut!
                                    will be printed to the standard output, and the read() function
                                    will be called again until valid input is entered into terminal"*/
    }
}


int well_n_miss_place[2] = {};//will return the number of well placed and missplaced pieces of the code guessed by user

for(int i = 0;i < CODE_LENGTH;i++){//counts how many numbers are in the right position
    //extra conditional for when secret code is randomly generated. a number plus '0' is its ascii value
    //...typecasting a character to int will give you its ascii value
    ///...will probably be able to void this in better solution
    if(valid_code[i] == secret_code[i] || (int)valid_code[i] =='0'+(int)secret_code[i]){
        well_n_miss_place[0]++;//increment number of correct pieces in correct place
    }
}
for(int i = 0;i < CODE_LENGTH;i++){//counts how many pieces are in the wrong place
    for(int j = 0;j < CODE_LENGTH;j++){
        if(valid_code[i] == secret_code[j] && valid_code[i] != secret_code[i]){
            well_n_miss_place[1]++;//increment number of correct pieces in wrong place
        }
    }
}
if(well_n_miss_place[0] == CODE_LENGTH){//returns EXIT_SUCCESS if the all the pieces match--the main function will end the game
    return EXIT_SUCCESS;
}

printf("Well placed pieces: %d\nMisplaced pieces: %d\n---\n",well_n_miss_place[0],well_n_miss_place[1]);
return EXIT_FAILURE;
}