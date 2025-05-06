#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>  // for time measurement
using namespace std;
using namespace chrono;

int n;

// ------------------------------
// Basic Backtracking
// ------------------------------
int countBasic = 0;
char boardBasic[15][15];

bool isSafeBasic(int row, int col) 
{
    for (int i = 0; i < row; i++) 
    {
        if (boardBasic[i][col] == 'Q') return false;
        if (col - (row - i) >= 0 && boardBasic[i][col - (row - i)] == 'Q') return false;
        if (col + (row - i) < n && boardBasic[i][col + (row - i)] == 'Q') return false;
    }
    return true;
}

void printBoard(char b[15][15]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
    cout << "----------------\n";
}

void solveBasic(int row) {
    if (row == n) {
        countBasic++;
        printBoard(boardBasic);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafeBasic(row, col)) {
            boardBasic[row][col] = 'Q';
            solveBasic(row + 1);
            boardBasic[row][col] = '.'; // backtrack
        }
    }
}

// ------------------------------
// Branch and Bound
// ------------------------------
int countBnB = 0;
bool col[15], diag1[30], diag2[30];
char boardBnB[15][15];

void solveBnB(int row) {
    if (row == n) {
        countBnB++;
        printBoard(boardBnB);
        return;
    }
    for (int c = 0; c < n; c++) 
    {
        if (!col[c] && !diag1[row - c + n] && !diag2[row + c]) 
        {
            col[c] = diag1[row - c + n] = diag2[row + c] = true;
            boardBnB[row][c] = 'Q';
            solveBnB(row + 1);
            col[c] = diag1[row - c + n] = diag2[row + c] = false;
            boardBnB[row][c] = '.';
        }
    }
}

int main() {
    cout << "Enter n: ";
    cin >> n;

    // Initialize boards
    memset(boardBasic, '.', sizeof(boardBasic));
    memset(boardBnB, '.', sizeof(boardBnB));

    cout << "\n--- Basic Backtracking Solutions ---\n";
    solveBasic(0);
    cout << "Total solutions (Basic Backtracking): " << countBasic << "\n";

    cout << "\n--- Branch and Bound Solutions ---\n";
    solveBnB(0);
    cout << "Total solutions (Branch & Bound): " << countBnB << "\n";

    return 0;
}


// ------------------------------
// Main Function
// ------------------------------
int main() {
    cout << "Enter n: ";
    cin >> n;

    // --------------------
    // Basic Backtracking
    // --------------------
    memset(boardBasic, '.', sizeof(boardBasic));
    auto start1 = high_resolution_clock::now();
    solveBasic(0);
    auto end1 = high_resolution_clock::now();

    long long boardSizeBasic = sizeof(boardBasic);
    long long callStackBasic = sizeof(int) * n; // Approximation
    long long totalSpaceBasic = boardSizeBasic + callStackBasic;

    cout << "\n--- Basic Backtracking Results ---\n";
    cout << "Total solutions: " << countBasic << "\n";
    cout << "Time taken: " << duration_cast<milliseconds>(end1 - start1).count() << " ms\n";
    cout << "Approx. Space used: " << totalSpaceBasic << " bytes (" << totalSpaceBasic / 1024.0 << " KB)\n";

    // --------------------
    // Branch and Bound
    // --------------------
    memset(boardBnB, '.', sizeof(boardBnB));
    memset(col, false, sizeof(col));
    memset(diag1, false, sizeof(diag1));
    memset(diag2, false, sizeof(diag2));

    auto start2 = high_resolution_clock::now();
    solveBnB(0);
    auto end2 = high_resolution_clock::now();

    long long boardSizeBnB = sizeof(boardBnB);
    long long boolArrays = sizeof(col) + sizeof(diag1) + sizeof(diag2);
    long long callStackBnB = sizeof(int) * n;
    long long totalSpaceBnB = boardSizeBnB + boolArrays + callStackBnB;

    cout << "\n--- Branch & Bound Results ---\n";
    cout << "Total solutions: " << countBnB << "\n";
    cout << "Time taken: " << duration_cast<milliseconds>(end2 - start2).count() << " ms\n";
    cout << "Approx. Space used: " << totalSpaceBnB << " bytes (" << totalSpaceBnB / 1024.0 << " KB)\n";

    return 0;
}
