#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For Windows console API
using namespace std;

// Function to add a random 2 or 4 to an empty cell
void addRandomTile(int board[4][4]) {
    int emptyCells[16][2];
    int emptyCount = 0;
    // Find all empty cells
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }
    if (emptyCount > 0) {
        int idx = rand() % emptyCount;
        int value = (rand() % 2 + 1) * 2; // 2 or 4
        board[emptyCells[idx][0]][emptyCells[idx][1]] = value;
    }
}

bool moveUp(int board[4][4], int &score) {
    bool moved = false;
    for (int col = 0; col < 4; col++) {
        int lastMergeRow = -1;
        for (int row = 1; row < 4; row++) {
            if (board[row][col] == 0) continue;
            int target = row;
            while (target > 0 && board[target-1][col] == 0) {
                board[target-1][col] = board[target][col];
                board[target][col] = 0;
                target--;
                moved = true;
            }
            if (target > 0 && board[target-1][col] == board[target][col] && lastMergeRow != target-1) {
                board[target-1][col] *= 2;
                score += board[target-1][col];
                board[target][col] = 0;
                lastMergeRow = target-1;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveDown(int board[4][4], int &score) {
    bool moved = false;
    for (int col = 0; col < 4; col++) {
        int lastMergeRow = 4;
        for (int row = 2; row >= 0; row--) {
            if (board[row][col] == 0) continue;
            int target = row;
            while (target < 3 && board[target+1][col] == 0) {
                board[target+1][col] = board[target][col];
                board[target][col] = 0;
                target++;
                moved = true;
            }
            if (target < 3 && board[target+1][col] == board[target][col] && lastMergeRow != target+1) {
                board[target+1][col] *= 2;
                score += board[target+1][col];
                board[target][col] = 0;
                lastMergeRow = target+1;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveLeft(int board[4][4], int &score) {
    bool moved = false;
    for (int row = 0; row < 4; row++) {
        int lastMergeCol = -1;
        for (int col = 1; col < 4; col++) {
            if (board[row][col] == 0) continue;
            int target = col;
            while (target > 0 && board[row][target-1] == 0) {
                board[row][target-1] = board[row][target];
                board[row][target] = 0;
                target--;
                moved = true;
            }
            if (target > 0 && board[row][target-1] == board[row][target] && lastMergeCol != target-1) {
                board[row][target-1] *= 2;
                score += board[row][target-1];
                board[row][target] = 0;
                lastMergeCol = target-1;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveRight(int board[4][4], int &score) {
    bool moved = false;
    for (int row = 0; row < 4; row++) {
        int lastMergeCol = 4;
        for (int col = 2; col >= 0; col--) {
            if (board[row][col] == 0) continue;
            int target = col;
            while (target < 3 && board[row][target+1] == 0) {
                board[row][target+1] = board[row][target];
                board[row][target] = 0;
                target++;
                moved = true;
            }
            if (target < 3 && board[row][target+1] == board[row][target] && lastMergeCol != target+1) {
                board[row][target+1] *= 2;
                score += board[row][target+1];
                board[row][target] = 0;
                lastMergeCol = target+1;
                moved = true;
            }
        }
    }
    return moved;
}

bool isGameOver(int board[4][4]) {
    // Check for any empty cell
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return false;
        }
    }
    // Check for possible merges horizontally
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j+1]) return false;
        }
    }
    // Check for possible merges vertically
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == board[i+1][j]) return false;
        }
    }
    return true;
}

bool has2048(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 2048) return true;
        }
    }
    return false;
}

// Helper function to set color in Windows console
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Helper function to get color for a tile value
int getTileColor(int value) {
    switch (value) {
        case 2: return 240;      // Gray background
        case 4: return 224;      // Yellow background
        case 8: return 208;      // Orange background
        case 16: return 206;     // Pink background
        case 32: return 220;     // Gold (was 204, which is not visible in some consoles)
        case 64: return 196;     // Bright red background
        case 128: return 226;    // Bright yellow
        case 256: return 214;    // Orange
        case 512: return 202;    // Deep orange
        case 1024: return 200;   // Red
        case 2048: return 15;    // White
        default: return 15;      // White
    }
}

int main(){
    system("chcp 65001 > nul"); // Set UTF-8 code page for box-drawing
    srand((unsigned)time(0));
    int board[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int score = 0;
    char input;
    bool won = false;
    bool endless = false;

    // Add two random tiles at the start
    addRandomTile(board);
    addRandomTile(board);

    for(;;)
    {
        system("cls");
        cout << "\n   +-------+-------+-------+-------+" << endl;
        for(int i = 0; i < 4; i++)
        {
            cout << "   |";
            for(int j = 0; j < 4; j++)
            {
                if (board[i][j] == 0) {
                    setColor(8); // Gray
                    cout << "       ";
                    setColor(7); // Reset
                } else {
                    setColor(getTileColor(board[i][j]));
                    cout.width(5);
                    cout << board[i][j] << "  ";
                    setColor(7); // Reset
                }
                cout << "|";
            }
            cout << endl;
            cout << "   +-------+-------+-------+-------+" << endl;
        }
        if (!won && has2048(board)) {
            cout << "Congratulations! You reached 2048!\n";
            cout << "Press 'c' to continue to endless mode, or any other key to quit..." << endl;
            char choice = _getch();
            if (choice == 'c' || choice == 'C') {
                endless = true;
                won = true;
            } else {
                break;
            }
        }
        if(isGameOver(board))
        {
            cout << "Game Over!" << endl;
            break;
        }
        input = _getch();
        switch(input)
        {
            case 'w':
                if (moveUp(board, score)) addRandomTile(board);
                break;
            case 's':
                if (moveDown(board, score)) addRandomTile(board);
                break;
            case 'a':
                if (moveLeft(board, score)) addRandomTile(board);
                break;
            case 'd':
                if (moveRight(board, score)) addRandomTile(board);
                break;
            default:
                break;
        }
    }
return 0;

}
