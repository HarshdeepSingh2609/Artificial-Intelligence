#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> board(9, 2); 
int PLAYER_User = 3;
int PLAYER_Computer = 5;
int turn = 1;                
bool userFirst = true;

void display() {
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) cout << endl;
        cout << (board[i] == 3 ? "X " : (board[i] == 5 ? "O " : "- "));
    }
    cout << endl;
}

int checkWin(const vector<int>& board) {
    for (int i = 0; i < 3; i++) {
       
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            if (board[i * 3] == PLAYER_Computer) return 10;
            else if (board[i * 3] == PLAYER_User) return -10;
        }
        
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == PLAYER_Computer) return 10; 
            else if (board[i] ==  PLAYER_User) return -10; 
        }
    }
    
    if (board[0] == board[4] && board[4] == board[8]) {
        if (board[0] ==  PLAYER_Computer) return 10; 
        else if (board[0] ==  PLAYER_User) return -10;
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        if (board[2] ==  PLAYER_Computer) return 10; 
        else if (board[2] ==  PLAYER_User) return -10; 
    }

    return 0; 
}

bool isDraw() {
    for (int spot : board) {
        if (spot == 2) return false;
    }
    return true;
}

int rate(const vector<int>& b) {
    int score = 0;
    
    if (b[4] ==  PLAYER_Computer) score += 4; 
    if (b[4] ==  PLAYER_User) score -= 4;

    int corners[] = {b[0], b[2], b[6], b[8]};
    for (int corner : corners) {
        if (corner ==  PLAYER_Computer) score += 3;
        if (corner ==  PLAYER_User) score -= 3; 
    }

    int edges[] = {b[1], b[3], b[5], b[7]};
    for (int edge : edges) {
        if (edge ==  PLAYER_Computer) score += 1;
        if (edge ==  PLAYER_User) score -= 1;
    }

    return score;
}

vector<int> move_gen(const vector<int>& board) {
    vector<int> moves;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) {
            moves.push_back(i);
        }
    }
    return moves;
}

int minimax(vector<int>& board, int depth, bool isMaximizing, int maxDepth) {
    int score = checkWin(board);
    if (score != 0) return score;
    if (isDraw()) return 0;
    if (depth >= maxDepth) return rate(board);

    if (isMaximizing) {
        int bestScore = -1000;
        vector<int> moves = move_gen(board);
        for (int move : moves) {
            board[move] = PLAYER_Computer;
            bestScore = max(bestScore, minimax(board, depth + 1, false, maxDepth));
            board[move] = 2;
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        vector<int> moves = move_gen(board);
        for (int move : moves) {
            board[move] =  PLAYER_User;
            bestScore = min(bestScore, minimax(board, depth + 1, true, maxDepth));
            board[move] = 2;
        }
        return bestScore;
    }
}

void computermove(int maxDepth) {
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) {
            board[i] =  PLAYER_Computer;
            int score = minimax(board, 0, false, maxDepth);
            board[i] = 2;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    if (bestMove != -1) {
        board[bestMove] =  PLAYER_Computer;
    }
    display();
}

void usermove() {
    int n;
    while (true) {
        cout << "Enter the block number for your move (1-9): ";
        cin >> n;
        n--;
        if (board[n] == 2) {
            board[n] =  PLAYER_User; 
            break;
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
    }
}

int main() {
    cout << "Do you want to play first? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n') userFirst = false;

    if (userFirst) {
        PLAYER_User = 3; 
        PLAYER_Computer = 5; 
    } else {
        PLAYER_Computer = 3; 
        PLAYER_User = 5; 
    }
    for(int depth = 1; depth <= 4; depth++){
        cout<<"Testing with depth "<<depth<<endl;

        board.assign(9, 2);
        turn = 1;

        while (turn <= 9) {
        display();
        
        if ((turn % 2 == 1 && userFirst) || (turn % 2 == 0 && !userFirst)) {
            usermove();
        } else {
            cout << endl << "Computer's move:" << endl;
            computermove(depth);
        }

        int result = checkWin(board);
        if (result == -10) {
            display();
            cout << "User wins!" << endl;
            break;
        } else if (result == 10) {
            display();
            cout << "Computer wins!" << endl;
            break;
        } else if (isDraw()) {
            display();
            cout << "It's a draw!" << endl;
            break;
        }
        
        turn++;
    }
      cout << "--------------------------" << endl;
    }
    

    return 0;
}