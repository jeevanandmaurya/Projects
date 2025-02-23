#include <stdio.h>
#include <windows.h>

// Tic Tac Toe for Terminal
/*
Board-
_ _ _
_ _ _
_ _ _

O X X
X O O
X O O

O WINS

 P1-O
 P2-X

*/
// Zoom terminal for better experience

// Initialization of variables
int inplay = 1; // 0-None 1-P1 2-P2 Player Currently InPlay
int n = 3;
char ch[3] = {'_', 'O', 'X'};
int gamestate = 1;
int state[3][3] = {0};
int x = 0, y = 0;
int pInput = 0;

void checkWinner(int state[3][3])
{

    for (int i = 0; i < 3; i++)
    {

        // Horizontal
        if (state[i][0] == inplay && state[i][0] == state[i][1] && state[i][0] == state[i][2])
        {
            gamestate = 0;
           
            printf("%c",ch[inplay]);
        }
        // // Vertical
        if (state[0][i] == inplay && state[0][i] == state[1][i] && state[0][i] == state[2][i])
        {
            gamestate = 0;
            printf("%c",ch[inplay]);
        }
    }
    // Diagonal
    // if(state[0][0]=inplay && state[0][0]==state[1][1] && state[0][0]==state[2][2]){
    //     gamestate=0;
    // }



}

void update()
{

    // Move Cursor
    // Print InPlaying
    printf("\033[14;14H%d", inplay);
    // Take Input
    printf("\033[6C");
    scanf("%d", &pInput);
    if (pInput > 0 && pInput < 10 && (!state[(pInput - 1) / 3][(pInput - 1) % 3]))
    {
        // Updating State
        state[(pInput - 1) / 3][(pInput - 1) % 3] = inplay;
        // Printing O/X
        x = 16 + 2 * ((pInput - 1) % 3);
        y = 8 + (pInput - 1) / 3;
        printf("\033[%d;%dH%c", y, x, ch[inplay]);
    }
    // Check Winner
    checkWinner(state);

    if (gamestate==0)
    {
        
    }
    


    // Switching InPlaying
    inplay = 3 - inplay;
}

int main()
{

    system("cls");
    // Initialization of variables
    // int inplay = 1; // 0-None 1-P1 2-P2 Player Currently InPlay
    // int n = 3;
    // int gamestate = 1;
    // int state[3][3] = {0};

    // Introduction and Instruction for the Game
    printf("\n\n            \033[1m\033[48;5;21mTIC TAC TOE\033[0m      \n\n");
    printf("      Player 1->O   Player 2->X\n");
    // Seperation margin
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        // Left Margin
        for (int j = 0; j < 15; j++)
        {
            printf(" ");
        }
        // Board
        for (int j = 0; j < n; j++)
        {
            switch (state[i][j])
            {
            case 1:
                printf("O ");
                break;
            case 2:
                printf("X ");
                break;

            default:
                printf("_ ");
                break;
            }
        }
        // NEXTLINE
        printf("\n");
    }

    // Seperation margin
    printf("\n\n");

    // Player Move

    for (int i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("Enter Your Move(1-9):\n");
    for (int i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("Player %d    ->\n\n", inplay);

    for (int i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("GameState   ->Ongoing \n");
    for (int i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("Result      ->NA \n");

    while (gamestate)
    {
        // // Player Input
        // scanf("%d", &pInput);
        // if (!state[pInput / 3][pInput % 3 - 1])
        // {

        //     // Updating State
        //     state[pInput / 3][pInput % 3 - 1] = inplay;
        //     // Switching InPlaying
        //     inplay = 3 - inplay;

        //     main();
        // }

        update();

    if(gamestate==0){




    }
    


    }
    printf("\007");
    // Bottom Margin
    for (int i = 0; i < 12; i++)
    {
        printf("\n");
    }

    return 0;
}