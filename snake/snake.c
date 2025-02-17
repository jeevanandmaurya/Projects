#include <stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <Windows.h>

// 30*30 Blocks
// BLOCK- 0 or N
// 0-Empty
// N-Filled(1-SnakeBlock/2-FoodBlock/3-Explosive)

int gameover = 0;
int snakeLen = 1;
int row[30], col[30];
int velX = 0, velY = 0;
int score = 0;
int time = 0;
int block[900];
int randPos=0;
int fcount=0;
int food[9]={
    35,45,55,
    455,465,475,
    835,845,855
};
// O++++++++++

void keyinput(char input)
{
    // printf("Press a key (W = Up, A = Left, S = Down, D = Right, Q = Quit):\n");
    // Reads a character without Enter

    switch (input)
    {
    case 'w':
        // case 'W':
        if(velY == 0)velY = -1;
        velX = 0;
        break;
    case 'a':
        // case 'A':
        if(velX == 0)velX = -1;
        velY = 0;
        break;
    case 's':
        // case 'S':
        if(velY == 0)velY = 1;
        velX = 0;
        break;
    case 'd':
        // case 'D':
        if(velX == 0)velX = 1;
        velY = 0;
        break;
    case 'q':
        //  case 'Q':
        //  gameover = 1;

    default:
        printf("Invalid key! Use W/A/S/D to move, Q to quit.\n");
    }
}

int index(int row, int col)
{

    return (row - 1) * (30) + col - 1;
}

void GameLoop()
{
    system("cls");
    printf("SCORE-> %d\n", score);
    // KeyControll
    if (_kbhit())
    {

        char input = _getch();
        keyinput(input);
    }

    // move
    // Resenting old block
    // b3->b2 b2->b1 b1->bnew

    // removing last block
    int tempCol = col[snakeLen-1], tempRow = row[snakeLen-1];

    tempCol += velX;
    if (tempCol > 30 || tempCol < 1)
    {
        gameover=1;
        return;
        //tempCol = tempCol - velX * 30;
    }
    tempRow += velY;
    if (tempRow > 30 || tempRow < 1)
    {
        tempRow = tempRow - velY * 30;
    }
    // Updating new Block
    if (block[index(tempRow, tempCol)] == 2)
    {
        score++;
        snakeLen++;
        fcount=0;
        row[snakeLen - 1]=tempRow;
        col[snakeLen - 1]=tempCol;
        //Stop all blocks and add new block in front
        block[index(row[snakeLen - 1], col[snakeLen - 1])] = 1;

    }else if (block[index(tempRow, tempCol)] == 1)
    {
        gameover=1;
        return;
    }
    else
    {
        //removing tail(last block-firstindex)
        block[index(row[0], col[0])] = 0;
        //shifting blocks
        for (int i = 0; i <snakeLen-1; i++)
        {
            row[i] = row[i + 1];
            col[i] = col[i + 1];
            block[index(row[i], col[i])] = 1;
        }
        row[snakeLen-1]=tempRow;
        col[snakeLen-1]=tempCol;
        block[index(row[snakeLen-1],col[snakeLen-1])] = 1;
    }

   

    // Updating new Block`s Instance


    // Printing
    for (int i = 0; i <= 31; i++)
    {
        printf(" - ");
    }

    // printing blocks
    for (int i = 0; i < 900; i++)
    {

        if (i % 30 == 0)
        {
            printf("\n | ");
        }

        switch (block[i])
        {

        case 1:
            printf(" O ");
            break;
        case 2:
            printf(" o ");
            break;
        case 3:
            printf("x");
            break;

        default:
            printf("   ");
            break;
        }
        if ((i + 1) % 30 == 0)
        {
            printf(" |");
        }
    }

    printf("\n");
    for (int i = 0; i <= 31; i++)
    {
        printf(" - ");
    }
    printf("\n VelX<%d> VelY<%d> row[0]<%d> col[0]<%d>", velX, velY, row[0], col[0]);
    for (int i = 0; i < snakeLen; i++)
    {
       // printf("\nrow[%d]<%d> col[%d]<%d> block<%d>", i, row[i], i, col[i], block[(row[i] - 1) * (30) + col[i] - 1]);
    }

    printf("\n time<%d>", time);

    // system("cls");

    // Food
    if (fcount==0)
    {
        while (block[food[randPos]]!=0)
        {
            randPos=rand()%9;
        }
        block[food[randPos]]=2;
        fcount=1;        
    }
    


}

int main()
{

    //Handling text cursor flashing
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Get current cursor settings
    cursorInfo.bVisible = FALSE;                     // Set the cursor to invisible
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    // system("cls");

    
    // Initializing Blocks
    for (int i = 0; i < 900; i++)
    {
        block[i] = 0;
    }
    // Initializing Snake with length=snakeLen
    for (int i = 0; i < snakeLen; i++)
    {
        row[i] = 15;
    }
    for (int i = 0; i < snakeLen; i++)
    {
        col[i] = 15 + i;
    }
    for (int i = 0; i < snakeLen; i++)
    {
        block[index(row[i], col[i])] = 1;
    }

    velX = 1;
    velY = 0;

    // Food
    randPos  = rand()%9;
    // block[index(food[randPos][0],food[randPos][1])]=2;
    block[food[randPos]]=2;
    fcount=1;


    while (gameover == 0)
    {

        GameLoop();
        Sleep(100);
        time++;
    }
    printf("\nGame Over!\n");

    printf("Enter 0-Exit and 1-Restart: ");
    int a;
    scanf("%d",&a);
    if (a==1)
    {
        gameover=0;
        score=0;
        snakeLen=1;
    
        main();
    }
    

   return 0;
}