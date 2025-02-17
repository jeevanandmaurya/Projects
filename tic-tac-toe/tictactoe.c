#include <stdio.h>

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

void printBoard(int *entries, char *playerChar, int entriCount, int charCount)
{

    for (int i = 0; i < entriCount; i++)
    {
                if ((i + 1) % 3 == 0)
                {
                    printf(" %c\n", playerChar[entries[i]]);
                }
                else
                {
                    printf(" %c ", playerChar[entries[i]]);
                }
            
        
    }
}

int checkWinner(int *entries, int entriCount)
{
    int count;
    for (int i = 0; i < entriCount; i += 3)
    {
        for (int j = 1; j < 3; j++)
        {

            // Horiontal OOO
            count = 0;
            if ((entries[0 + i ] == j && entries[1 + i] == j && entries[2 + i] == j))
            {

                count++;
                if (count)
                {
                    return j;
                }
            }
            // Vertical OOO
            count = 0;
            if ((entries[0 + i/3] == j && entries[3 + i/3] == j && entries[6 + i/3] == j))
            {

                count++;
                if (count)
                {
                    return j;
                }
            }

            // Diagonal forwardslash
            count = 0;
            if ((entries[2] == j && entries[4] == j && entries[6] == j))
            {

                count++;
                if (count)
                {
                    return j;
                }
            }
            // Diagonal backslash
            count = 0;
            if ((entries[0] == j && entries[4] == j && entries[8] == j))
            {

                count++;
                if (count)
                {
                    return j;
                }
            }
        }
    }

    // Manual Checking
    //  // Horizontal
    //  for (int i = 1; i < 3; i++)
    //  {
    //      if ((entries[0] == i && entries[1] == i && entries[2] == i) || (entries[3] == i && entries[4] == i && entries[5] == i) || (entries[6] == i && entries[7] == i && entries[8] == i))
    //      {
    //          return i;
    //      }
    //  }
    //  // Vertical
    //  for (int i = 1; i < 3; i++)
    //  {
    //      if ((entries[0] == i && entries[3] == i && entries[6] == i) || (entries[1] == i && entries[4] == i && entries[7] == i) || (entries[2] == i && entries[5] == i && entries[8] == i))
    //      {
    //          return i;
    //      }
    //  }

    return 0;
}

int main(int argc, char const *argv[])
{

    int moves = 0;
    // 1-O 2-X
    int turn = 1;
    int GameEnd = 0;
    char playerChar[] = {'_', 'O', 'X'};

    printf("Positions\n1 2 3\n4 5 6\n7 8 9\n");

    printf("\nGame Started\n");

    int entries[9];
    for (int i = 0; i < 9; i++)
    {
        // 0-empty 1-O 2-X
        entries[i] = 0;
    }
    printBoard(entries, &playerChar[0], 9, 1);
    int enteredPos;

    while (!GameEnd)
    {

        printf("\n\nPlayer %d Turn - %c\n", turn, playerChar[turn]);
        printf("Enter Position: \n");
        scanf("%d", &enteredPos);

        while (entries[enteredPos - 1] != 0 || enteredPos > 9)
        {
            printf("Invalid Input, Retry\n");
            printf("Enter Position: \n");
            scanf("%d", &enteredPos);
        }
        entries[enteredPos - 1] = turn;

        moves++;
        turn = 3 - turn;
        printBoard(entries, playerChar, 9, 3);

        GameEnd = checkWinner(entries, 9);

        if (moves == 9 && GameEnd == 0)
        {
            GameEnd = 3;
        }
    }
    if (GameEnd == 3)
    {
        printf("\nGame Draw!!!!!\n");
    }
    else
    {
        printf("\nGame End!!!!!\nWinner is Player: %d (%c%c%c)\n", GameEnd, playerChar[GameEnd], playerChar[GameEnd], playerChar[GameEnd]);
    }

    return 0;
}