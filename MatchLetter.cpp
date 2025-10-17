#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <limits>
#include <cmath>

using namespace std;

void displayBoard(const char board[], int size) {
    int gridSize = static_cast<int>(sqrt(size));
    if (gridSize * gridSize != size) {
        gridSize++;
    }

    cout << "=========================================================\n";
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    cout << "=========================================================\n";
    cout << "||                   MATCH THE LETTER                  ||\n";
    cout << "=========================================================\n";

    for (int i = 0; i < size; ++i) {
        cout << setw(4) << i + 1 << ". " << board[i];
        if ((i + 1) % gridSize == 0) {
            cout << endl;
        }
    }

    cout << "\n=========================================================";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
/* #else
    system("clear"); */
#endif
}

void showGameMechanics() {
    cout << "==================================================================================================\n";
    cout << "\n                              Welcome to the Match the Letter!\n";
    cout << "==================================================================================================\n";
    cout << "   = This game was created by Tabanao, Sumarsar, Barros, Tibayan from BSIT-1C\n";
    cout << "==================================================================================================\n";
    cout << "   = The objective of the game is to match pairs of hidden letters.\n";
    cout << "   = You will be presented with a set of numbers representing hidden letters.\n";
    cout << "   = Your task is to choose two numbers, and if the letters behind them match, you win a pair!\n";
    cout << "   = You have 5 seconds to memorize the revealed letters before they are hidden again.\n";
    cout << "   = If they don't match, the letters will be hidden again, and you can try again!\n";
    cout << "   = Note: Each number has a hidden letter, the letters are jumbled in different numbers!\n";
    cout << "   = Note: When inputting two numbers make sure to add space between them!!!\n";
    cout << "   = Good luck and have fun! ^3^";
    cout << "\n==================================================================================================\n";
}

bool isValidNumberInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int chooseDifficulty(int totalPairs) {
    int choice;
    while (true) {
    	cout << "=====================================================\n";
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
        cout << "=====================================================\n";
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
        cout << "=====================================================\n";
        cout << "Choose your difficulty level:\n";
        cout << "-----------------------------------------------------\n";
        cout << "1. Easy (1/4 of the letters)\n";
        cout << "2. Normal (1/2 of the letters)\n";
        cout << "3. Hard (All the letters)\n";
        cout << "4. Exit\n"; 
        cout << "=====================================================\n";
        cout << "Enter the number of your choice: ";
        cin >> choice;

        if (isValidNumberInput() && (choice >= 1 && choice <= 4)) {
            if (choice == 4) {
                cout << "\nExiting the game. Thank you for playing!!! 🙂 :3 <3\n";
                exit(0);
            }
            break;
        } else {
            cout << "\nInvalid choice. Please choose a valid option (1-4).\n";
            continue;
        }
    }

    int selectedPairs = 0;
    switch (choice) {
        case 1:
            selectedPairs = totalPairs / 4;
            break;
        case 2:
            selectedPairs = totalPairs / 2;
            break;
        case 3:
            selectedPairs = totalPairs;
            break;
    }
    return selectedPairs;
}

void delay(int seconds) {
    time_t start = time(0);
    while (time(0) - start < seconds) {
    }
}

void countdown() {
    cout << "\nGame starting in:\n";
    for (int i = 3; i > 0; --i) {
        cout << i << " ";
        delay(2);
    }
    clearScreen();
    cout << "\n                    ||||||||||||||||||||||||||||||||||||\n";
    cout << "                    ====================================\n";
    cout << "                    ||***^3^****GAME START!*****^3^***||\n";
    cout << "                    ====================================\n";
    cout << "                    ||||||||||||||||||||||||||||||||||||";
    delay(2);
    clearScreen();
}

void displayWinMessage() {
	cout << "\n                    ===============================================================\n";
    cout << "                    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    cout << "                    ===============================================================\n";
    cout << "\n                    ++++++ Congratulations! You matched all pairs! ++++++\n";
    cout << "                    ===============================================================\n";
}

void displayTryAgainMessage() {
    cout << "\nOops! Not a match. Try Again! \nHiding the letters again... ";
    for (int i = 5; i > 0; --i) {
        cout << i << " ";
        delay(2);
    }
}

bool isExitInput(const string& input) {
    return input == "x" || input == "X";
}

bool isRestartInput(const string& input) {
    return input == "y" || input == "Y";
}

void shuffleArray(char arr[], int size) {
    srand(time(0));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

int main() {
    srand(time(0));

    const int MAX_PAIRS = 26;
    const int MAX_SIZE = MAX_PAIRS * 2;
    char hiddenLetters[MAX_SIZE];
    char board[MAX_SIZE];
    bool revealedLetters[MAX_SIZE];

    for (int i = 0; i < MAX_PAIRS; ++i) {
        hiddenLetters[2 * i] = 'A' + i;
        hiddenLetters[2 * i + 1] = 'a' + i;
        revealedLetters[2 * i] = revealedLetters[2 * i + 1] = false;
        board[2 * i] = board[2 * i + 1] = '*';
    }

    shuffleArray(hiddenLetters, MAX_SIZE);

    while (true) { 
        showGameMechanics();
        int selectedPairs = chooseDifficulty(MAX_PAIRS);
        countdown();

        bool game_over = false;
        while (!game_over) {
            displayBoard(board, selectedPairs * 2);

            string input1, input2;
            int choice1 = -1, choice2 = -1;
            bool validInput = false;

            while (!validInput) {
                cout << "\nEnter two numbers to reveal letters 1-" << selectedPairs * 2 
                     << "\n('x' to exit, or 'y' to restart): ";
                cin >> input1;

                if (isExitInput(input1)) {
                    cout << "\nExiting the game. Thank you for playing!!! 🙂 :3 <3\n";
                    delay(2);
                    return 0; 
                }
                if (isRestartInput(input1)) {
                    cout << "\nRestarting the game. Returning to difficulty selection...\n";
                    delay(2);
                    clearScreen();
                    break; 
                }

                cin >> input2;
                if (isExitInput(input2)) {
                    cout << "\nExiting the game. Thank you for playing!\n";
                    return 0;
                }
                if (isRestartInput(input2)) {
                    cout << "\nRestarting the game. Returning to difficulty selection...\n";
                    clearScreen();
                    break; 
                }

                choice1 = stoi(input1);
                choice2 = stoi(input2);

                if (isValidNumberInput() && choice1 > 0 && choice1 <= selectedPairs * 2 &&
                    choice2 > 0 && choice2 <= selectedPairs * 2 && choice1 != choice2) {
                    validInput = true;
                } else {
                    cout << "\nInvalid input. Please enter valid numbers and ensure the numbers are different.\n";
                }
            }

            if (isRestartInput(input1) || isRestartInput(input2)) break; 

            choice1--;
            choice2--;

            board[choice1] = hiddenLetters[choice1];
            board[choice2] = hiddenLetters[choice2];

            displayBoard(board, selectedPairs * 2);

            if (tolower(hiddenLetters[choice1]) == tolower(hiddenLetters[choice2])) {
                cout << "\nGreat job! It's a match!";
                delay(2);
            } else {
                displayTryAgainMessage();
                board[choice1] = '*';
                board[choice2] = '*';
            }

            delay(2);

            clearScreen();
            game_over = true;
            for (int i = 0; i < selectedPairs * 2; ++i) {
                if (board[i] == '*') {
                    game_over = false;
                    break;
                }
            }
        }

        if (!game_over) continue; 

        displayWinMessage();
        return 0; 
    }
}
