#include <iostream>
#include <vector>

using namespace std;

int human = 3;
int computer = 5;
int EMPTY = 2;

vector<int> gameBoard(9, EMPTY); 
int moveCount = 1;                
bool isHumanFirst = true;

void displayBoard() {
    for (int i = 0; i < 9; i++) {
        if (gameBoard[i] == 3) cout << "X ";
        else if (gameBoard[i] == 5) cout << "O ";
        else cout << "- ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

string checkWinner() {
    vector<vector<int>> winningCombinations = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (auto& combination : winningCombinations) {
        int product = gameBoard[combination[0]] * gameBoard[combination[1]] * gameBoard[combination[2]];
        if (product == human * human * human) return "human";
        if (product == computer * computer * computer) return "computer"; 
    }
    return "";
}

int findAnyMove(){
    for (int i = 0; i < 9; i++) {
        if (gameBoard[i] == EMPTY) return i;
    }
    return -1;
}

int possibleWin(int player) {
    vector<vector<int>> winningCombinations = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6} 
    };

    for (auto& combination : winningCombinations) {
        int product = gameBoard[combination[0]] * gameBoard[combination[1]] * gameBoard[combination[2]];
        if (product == player * player * EMPTY) {
            for (int idx : combination) {
                if (gameBoard[idx] == EMPTY) {
                    return idx;
                }
            }
        }
    }
    return -1;
}

void placeMove(int position) {
    gameBoard[position] = isHumanFirst ? human : computer;
    moveCount++;
}

int bestMove() {
    if (gameBoard[4] == EMPTY) return 4;
    vector<int> corners = {0, 2, 6, 8};
    for (int corner : corners) {
        if (gameBoard[corner] == EMPTY) return corner;
    }
    return -1;
}

void humanTurn() {
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;
    if (gameBoard[move-1] == EMPTY) {
        placeMove(move-1);
    } else {
        cout << "Invalid move. Try again." << endl;
        humanTurn();
    }
}

void aiTurn() {
    int move = -1;
    switch (moveCount) {
        case 1:
            move = 0;
            break;
        case 2:
            move = (gameBoard[4] == EMPTY) ? 4 : 0;
            break;
        case 3:
            move = (gameBoard[8] == EMPTY) ? 8 : 2;
            break;
        case 4:
            if (possibleWin(human) != -1) move = possibleWin(human);
            else move = bestMove();
            break;
        case 5:
            if (possibleWin(computer) != -1) move = possibleWin(computer);
            else if (possibleWin(human) != -1) move = possibleWin(human);
            else if (gameBoard[6] == EMPTY) move = 6;
            else move = 2;
            break;
        case 6:
            if (possibleWin(computer) != -1) move = possibleWin(computer);
            else if (possibleWin(human) != -1) move = possibleWin(human);
            else move = bestMove();
            break;
        default:
            if (possibleWin(computer) != -1) move = possibleWin(computer);
            else if (possibleWin(human) != -1) move = possibleWin(human);
            else move = findAnyMove();
            break;
    }
    placeMove(move);
}

int main() {
    cout << "Do you want to play first? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n') isHumanFirst = false;

    if (isHumanFirst) {
        human = 3;
        computer = 5;
    } else {
        computer = 3;
        human = 5;
    }

    while (moveCount <= 9) {
        displayBoard();

        if (isHumanFirst) {
            humanTurn();
            isHumanFirst = false;
        } else {
            aiTurn();
            isHumanFirst = true;
        }

        string winner = checkWinner();
        if (winner == "human") {
            displayBoard();
            cout << "Human wins!" << endl;
            break;
        } else if (winner == "computer") {
            displayBoard();
            cout << "AI wins!" << endl;
            break;
        } else if (moveCount > 9) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
