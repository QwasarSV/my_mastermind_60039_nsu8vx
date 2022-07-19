#define CODE_LENGTH 4
#define RANDER 7

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int my_mastermind(char secret_code[]){

bool valid_input = false;//will be made true if the user input is valid
char valid_code[4];//the user input will be transcribed into this
while (valid_input == false) {
    // get user input
    char usr_input[10];
    read(0, usr_input, 10);
    // validate input
    int length = strlen(usr_input);//gets number of characters in the string
    if (length != 8) {/*if number of characters is not 4 (valid secret code), read(0, input, 10)
                        is called again, and will be called until a valid input is entered.
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
///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
    char secret_code[4] = {};//will hold the secret code in an array of integers
    int max_attempts = 10;
    bool c_flag = false;//will be used to determine whether program needs to produce a random secret code***
    srand(time(NULL));//time() produces, in seconds, the time since january 1, 1970, providing a unique seed value for rand() each time program is called
    if(argc == 1)//if no entry is given, random secret code is created with rand(),and max attempts = 10
    {
        
        for(int i = 0;i < CODE_LENGTH;i++){
            int random_number = rand() % RANDER;//RAND_MAX is already defined
            sprintf(&secret_code[i],"%c",random_number);//turns random numbers into characters
                                                        //...need to fix formatting later
        }
    }
    else
    {
    for(int i = 1;i < argc;i++){//will determine what flags (-c, -t, or both)...
        if(argv[i][0] == '-'){//detects that a flag is present... the next character after hyphen will be c or t
            char flag = argv[i][1];//holds either a c or t
            switch(flag){
            //switch statement will trigger the action of one of two cases... a c or a t flag
            case 'c':
                for(int j = 0;j < CODE_LENGTH;j++){
                    secret_code[j] = argv[i + 1][j];//transcribes the secret code provided in command line to a string array (each character representing an integer 0-7)
                    c_flag = true;//will stop the if statement below the loop from creating a random value for the secret code
                }
                break;

            case 't':
                max_attempts = atoi(argv[i + 1]);//i is the flag (t in this case), so i + 1 represents the next CLA, the specified max attempts
                                                //...i + 1 would represent the specified secret code in the context of the c flag in the above case
                break;
            }
        }
    }
    if(c_flag == false){//***if there was only a -t flag, then a random secret code will be genreated
        for(int i = 0;i < CODE_LENGTH;i++){
            int random_number = rand() % RANDER;//RAND_MAX is already defined
            sprintf(&secret_code[i],"%c",random_number);//turns random numbers into characters
        }
    }
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");//opening line to game

    for(int i = 1;i < max_attempts;i++){/*will call the my_mastermind function a max of (max_attempts) times -default is 10
                                          ...will print the return value of my_mastermind funciton--either the number of well/missplaced
                                             pieces of the code
                                          ...if the code is guessed correctly, will print "Congratz! You did it!" and end the game*/
        
        printf("Round %d\n",i);
        int result = my_mastermind(secret_code);
        if(result == EXIT_SUCCESS){//all pieces match
            printf("Congratz! You did it!\n");
            return EXIT_SUCCESS;
        }
    }
return 0;
}