#define RANDER 7
#include "my_mastermind.h"

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