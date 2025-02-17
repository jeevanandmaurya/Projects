
import java.util.Scanner;

public class tictactoe {

    public static void main(String[] args) {

        int moves = 0;
        // 1-O 2-X
        int turn = 1;
        int GameEnd = 0; // 0-not decided,1-plyr1,2-plyr2,3-draw
        char playerChar[] = {'_', 'O', 'X'};

        System.out.print("Positions\n1 2 3\n4 5 6\n7 8 9\n");
        System.out.println("\nGame Started\n");

        int entries[] = new int[9];
        for (int i = 0; i < 9; i++) {
            // 0-empty 1-O 2-X
            entries[i] = 0;
        }
        printBoard(entries, playerChar);
        int enteredPos;

        Scanner scan = new Scanner(System.in);

        while (GameEnd == 0) {

            System.out.print("\n\nPlayer " + turn + " Turn - " + playerChar[turn] + "\n");
            System.out.print("Enter Position: \n");
            enteredPos = scan.nextInt();

            while (enteredPos > 9 || entries[enteredPos - 1] != 0) {
                System.out.println("Invalid Input, Retry");
                System.out.println("Enter Position: ");
                enteredPos = scan.nextInt();
            }
            entries[enteredPos - 1] = turn;

            moves++;
            turn = 3 - turn;
            printBoard(entries, playerChar);

            GameEnd = checkWinner(entries);

            if (moves == 9 && GameEnd == 0) {
                GameEnd = 3;
            }
        }
        if (GameEnd == 3) {
            System.out.println("\nGame Draw!!!!!");
        } else {
            System.out.println("\nGame End!!!!!\nWinner is Player: " + GameEnd + "\n" + playerChar[GameEnd] + playerChar[GameEnd] + playerChar[GameEnd]);
        }

    }

    public static void printBoard(int entries[], char playerChar[]) {

        for (int i = 0; i < 9; i++) {
            if ((i + 1) % 3 == 0) {
                System.out.print(playerChar[entries[i]] + " \n");
            } else {
                System.out.print(playerChar[entries[i]] + " ");
            }

        }

    }

    public static int checkWinner(int entries[]) {

        // Horizontal
        if (entries[0] == entries[1] && entries[1] == entries[2]) {
            return entries[0];
        } else if (entries[3] == entries[4] && entries[4] == entries[5]) {
            return entries[3];
        } else if (entries[6] == entries[7] && entries[7] == entries[8]) {
            return entries[6];
        }

        // Vertical
        if (entries[0] == entries[3] && entries[3] == entries[6]) {
            return entries[0];
        } else if (entries[1] == entries[4] && entries[4] == entries[7]) {
            return entries[1];
        } else if (entries[2] == entries[5] && entries[5] == entries[7]) {
            return entries[2];
        }

        // Diagonal
        //-\\\
        if (entries[0] == entries[4] && entries[4] == entries[8]) {
            return entries[0];
        } //-///
        else if (entries[2] == entries[4] && entries[4] == entries[6]) {
            return entries[2];
        }

        return 0;
    }

}
