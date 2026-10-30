#include<stdio.h>
#include<string.h>
#include<time.h>

void print_mark(char mark) {
    if (mark == 'X') {
        printf("\033[31mX\033[0m"); //red X
    }
    else if (mark == 'O') {
        printf("\033[34mO\033[0m"); //blue o
    }
    else {
        printf("%c", mark); //empty square with its positioning
    }
}

void print_board(char board[]) {
    printf("\n");

    printf(" ");
    print_mark(board[0]);
    printf(" | ");
    print_mark(board[1]);
    printf(" | ");
    print_mark(board[2]);
    printf("\n---+---+---\n");

    printf(" ");
    print_mark(board[3]);
    printf(" | ");
    print_mark(board[4]);
    printf(" | ");
    print_mark(board[5]);
    printf("\n---+---+---\n");

    printf(" ");
    print_mark(board[6]);
    printf(" | ");
    print_mark(board[7]);
    printf(" | ");
    print_mark(board[8]);
    printf("\n\n");
}

int main()
{
    //positioning the squares of the game
    //the numbers show which squares are still empty
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char player[50]; //stores player's name

    char psign = 'X';

    int choice; //stores player's choice between 1-9th squares

    int game_over = 0;

    int position; //defines the postion of the player's choice in the array

    char player1[50];
    char player2[50];

    char game_result[100];

    char filename[30] = "GAME RESULT HISTORY.txt";

    char final_board[100];

    printf("\n");

    printf("ENTER THE 1ST-PLAYER NAME: ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = '\0';
    
    printf("ENTER THE 2ND-PLAYER NAME: ");
    fgets(player2, sizeof(player2), stdin);
    player2[strcspn(player2, "\n")] = '\0';

    strcpy(player, player1);

    //prints the title of the game
    printf("\n\n");
    printf("\033[107mTIC-TAC_TOE\033[0m\n");

    while(game_over == 0) {

        //showing the board
        print_board(board);
        
        //asking the current player to choose a square
        printf("\nPLAYER-%s, CHOOSE A SQUARE(1-9): ", player);

        //checks that the player input any number or not
        if(scanf("%d", &choice) != 1) {
            printf("PLEASE ENTER A NUMBER: \n");
            return 1;
        }

        //check that whether the player inputs a number betwwen 1 to 9 or not
        if(choice < 1 || choice > 9) {
            printf("PLEASE CHOOSE A NUMBER FROM 1 TO 9\n");
            continue;
        }

        //converts the player's choice into array's position
        position = choice - 1;

        //checks if the square which has choosen by the player is already taken by another player or not
        if(board[position] == 'X' || board[position] == 'O') {
            printf("THE POSITION IS ALREADY TAKEN!");
            continue;
        }

        //putting the player's game-mark in his choosed position
        board[position] = psign;

        //checking all the rows and all the coloumns for a win
        if ((board[0] == psign && board[1] == psign && board[2] == psign) ||
            (board[3] == psign && board[4] == psign && board[5] == psign) ||
            (board[6] == psign && board[7] == psign && board[8] == psign) ||
            (board[0] == psign && board[3] == psign && board[6] == psign) ||
            (board[1] == psign && board[4] == psign && board[7] == psign) ||
            (board[2] == psign && board[5] == psign && board[8] == psign) ||
            (board[0] == psign && board[4] == psign && board[8] == psign) ||
            (board[2] == psign && board[4] == psign && board[6] == psign)) {

            //showing the final board
            print_board(board);

            //showing the result
            printf("PLAYER-%s WINS THE GAME\n\n", player);
            
            snprintf(game_result, sizeof(game_result), "PLAYER-1: %s\t\tPLAYER-2: %s\nPLAYER-%s WINS THE GAME\n\n", player1, player2, player); //saving the result in a string

            //storing the time into a variable for save the game result with more result
            time_t now = time(NULL);
            struct tm *local = localtime(&now);

            //checking whether the time is still null value or not
            if(local == NULL) {
                return 1;
            }

            char date_time[100];
            if(strftime(date_time, sizeof(date_time), "DATE AND TIME: %Y-%m-%d, %H:%M:%S", local) == 0) {
                return 1;
            }

            //saving the result in a file for saving the game history
            FILE *file = fopen(filename, "a"); //opening the file

            fprintf(file, "%s\n", date_time);
            fprintf(file, "%s", game_result); //printing the result in the file

            fclose(file); //closing the file

            //stopping the game
            game_over = 1;
        } else {
                
            //checking that the all of the squares are user or not
            int board_full = 1;
                
            //checking all squaers
            for(int i = 0; i < 9; i++) {
                if (board[i] != 'X' && board[i] != 'O') {
                    board_full = 0;
                }
            }

            if (board_full == 1) {
                print_board(board);
                printf("\nITS A DRAW\n\n");

                snprintf(game_result, sizeof(game_result), "PLAYER-1: %s\t\tPLAYER-2: %s\nTHE MATCH RESULT IS A DRAW\n\n", player1, player2); //saving the result in a string

                time_t now = time(NULL);
                struct tm *local = localtime(&now);

                //checking whether the time is still null value or not
                if(local == NULL) {
                    return 1;
                }

                char date_time[100];
                if(strftime(date_time, sizeof(date_time), "DATE AND TIME: %Y-%m-%d, %H:%M:%S", local) == 0) {
                    return 1;
                }

                //saving the result in a file for saving the game history
                FILE *file = fopen(filename, "a"); //opening the file

                fprintf(file, "%s\n", date_time);
                fprintf(file, "%s", game_result); //printing the result in the file

                fclose(file); //closing the file

                game_over = 1;
            } else {

                //change to the other player
                if (strcmp(player, player1) == 0) {
                    strcpy(player, player2);
                } else {
                    strcpy(player, player1);
                }

                if (psign == 'X') {
                    psign = 'O';
                } else {
                    psign = 'X';
                }
            }
        }    
    }

    return 0;
}