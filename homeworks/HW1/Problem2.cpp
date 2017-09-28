//
// Created by Dario Rendon.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;


void printMatrix(int m[3][3]);

void indexTranspose(int m[3][3]);

void pointerTranspose(int m[3][3]);

int main() {
    // will read from file called matrix.txt
    cout << "Will now read a 3x3 matrix from file \"matrix.txt\"" << endl;
    int m[3][3];
    ifstream infile;
    infile.open("matrix.txt");
    if (!infile) {
        cout << "Unable to open matrix.txt" << endl;
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        // reading and delimiting input file by spaces and commas
        string line;
        getline(infile, line);
        string::size_type n = 0;

        while ((n = line.find(',', n)) != std::string::npos) {
            line.replace(n, 1, 1, ' ');
            n++;
        }
        istringstream s(line);
        // finally setting variables from input
        s >> m[i][0] >> m[i][1] >> m[i][2];
    }
    indexTranspose(m);
    pointerTranspose(m);
}

// prints matrix with the first index representing the rows and the second the columns
void printMatrix(int m[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    }

void indexTranspose(int m[3][3]) {
    cout << "Transposing the following matrix using array indices: " << endl;
    printMatrix(m);
    int t[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            t[j][i] = m[i][j];
        }
    }
    cout << "Transposed matrix is: " << endl;
    printMatrix(t);
}

void pointerTranspose(int m[3][3]) {
    cout << "Transposing the following matrix using pointers: " << endl;
    printMatrix(m);
    int t[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *(*(t + j) + i) = *(*(m + i) + j);
        }
    }
    cout << "Transposed matrix is: " << endl;
    printMatrix(t);
}