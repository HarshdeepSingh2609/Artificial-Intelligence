#include <iostream>
#include <vector>
using namespace std;

int human = 3;
int computer = 5;
const int BLANK = 2;

vector<int> board(9, BLANK);
int turn = 1;
bool userFirst = true;
vector<int> MagicSquare = {6, 1, 8, 7, 5, 3, 2, 9, 4};

void printBoard()
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 3)
            cout << "X ";
        else if (board[i] == 5)
            cout << "O ";
        else
            cout << "- ";
        if (i % 3 == 2)
            cout << endl;
    }
    cout << endl;
}

string checkWin()
{
    // Checking for player win
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == human)
        {
            for (int j = i + 1; j < 9; ++j)
            {
                if (board[j] == human)
                {
                    for (int k = j + 1; k < 9; ++k)
                    {
                        if (board[k] == human)
                        { 
                            if (MagicSquare[i] + MagicSquare[j] + MagicSquare[k] == 15)
                            {
                                return "human";
                            }
                        }
                    }
                }
            }
        }
    }  

    // Checking for computer win
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == computer)
        {
            for (int j = i + 1; j < 9; ++j)
            {
                if (board[j] == computer)
                {
                    for (int k = j + 1; k < 9; ++k)
                    {
                        if (board[k] == computer)
                        {
                            if (MagicSquare[i] + MagicSquare[j] + MagicSquare[k] == 15)
                            {
                                return "computer";
                            }
                        }
                    }
                }
            }
        }
    }

    return "";
}

int goAnywhere()
{
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == BLANK)
            return i;
    }
    return -1;
}

int posswin(int player)
{
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == player)
        {
            for (int j = i + 1; j < 9; ++j)
            {
                if (board[j] == player)
                {
                    int requiredSum = 15 - MagicSquare[i] - MagicSquare[j];
                    for (int k = 0; k < 9; ++k)
                    {
                        if (MagicSquare[k] == requiredSum && board[k] == BLANK)
                        {
                            return k;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void go(int move)
{
    board[move] = userFirst ? human : computer;
    turn++;
}

int make2()
{
    if (board[4] == BLANK)
        return 4;
    vector<int> options = {0, 2, 6, 8};
    for (int option : options)
    {
        if (board[option] == BLANK)
            return option;
    }
    return -1;
}

void userMove()
{
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;
    if (move < 1 || move > 9 || board[move - 1] != BLANK)
    {
        cout << "Invalid move. Try again." << endl;
        userMove();
    }
    else
    {
        go(move - 1);
    }
}

void computerMove()
{
    int move = -1;
    switch (turn)
    {
    case 1:
        move = 0;
        break;
    case 2:
        move = (board[4] == BLANK) ? 4 : 0;
        break;
    case 3:
        move = (board[8] == BLANK) ? 8 : 2;
        break;
    case 4:
        if (posswin(human) != -1)
            move = posswin(human);
        else
            move = make2();
        break;
    case 5:
        if (posswin(computer) != -1)
            move = posswin(computer);
        else if (posswin(human) != -1)
            move = posswin(human);
        else
            move = make2();
        break;
    default:
        if (posswin(computer) != -1)
            move = posswin(computer);
        else if (posswin(human) != -1)
            move = posswin(human);
        else
            move = goAnywhere();
        break;
    }
    go(move);
}

int main()
{
    cout << "Do you want to play first? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n')
        userFirst = false;
    if (userFirst)
    {
        human = 3;
        computer = 5;
    }
    else
    {
        computer = 3;
        human = 5;
    }

    while (turn <= 9)
    {
        printBoard();

        if (userFirst)
        {
            userMove();
            userFirst = false;
        }
        else
        {
            computerMove();
            userFirst = true;
        }

        if (checkWin() == "human")
        {
            printBoard();
            cout << "User wins!" << endl;
            break;
        }
        else if (checkWin() == "computer")
        {
            printBoard();
            cout << "Computer wins!" << endl;
            break;
        }
        else if (turn > 9)
        {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
