//
// Created by Dario Rendon
//
#include <iostream>
#include <cmath>

using namespace std;

void printSizes();

double myPow(int base, int power);

int myMax(int a, int b);

void printMultiBase(int a);

string convertFromBase10(int a, int base);

int main() {
    int a, b;

    cout << "Please enter a positive integer: " << endl;
    do {
        while (!(cin >> a) || (cin.get() != '\n')) {
            cout << "\nError: Input must be a positive integer! Try again: ";
            cin.clear();
            cin.ignore(65535, '\n');
        }
        if (a < 1) {
            cout << "Must be a positive integer. Try again: " << endl;
        }
    } while (a < 1);
    cout << "Please enter a second positive integer: " << endl;
    do {
        while (!(cin >> b) || (cin.get() != '\n')) {
            cout << "\nError: Input must be a positive integer! Try again: ";
            cin.clear();
            cin.ignore(65535, '\n');
        }
        if (b < 1) {
            cout << "Must be a positive integer. Try again: " << endl;
        }
    } while (b < 1);
    printSizes();
    cout << a << " raised to the power of " << b << " is " << myPow(a, b) << endl;
    cout << myMax(a, b) << " is the larger number between " << a << " and " << b << endl;
    printMultiBase(a);
    printMultiBase(b);
    return 0;
}

void printSizes() {
    cout << "Displaying sizes of various datatypes:" << endl;
    cout << "A bool is " << sizeof(bool) << " bytes long" << endl;
    cout << "A char is " << sizeof(char) << " bytes long" << endl;
    cout << "A int is " << sizeof(int) << " bytes long" << endl;
    cout << "A float is " << sizeof(float) << " bytes long" << endl;
    cout << "A double is " << sizeof(double) << " bytes long" << endl;
}

double myPow(int base, int power) {
    return pow(base, power);
}

int myMax(int a, int b) {
    return max(a, b);
}

void printMultiBase(int a) {
    cout << "Printing a number in various bases: " << endl;
    cout << "Decimal: " << a << endl;
    cout << "Hexadecimal: " << convertFromBase10(a, 16) << endl;
    cout << "Octal: " << convertFromBase10(a, 8) << endl;
    cout << "Binary: " << convertFromBase10(a, 2) << endl;
}

// helper function to convert the given int to the specified base in a string representation
string convertFromBase10(int a, int base) {
    string r;
    while (a > 0) {
        char s;
        int mod = a % base;
        if (mod < 10) {
            s = '0' + mod;
        } else {
            s = 'A' + (mod - 10);
        }
        r = s + r;
        a /= base;
    }
    return r;
}