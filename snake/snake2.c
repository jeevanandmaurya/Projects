#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

// INCOMPLETE
// PROBLEM

// 30*30 Blocks
// BLOCK- 0 or N
// 0-Empty
// N-Filled(1-SnakeBlock/2-FoodBlock/3-Explosive)

int gameover = 0;
int snakeLen = 1;
int cX = 0, cY = 0;
int velX = 0, velY = 0, pHeadX = 0, pHeadY = 0;
int score = 0;
int time = 0;
int randPos = 0;
int fcount = 0;
// Structure to hold coordinates
typedef struct
{
    int x;
    int y;
} Coordinate;
Coordinate *tail;
Coordinate food;

void moveCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void keyinput(char input)
{
    // printf("Press a key (W = Up, A = Left, S = Down, D = Right, Q = Quit):\n");
    // Reads a character without Enter

    switch (input)
    {
    case 'w':
        // case 'W':
        if (velY == 0)
            velY = -1;
        velX = 0;
        break;
    case 'a':
        // case 'A':
        if (velX == 0)
            velX = -1;
        velY = 0;
        break;
    case 's':
        // case 'S':
        if (velY == 0)
            velY = 1;
        velX = 0;
        break;
    case 'd':
        // case 'D':
        if (velX == 0)
            velX = 1;
        velY = 0;
        break;
    case 'q':
        //  case 'Q':
        //  gameover = 1;

    default:
        printf("Invalid key! Use W/A/S/D to move, Q to quit.\n");
    }
}

char getCharAtCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD charsRead;
    char ch;

    // Get the cursor position
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        COORD cursorPos = csbi.dwCursorPosition; // Current cursor position

        // Read the character at the cursor position
        ReadConsoleOutputCharacter(hConsole, &ch, 1, cursorPos, &charsRead);

        if (charsRead > 0)
        {
            return ch; // Return the character
        }
    }

    return '\0'; // Return null character if failed
}

void update()
{

    // KeyControll
    if (_kbhit())
    {
        char input = _getch();
        keyinput(input);
    }

    // Next Move
    moveCursor(cX + 1, cY);
    char ch = getCharAtCursor();
    moveCursor(cX, cY);
    switch (ch)
    {
    // Empty Block
    case ' ':

        // Printing First Block(Head)
        printf(" O ");
        // Removing Last Block(Tail)
        if (snakeLen > 1)
        {
            moveCursor(3 * tail[0].x, tail[0].y);
            printf("   ");
        }
        else
        {
            moveCursor(3 * (tail[0].x-pHeadX), tail[0].y-pHeadY);
            printf("   ");
        }
        // Every Block Following the block in front of it
        for (int i = 0; i < snakeLen - 1; i++)
        {
            tail[i] = tail[i + 1];
        }
        // Moving head block to new Pos
        pHeadX=tail[snakeLen-1].x;
        pHeadY=tail[snakeLen-1].y;
        tail[snakeLen - 1].x = cX / 3;
        tail[snakeLen - 1].y = cY;
        break;

    // Food Block
    case 'o':
        snakeLen++;
        score++;
        printf(" O ");
        tail = realloc(tail, snakeLen * sizeof(Coordinate));
        // Just ADDING NEW Block
        tail[snakeLen - 1].x = cX / 3;
        tail[snakeLen - 1].y = cY;

        fcount--;

        if (fcount == 0)
        {
            food.x = rand() % 30;
            food.y = rand() % 30;
            fcount = 1;
            moveCursor(3 * food.x, food.y);
            printf(" o ");
        }
        break;

    // Snake Hit
    case 'O':
        gameover = 1;
        return;

        break;
    }

    // Motion & Constraint
    cX += 3 * velX;
    if (cX > 3 * 30 || cX < 1)
    {
        gameover = 1;
        return;
    }
    cY += velY;
    if (cY > 30 || cY < 1)
    {
        cY = cY - velY * 30;
    }
    tail[0].x = cX / 3;
    tail[0].y = cY;

    // // Saving prev vel
    // pvelX = velX;
    // pvelY = velY;

    moveCursor(0, 35);
    printf("Snake blocks: ");
    for (int i = 0; i < snakeLen; i++)
    {
        printf("x-%d y-%d ", tail[i].x, tail[i].y);
    }
    printf("\nx-%d y-%d ", pHeadX, pHeadY);
    printf("\nScore: %d ", score);
    printf("Time: %d ", time);
    printf("SnakeLen: %d ", snakeLen);

    printf("Cursor: x-%d y-%d", cX, cY);
    printf("\nCharAtCursor: %c", ch);
}

void printBoundary(int r, int c)
{

    for (int i = 0; i < c + 2; i++)
    {
        printf(" - ");
    }
    printf("\n");
    for (int i = 0; i < r; i++)
    {
        printf(" | ");
        for (int i = 0; i < c; i++)
        {
            printf("   ");
        }
        printf(" |\n");
    }
    for (int i = 0; i < c + 2; i++)
    {
        printf(" - ");
    }
}

int main()
{

    tail = malloc(snakeLen * sizeof(Coordinate));

    // Handling text cursor flashing
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Get current cursor settings
    // cursorInfo.bVisible = FALSE;                      // Set the cursor to invisible
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    system("cls");

    // Initial Velocity
    velX = 1;
    velY = 0;

    // Food
    food.x = rand() % 30;
    food.y = rand() % 30;
    fcount = 1;

    printBoundary(30, 30);

    // Initialize Food
    food.x = rand() % 30;
    food.y = rand() % 30;
    fcount = 1;
    moveCursor(3 * food.x, food.y);
    printf(" o ");

    // Initialize Cursor
    cX = 3 * 15;
    cY = 15;
    moveCursor(cX, cY);
    pHeadX=cX/3;
    pHeadY=cY;
    // //Initial Snake Head
    // tail = malloc(1 * sizeof(Coordinate));
    // tail[0].x=0;
    // tail[0].y=0;
    // printf(" O ");
    // //Move Cursor Next to Head
    // cX += 3*velX;
    // cY += velY;

    // moveCursor(33,34);

    while (gameover == 0)
    {
        update();
        Sleep(500);
        time++;
    }
    printf("\nGame Over!\n");

    // printf("Enter 0-Exit and 1-Restart: ");
    // int a;
    // scanf("%d", &a);
    // if (a == 1)
    // {
    //     gameover = 0;
    //     score = 0;
    //     snakeLen = 1;

    //     main();
    // }

    return 0;
}