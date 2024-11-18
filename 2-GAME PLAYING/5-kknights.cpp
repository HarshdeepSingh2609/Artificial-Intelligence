#include <iostream>
#include <ctime>
using namespace std;

int m, n;  
int Count = 0; 

void print_board(int **board) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool canPlace(int **board, int row, int col) {
    int moves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };

    for (int i = 0; i < 8; i++) {
        int newRow = row + moves[i][0];
        int newCol = col + moves[i][1];
        
        if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
            if (board[newRow][newCol] == 1) {
                return false; 
            }
        }
    }
    return true;
}

void Nknights(int **board, int knights_left, int row, int col) {
    if (knights_left == 0) {
        Count++;
        cout << "Board " << Count << ":" << endl;
        print_board(board);
        return;
    }

    if (row >= m) return;

    if (col >= n) {
        Nknights(board, knights_left, row + 1, 0);
        return;
    }

    int left_cells = (m * n) - (row * n + col);
    if (left_cells < knights_left) return;

    if (canPlace(board, row, col)) {
        board[row][col] = 1;  
        Nknights(board, knights_left - 1, row, col + 1);
        board[row][col] = 0;
    }

    Nknights(board, knights_left, row, col + 1);
}

int main() {
    double time1, time2, totaltime;
    cout << "Enter size of board (rows and columns): ";
    cin >> m >> n;

    int **board = new int*[m];
    for (int i = 0; i < m; i++) {
        board[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }

    cout << "Number of knights to be placed: ";
    int K;
    cin >> K; 

    time1 = (double)clock();
    Nknights(board, K, 0, 0); 
    time2 = (double)clock();
    totaltime = (time2 - time1) / CLOCKS_PER_SEC;

    if (Count == 0) {
        cout << "No solution exists!" << endl;
    } else {
        cout << "Total solutions found: " << Count << endl;
    }
    cout << "Total time taken: " << totaltime << " seconds" << endl;

    for (int i = 0; i < m; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}
