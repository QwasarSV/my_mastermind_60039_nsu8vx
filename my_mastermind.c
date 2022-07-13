#define RANDER 7
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int my_mastermind(char secret_code[],char code_buffer[]){

bool wrg_inp = false;
for(int i = 0;i < CODE_LENGTH;i++){//catches incorrect input
    if((int)code_buffer[i] > 57 || (int)code_buffer[i] < 48){
        wrg_inp = true;
    }
}
if(wrg_inp){
    printf("Wrong Input!\n");
    read(0, code_buffer, CODE_LENGTH);
    read(0, code_buffer, CODE_LENGTH);
}


int well_n_miss_place[2] = {};//will return the number of well placed and missplaced pieces of the code guessed by user

for(int i = 0;i < CODE_LENGTH;i++){//counts how many numbers are in the right position
    //extra conditional for when secret code is randomly generated. a number plus '0' is its ascii value
    //...typecasting a character to int will give you its ascii value
    ///...will probably be able to void this in better solution
    if(code_buffer[i] == secret_code[i] || (int)code_buffer[i] =='0'+(int)secret_code[i]){
        well_n_miss_place[0]++;//increment number of correct pieces in correct place
    }
}
for(int i = 0;i < CODE_LENGTH;i++){//counts how many pieces are in the wrong place
    for(int j = 0;j < CODE_LENGTH;j++){
        if(code_buffer[i] == secret_code[j] && code_buffer[i] != secret_code[i]){
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
    if(argc == 1)//if no entry is given, random secret code is created with rand()
    {
        for(int i = 0;i < CODE_LENGTH;i++){
            int random_number = rand() % RANDER;//RAND_MAX is already defined
            sprintf(&secret_code[i],"%c",random_number);//turns random numbers into characters
                                                        //...need to fix formatting later
        }
    }
    else
    {
    for(int i = 0;i < CODE_LENGTH;i++){//if the code is entered correclty in command line argument, convert it to array of integers
        secret_code[i] = argv[1][i];//argv[1] is CLA, i represents individual characters
    }
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");//opening line to game

    char code_buffer[CODE_LENGTH + 1];//plus one to account for null terminated character
    printf("Round %d\n",0);//initiates round 0
    for(int i = 1;i < MAX_ATTEMPTS;i++){/*will call the my_mastermind function a max of MAX_ATTEMPTS (10) times
                                          ...will print the return value of my_mastermind funciton--either the number of well/missplaced
                                             pieces of the code
                                          ...if the code is guessed correctly, will print "Congratz! You did it!" and end the game*/
        
        read(0, code_buffer, CODE_LENGTH);
        int res = my_mastermind(secret_code, code_buffer);
        if(res == EXIT_SUCCESS){//all pieces match
            printf("Congratz! You did it!\n");
            return EXIT_SUCCESS;
        }
        else{
            printf("Round %d\n",i);//dont know why this makes it work
            read(0, code_buffer, CODE_LENGTH);//dont know why this makes it work
        }
    }
return 0;
}