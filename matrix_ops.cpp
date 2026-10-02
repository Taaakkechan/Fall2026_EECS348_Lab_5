// matrix_ops.cpp - basic matrix operations on N x N matrices read from a file
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int> > Matrix;

// Column width: at least 4 (matches the sample output), wider if values need it.
static int columnWidth(const Matrix &m) {
    size_t maxLen = 0;
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m[i].size(); j++)
            maxLen = max(maxLen, to_string(m[i][j]).size());
    return static_cast<int>(max<size_t>(4, maxLen + 1));
}

void printMatrix(const Matrix &m) {
    int w = columnWidth(m);
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++)
            cout << setw(w) << m[i][j];
        cout << "\n";
    }
}

// 1. Load N, then two N x N matrices, from a file.
bool loadMatrices(const string &filename, int &n, Matrix &a, Matrix &b) {
    ifstream in(filename.c_str());
    if (!in) {
        cerr << "Error: cannot open file '" << filename << "'\n";
        return false;
    }
    if (!(in >> n) || n <= 0) {
        cerr << "Error: first line must be a positive integer N\n";
        return false;
    }
    // creates empty matricies with 0 to be filled later
    a.assign(n, vector<int>(n)); 
    b.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> a[i][j])) {
                cerr << "Error: not enough values for Matrix A\n";
                return false;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> b[i][j])) {
                cerr << "Error: not enough values for Matrix B\n";
                return false;
            }
    return true;
}

// 2. Add two matrices and display the result.
Matrix addMatrices(const Matrix &a, const Matrix &b) {
    size_t n = a.size();
    Matrix c(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    return c;
}

// 3. Multiply two matrices (row of A dot column of B).
Matrix multiplyMatrices(const Matrix &a, const Matrix &b) {
    size_t n = a.size();
    Matrix c(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            for (size_t k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

// 4. Main and secondary diagonal sums.
void diagonalSums(const Matrix &m, int &mainSum, int &secSum) {
    int n = static_cast<int>(m.size());
    mainSum = 0;
    secSum = 0;
    for (int i = 0; i < n; i++) {
        mainSum += m[i][i];
        secSum += m[i][n - 1 - i];
    }
}

// 5. Swap two rows (0-based). Returns false if an index is out of range.
bool swapRows(Matrix &m, int r1, int r2) {
    int n = static_cast<int>(m.size());
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) return false;
    swap(m[r1], m[r2]);
    return true;
}

// 6. Swap two columns (0-based). Returns false if an index is out of range.
bool swapColumns(Matrix &m, int c1, int c2) {
    int n = static_cast<int>(m.size());
    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) return false;
    for (int i = 0; i < n; i++) swap(m[i][c1], m[i][c2]);
    return true;
}

// 7. Update one element (0-based). Returns false if an index is out of range.
bool updateElement(Matrix &m, int row, int col, int value) {
    int n = static_cast<int>(m.size());
    if (row < 0 || row >= n || col < 0 || col >= n) return false;
    m[row][col] = value;
    return true;
}

int main() {
    string filename;
    cout << "Enter input filename: ";
    getline(cin, filename);
    cout << "\n";

    int n;
    Matrix a, b;
    if (!loadMatrices(filename, n, a, b)) return 1;

    cout << "Matrix A:\n";
    printMatrix(a);
    cout << "\nMatrix B:\n";
    printMatrix(b);

    cout << "\nA + B:\n";
    printMatrix(addMatrices(a, b));

    cout << "\nA * B:\n";
    printMatrix(multiplyMatrices(a, b));

    int mainSum, secSum;
    diagonalSums(a, mainSum, secSum);
    cout << "\nDiagonal sums for Matrix A:\n";
    cout << "Main diagonal sum: " << mainSum << "\n";
    cout << "Secondary diagonal sum: " << secSum << "\n";

    // Problems 5-7 each operate on a fresh copy of Matrix A.
    // Example arguments match the sample output; change as desired.
    Matrix m = a;
    cout << "\nProblem 5 - Rows 0 and 2 swapped:\n";
    if (swapRows(m, 0, 2)) printMatrix(m);
    else cout << "Invalid row index.\n";

    m = a;
    cout << "\nProblem 6 - Columns 0 and 2 swapped:\n";
    if (swapColumns(m, 0, 2)) printMatrix(m);
    else cout << "Invalid column index.\n";

    m = a;
    cout << "\nProblem 7 - Updated matrix:\n";
    if (updateElement(m, 1, 2, 99)) printMatrix(m);
    else cout << "Invalid row or column index.\n";

    return 0;
}
