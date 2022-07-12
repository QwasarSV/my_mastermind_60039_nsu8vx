#define RAND_MAX 7
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int my_mastermind(int rand_code[]){

int well_n_miss_place[2] = {};//will return the number of well placed and missplaced pieces of the code guessed by user
char code_buffer[CODE_LENGTH + 1];//plus one to account for null terminated character
read(0, code_buffer, CODE_LENGTH);
printf(">%s",code_buffer);
printf("\n");

for(int i = 0;i < CODE_LENGTH;i++){//counts how many numbers are in the right position
    if(atoi(&code_buffer[i]) == rand_code[i]){
        well_n_miss_place[0]++;
    }
}
for(int i = 0;i < CODE_LENGTH;i++){//counts how many pieces are in the wrong place
    for(int j = 0;j < CODE_LENGTH;j++){
        if(atoi(&code_buffer[i]) == rand_code[j] && atoi(&code_buffer[i]) != rand_code[i]){
            well_n_miss_place[1]++;
        }
    }
}

if(well_n_miss_place[0] == CODE_LENGTH){//returns EXIT_SUCCESS if the all the pieces match--the main function will end the game
    return EXIT_SUCCESS;
}

printf("Well placed pieces: %d\nMisplaced pieces: %d\n",well_n_miss_place[0],well_n_miss_place[1]);
return EXIT_FAILURE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
    if(!argc){
        return 0;
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n");//opening line to game
    int rand_code[4] = {};//will hold the secret code in an array of integers
    if(strlen(argv[1]) != CODE_LENGTH){/*if no code is entered, or the entered code is not
                                         the desired code length (4), pseudo-random code will be generated*/
        for(int i = 0;i < CODE_LENGTH;i++){
            rand_code[i] = rand() % RAND_MAX;//rand() % RAND_MAX is syntax to create a psedo-random number 0 - RAND_MAX
        }
    }
    for(int i = 0;i < CODE_LENGTH;i++){//if the code is entered correclty in command line argument, convert it to array of integers
        rand_code[i] = atoi(&argv[1][i]);
    }
    for(int i = 0;i < MAX_ATTEMPTS;i++){/*will call the my_mastermind function a max of MAX_ATTEMPTS (10) times
                                          ...will print the return value of my_mastermind funciton--either the number of well/missplaced
                                             pieces of the code
                                          ...if the code is guessed correctly, will print "Congratz! You did it!" and end the game*/
        printf("Round %d\n",i);
        if(my_mastermind(rand_code) == EXIT_SUCCESS){
            printf("Congratz! You did it!\n");
            return EXIT_SUCCESS;
        }
    }
    return 0;
}