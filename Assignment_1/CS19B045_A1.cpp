/**************************************************************************
 *  
 *  File:    CS19B045_A1.cpp
 *
 *  Purpose:    Program to implement various matrix operations using Operator Overloading
 *
 *  Author:    Vishnu
 *
 *  Created:    Mon 08-February-2021 18:56:45
 *
 *  Last Modified:    Tue 09-February-2021 19:07:31
 *
 *  Changes:    - 
 *
 **************************************************************************/
#include <iostream>


/* int Graph::cycle(int u, int visited[], int p) {
    visited[u] = 1;
    for(int v = 0; v < vertices; v++) {
        if(adjMat[u][v] == 0) continue;
        if(visited[v] == 0) {
            if(cycle(v, visited, u) == 1)
                return 1;
        }
        else if(v != p) return 1;
    }
    return 0;
} */

using namespace std;

#define MAT_SIZE 60         // Maximum size of the array
#define MAX_ELEM 1000       // Maximum value of an element in the array

class Matrix {
    int **mat;                    // Members of the class
    int matSize;

    public :
        // Function declarations
        Matrix(int);
        ~Matrix();
        void input();
        void printMatrix();
        Matrix transpose ();
        void operator+();
        void operator& ();
        Matrix operator>> (int);
        Matrix operator+ (Matrix&);
};

Matrix::Matrix(int n) {                                 // Constructor to allocate memory
    matSize = n;
    mat = new int* [matSize];
    for(int i = 0; i < matSize; i++) 
        mat[i] = new int [matSize];
}

Matrix::~Matrix() {                                 // Destructor to free memory
    for(int i = 0; i < matSize; i++) {
        delete[] mat[i];
        mat[i] = NULL;
    }
    delete[] mat;
    mat = NULL;
}

void Matrix::input() {                                  // Member function to get the input
    for(int i = 0; i < matSize; i++) {
        for(int j = 0; j < matSize; j++) {
            cin >> mat[i][j];
        }
    }
}

void Matrix::printMatrix() {                            //Member function to print the matrix
    for(int i = 0; i < matSize; i++) {
        for(int j = 0; j < matSize; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::operator+ () {                                         //SPSUM
    int ans[MAT_SIZE][MAT_SIZE];
    for(int i = 0; i < matSize; i++) {
        for(int j  = i; j < matSize; j++) {
            if((i + j)%2 == 1) {                     // If i+j is odd, switch
                ans[i][j] = mat[j][i];
                ans[j][i] = mat[i][j];
            }
            else {                                    // Else it is the same
                ans[i][j] = mat[i][j];
                ans[j][i] = mat[j][i];
            }
        }
    }

    int rowSum = 0;
    for(int i = 0; i < matSize; i++) {
        rowSum = 0;
        for(int j  = 0; j < matSize; j++) 
            rowSum += ans[i][j];                // Finding row-wise sum
        if(i != matSize-1)
        cout << rowSum << ',';
        else 
        cout << rowSum << endl;
    }
}

void Matrix::operator& () {                                      // MOD
    int minRow, maxRow, avgRow;
    long long ans = 1;
    for(int i = 0; i < matSize; i++) {
        minRow = MAX_ELEM, maxRow = 0, avgRow = 0;
        for(int j  = 0; j < matSize; j++) {
            if(minRow > mat[i][j])
                minRow = mat[i][j];                 // Row wise minimum
            if(maxRow < mat[i][j])
                maxRow = mat[i][j];                 // Row wise maximum
            avgRow += mat[i][j];                // Sum of row elements
        }
        avgRow /= matSize;                  // Row average
        if(i%3 == 0) ans *= maxRow;
        else if(i%3 == 1) ans *= minRow;
        else ans *= avgRow;
    }
    cout << ans <<endl;
}

Matrix Matrix::operator>> (int k) {                                    // Function to shift the matrix right by k
    int shiftedI = 0, shiftedJ = 0;
    Matrix ans(matSize);
    for(int i = 0; i < matSize; i++) {
        for(int j = 0; j < matSize; j++) {
            shiftedI = ((i*matSize + j - k + matSize*matSize) / matSize)%matSize;
            shiftedJ = (i*matSize + j - k) % matSize;
            shiftedI = (shiftedI + matSize)%matSize;
            shiftedJ = (shiftedJ + matSize)%matSize;
            ans.mat[i][j] = mat[shiftedI][shiftedJ];
        }
    }
    return ans;
}
Matrix Matrix::operator+ (Matrix &op) {                          // MADD
    Matrix ans(matSize);

    for(int i = 0; i < matSize; i++) {
        for(int j  = 0; j < matSize; j++) {
            ans.mat[i][j] = mat[i][j] + op.mat[i][j];           // Adding the diagonally opposite elements of second operand
        }
    }
    return ans;
}

Matrix Matrix::transpose () {                        // Function to return the transpose of the matrix
    Matrix ans(matSize);
    for(int i = 0; i < matSize; i++) {
        for(int j  = 0; j < matSize; j++) {
            ans.mat[i][j] = mat[j][i];     // Just adding coresponding elements
        }
    }
    return ans;
}

int main() {
    int n, Q;
    cin >> Q;
    cin >> n;
    
    // Initialization
    Matrix A(n); 
    Matrix B(n);

    // Getting the input values for matrix A and B
    A.input();
    B.input();

    string operation;
    int k, x;

    while(Q--) {
        cin >> operation;

        // Call to respective functions
        if(operation == "SPSUM") {
            +A;
        }
        else if(operation == "MOD") {
            &A;
        }
        else if(operation == "MRS") {
            cin >> k;
            Matrix Sum = (A+B);                      // First add the elements
            Matrix Ans = Sum>>k;               // Then shift it right by k
            Ans.printMatrix();          // Print the shifted elements 
        }
        else {
            cin >> x;
            if(x == 1) {
                Matrix Trans = A.transpose();          // Transpose of A
                Matrix Ans = Trans+B;              // Added to B
                Ans.printMatrix(); 
            }         
            else {
                Matrix Trans = B.transpose();          // Transpose of B
                Matrix Ans = Trans+A;              // Added to A
                Ans.printMatrix();
            }
        }
    }
}