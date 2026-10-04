
#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// Display the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    cout << "\n=========================\n";

    for (int r = 0; r < N; r++) {
        if (r > 0 && r % 3 == 0)
            cout << "------+-------+------\n";

        for (int c = 0; c < N; c++) {
            if (c > 0 && c % 3 == 0)
                cout << "| ";

            cout << grid[r][c] << " ";
        }
        cout << "\n";
    }

    cout << "=========================\n";
}

// Check whether a number can be placed
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {

    // Check row and column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Solve the puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row = -1, col = -1;

    // Find an empty cell
    bool found = false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                found = true;
                break;
            }
        }

        if (found)
            break;
    }

    if (!found)
        return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));

    cout << "Enter your 9x9 Sudoku puzzle row by row.\n";
    cout << "Use the number '0' for blank spaces. Separate numbers with spaces:\n\n";

    for (int i = 0; i < N; i++) {
        cout << "Enter Row " << i + 1 << ": ";

        for (int j = 0; j < N; j++)
            cin >> grid[i][j];
    }

    cout << "\nInitial Puzzle Entered:";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSudoku Solved Successfully!";
        printGrid(grid);
    }
    else {
        cout << "\nNo solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}

