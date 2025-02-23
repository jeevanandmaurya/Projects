#include <stdio.h>
#include <Windows.h>
#include <conio.h>

// Constants
#define length 80
#define width 20

// Variables
char input;
int x = length / 2, y = width / 2;
int tempX = 0, tempY = 0;
int velX = 1, velY = 0;

// Sliders
int s1X = 1, s2X = length, s1Y = width / 2 + 1, s2Y = width / 2 + 1, sWidth = 5;
int s1VelY = 0, s2VelY = 0;
// Players
int lives1 = 3, lives2 = 3;

void moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

int main()
{
    // Hide Cursor
    printf("\033[?25l");

    // Starting
    printf("Starting...");
    Sleep(1500);

    system("cls");

    // Printing Boundary
    for (int i = 0; i < length; i++)
        printf("-");

    for (int i = 0; i < width; i++)
        printf("\n");

    for (int i = 0; i < length; i++)
        printf("-");

    while (1)
    {
        // Erasing  Ball
        if (tempY)
        {
            moveCursor(tempX, tempY);
            printf(" ");

            x += velX;
            if (velY > 1)
                velY = 1;
            if (velY < -1)
                velY = -1;

            y += velY;
        }

        // Printing Ball
        moveCursor(x, y);
        printf("O");

        tempX = x;
        tempY = y;

        // Player 1 Slider
        // Slider Drawing And Moving
        if (s1VelY < 0)
        {
            moveCursor(s1X, s1Y + sWidth / 2);
            printf(" ");
        }
        else if (s1VelY > 0)
        {
            moveCursor(s1X, s1Y - sWidth / 2);
            printf(" ");
        }
        s1Y += s1VelY;
        // Slider Constraint
        if (s1Y <= sWidth / 2 + 2)
            s1Y = sWidth / 2 + 2;
        if (s1Y >= width - sWidth / 2)
            s1Y = width - sWidth / 2;

        // Drawing
        moveCursor(s1X, s1Y - sWidth / 2);
        for (int i = 0; i < sWidth; i++)
            printf("|\n");

        // Player 2 Slider
        // Slider Drawing And Moving
        if (s2VelY < 0)
        {
            moveCursor(s2X, s2Y + sWidth / 2);
            printf(" ");
        }
        else if (s2VelY > 0)
        {
            moveCursor(s2X, s2Y - sWidth / 2);
            printf(" ");
        }
        s2Y += s2VelY;
        // Slider Constraint
        if (s2Y <= sWidth / 2 + 2)
            s2Y = sWidth / 2 + 2;
        if (s2Y >= width - sWidth / 2)
            s2Y = width - sWidth / 2;

        // Drawing
        moveCursor(s2X, s2Y - sWidth / 2);
        for (int i = 0; i < sWidth; i++)
            printf("|\033[1B\033[1D");

        // Ball Collision
        // Horizontal Wall

        if (y < 3 || y > width - 1)
            velY = -velY;

        // Player 1 Slider Collision
        if ((x < s1X + 1) && velX < 0)
        {
            if (y >= s1Y - sWidth / 2 && y <= s1Y + sWidth / 2)
            {

                velX = -velX;
                velY += s1VelY;
            }
            else
            {
                // Decrease Lives
                lives1--;
                x = length / 2;
                y = width / 2;
                velY = 0;
                if (lives1 == 0)
                    break;
            }
        }

        // Player 2 Slider Collision
        if ((x >= s2X) && velX > 0)
        {
            if (y >= s2Y - sWidth / 2 && y <= s2Y + sWidth / 2)
            {

                velX = -velX;
                velY += s2VelY;
            }
            else
            {
                // Decrease Lives
                lives2--;
                x = length / 2;
                y = width / 2;
                velY = 0;
                if (lives2 == 0)
                    break;
            }
        }

        // Moving Slider
        // KeyControll
        if (GetAsyncKeyState('W') & 0x8000)
            s1VelY = -1;
        else if (GetAsyncKeyState('S') & 0x8000)
            s1VelY = 1;
        else
            s1VelY = 0; // Stop when key is released

        if (GetAsyncKeyState(VK_UP) & 0x8000)
            s2VelY = -1;
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            s2VelY = 1;
        else
            s2VelY = 0; // Stop when key is released

        // ScoreBoard
        moveCursor(0, width + 2);
        printf("\033[0J");
        printf("Lives: ");
        for (int i = 0; i < lives1; i++)
            if (lives1 == 3)
                printf("\033[1;32m * \033[0m");//Green
            else if (lives1 == 2)
                printf("\033[1;33m * \033[0m");//Yellow
            else
                printf("\033[1;31m * \033[0m");//Red

        // Seperation
        for (int i = 0; i < length - 30; i++)
            printf(" ");

        // Printing Life Stars
        printf("Lives: ");
        for (int i = 0; i < lives2; i++)
            if (lives2 == 3)
                printf("\033[1;32m * \033[0m");
            else if (lives2 == 2)
                printf("\033[1;33m * \033[0m");
            else
                printf("\033[1;31m * \033[0m");

        Sleep(50);
    }

    // GameOver
    system("cls");
    printf("GameOver!\nResult:\n");
    (lives1) ? printf("Winner->Player 1") : printf("Winner->Player 2");

    // Restart or Exit
    printf("\n\n Press 'R' to replay and Press Any Other Key to exit: ");
    char c;
    scanf("%c", &c);
    if (c == 'r' || c == 'R')
    {
        // Reset Values
        lives1 = lives2 = 3;
        velY = 0;
        // Sliders1
        s1X = 1, s2X = length, s1Y = width / 2 + 1, s2Y = width / 2 + 1, sWidth = 5;
        s1VelY = 0, s2VelY = 0;
        // Players
        lives1 = 3, lives2 = 3;

        main();
    }

    return 0;
}