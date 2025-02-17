#include <windows.h>
#include <stdio.h>

char getCharAtCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD charsRead;
    char ch;

    // Get the cursor position
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        COORD cursorPos = csbi.dwCursorPosition; // Current cursor position

        // Read the character at the cursor position
        ReadConsoleOutputCharacter(hConsole, &ch, 1, cursorPos, &charsRead);

        if (charsRead > 0) {
            return ch; // Return the character
        }
    }

    return '\0'; // Return null character if failed
}

int main() {
    system("cls");
    // Example: Place a character and get it back
    printf("Hello World");
    COORD coord = {0, 0}; // Position of 'W' in "World"

    // Move the cursor to the desired position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Get the character at the cursor
    while(coord.X < 11) {
        char ch = getCharAtCursor();
        printf("\nCharacter at cursor: %c\n", ch);
        printf("%d %d", coord.X, coord.Y);
        Sleep(100);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("X");
        coord.X++;
        if(coord.X==11)coord.X=0;
    }
    return 0;
}
