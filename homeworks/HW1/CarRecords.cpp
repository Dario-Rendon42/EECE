//
// Created by Dario Rendon
//
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;
    string color;
public:
    // default constructor sets values to default so no need to define one

    // sets all fields
    void setFields(string mk, string md, int yr, string cl) {
        make = mk;
        model = md;
        year = yr;
        color = cl;
    }

    string getMake() {
        return make;
    }

    string getModel() {
        return model;
    }

    int getYear() {
        return year;
    }

    string getColor() {
        return color;
    }

    void print() {
        cout << getMake() << ", " << getModel() << ", " << getYear() << ", " << getColor() << endl;
    }

    static int sort_by_make(Car c1, Car c2) {
        return c1.getMake() < c2.getMake();
    }

    static int sort_by_year(Car c1, Car c2) {
        return c1.getYear() < c2.getYear();
    }

    bool operator==(Car rhs) {
        return this->getMake() == rhs.getMake() &&
               this->getModel() == rhs.getModel() &&
               this->getYear() == rhs.getYear() &&
               this->getColor() == rhs.getColor();
    }
};

class CarRecords {
private:
    int arraySize; // keep track of number of records
    ifstream infile;
    Car *cars;
public:
    // Reads file records to array
    CarRecords(int size) {
        size = size > 10 ? 10 : size;
        size = size < 0 ? 0 : size;
        arraySize = size;
        cars = new Car[arraySize];
        infile.open("CarRecords.txt");
        if (!infile) {
            cout << "Unable to open CarRecords.txt" << endl;
            exit(1);
        }
        for (int i = 0; i < arraySize; i++) {
            // declaring starting values for car
            string make;
            string model;
            int year;
            string color;

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
            s >> make >> model >> year >> color;

            // create car and put in array
            Car c;
            c.setFields(make, model, year, color);
            cars[i] = c;
        }
    }

    // – Destructor frees the memory allocated with new, and closes the file handler
    ~CarRecords() {
        delete[] cars;
        infile.close();
    }

    // prints out the car records from the array of objects
    void printCarRecords() {
        cout << "PRINTING " << arraySize << " RECORDS!" << endl;
        cout << "---------------------" << endl;
        for (int i = 0; i < arraySize; i++) {
            cars[i].print();
        }
        cout << endl;
    }

    // sorts the records in ascending order based on the make field
    void sort_cars_by_make() {
        cout << "SORTING RECORDS BY MAKE.....\n" << endl;
        sort(cars, cars + arraySize, Car::sort_by_make);
    }

    // sorts the records in descending order based on the year field
    void sort_cars_by_year() {
        cout << "SORTING RECORDS BY YEAR.....\n" << endl;
        sort(cars, cars + arraySize, Car::sort_by_year);
    }

    // identifies any repeated records, and prints them out when
    // found. Repeated records means that all the fields are the same
    void print_duplicates() {
        cout << "CHECKING FOR DUPLICATES...\n" << endl;
        bool dupe[arraySize];
        for (int i = 0; i < arraySize; i++) {
            dupe[i] = false;
        }
        for (int i = 0; i < arraySize; i++) {
            // if the element encountered has already been marked as a dupe skip it
            if (dupe[i]) {
                continue;
            }
            // start at i + 1 because previous elements have already been checked and it shouldn't check itself
            for (int j = i + 1; j < arraySize; j++) {
                // don't bother checking element if already marked as dupe
                if (dupe[j]) {
                    continue;
                }
                if(cars[i] == cars[j]) {
                    // print if it hasn't been marked as a dupe yet
                    if(!dupe[i]) {
                        cars[i].print();
                    }
                    if(!dupe[j]) {
                        cars[j].print();
                    }
                    dupe[i] = true;
                    dupe[j] = true;
                }
            }
        }
    }
};

int main() {
    int numRecs;
    cout << "Number or Records to read? ";
    cin >> numRecs;
    cout << endl;
    CarRecords *cr = new CarRecords(numRecs);
// Print car records
    cr->printCarRecords();
// Sort by Year
    cr->sort_cars_by_year();
// Print car records
    cr->printCarRecords();
// Sort by Make
    cr->sort_cars_by_make();
// Print car records
    cr->printCarRecords();
// Check for Duplicates
    cr->print_duplicates();
    delete cr;
} // end main
