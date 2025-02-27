#include <stdio.h>

int main() {
    printf("\033[1mBold Text\033[0m\n");       // Bold
    printf("\033[9mUnderlined\033[0m\n");     // Underline
    printf("\033[7mInverted\033[0m\n");       // Inverted colors


    for (int i = 0; i < 256; i++)
    {
        printf("\033[38;5;%d;48;5;%dm Hello %d\033[0m \n",i,i%10,i);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("\033[48;5;3m   ");
        }
        
        
    }
    

    return 0;
}
