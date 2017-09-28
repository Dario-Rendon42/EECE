/**
 * @file   Vector.cpp
 * @Author John Kimani (j.kimani@neu.edu)
 * @date   September, 2017
 * @brief  Process a vector array.
 *
 * Creates and operates a vector array by growing and shrinking
 * when necessary
 */
#include <iostream>
#include <limits>
using namespace std;

class Vector1 {
private:
    double *v;		// the array vector
    int count;  	// keeps track of number of elements in the vector
    int size;		// maximum size of the vector

public:
    Vector1();			// Default Constructor
    ~Vector1();			// Destructor
    void Initialize();
    void Finalize();
    void Grow();
    void AddElement();
    void PrintVector();
    void RemoveElement();
    void Shrink();
};

/**
 * Constructor Initialize vector class data members
 *  - Sets the initial dimensions of the vector
 *  - Requests initial memory
 *
 * @param  None	Default constructor does not need arguments.
 * @return	None Default constructor does not return anything.
 */
Vector1::Vector1()
{
    // initialize class members
    count = 0;
    size = 2;
    v = new double[size];
    cout << "Vector initialized..." << endl;
}

/**
 * Destructor to free the memory allocated to the vector
 * - Uses delete to free the memory pointed to by v
 *
 * @param  None	Destructor does not need arguments.
 * @return	None Destructor does not return anything.
 */
Vector1::~Vector1()
{
    delete [] v;		// free up the memory
    cout << "Vector destroyed..." << endl;
}

/**
 * Doubles the capacity of the current vector.
 *
 * - Uses new and delete to allocate larger memory for the vector
 * - Releases the old shorter memory
 * @param None
 * @return	None
 */
void Vector1::Grow()
{
    try {
        double *new_vector = new double[size * 2];
        // transfer elements to the new array
        for (int i = 0; i < count; i++) {
            new_vector[i] = v[i];
        }
        // release the old memory and reassign pointers
        delete[] v;
        v = new_vector;
        cout << "Vector grown:" << endl;
        cout << "Previous capacity: " << size << " elements" << endl;
        size = size * 2;
        cout << "New capacity: " << size << " elements" << endl;
    } catch(bad_alloc &e) {
        cerr << "Error growing vector. Not enough memory!" << endl;
    }
}

/**
 * Adds an element to the current vector.
 *
 * - Adds an element at the end of the array vector
 * @param None
 * @return	None
 */
void Vector1::AddElement()
{	// check if array is full
    if (count == size) {
        Grow();
    }
    if(count != size) {
        // read and add a new element into the array
        double value = 0.0;
        cout << "Enter new element: ";

        // Get and check for input errors
        while(!(cin >> value) || (cin.get() != '\n')) {
            cout << "\nError: Input must be a double! Try again: " ;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        v[count] = value;
        count++;
        cout << "Element added" << endl;
    } else {
        cout << "Element not added. Vector is full!" << endl;
    }
}

/**
 * Prints the elements of the current vector.
 *
 * @param None
 * @return	None
 */
void Vector1::PrintVector()
{
    // Check if empty
    if( count == 0) {
        cout << "Nothing to print. Vector is empty!" << endl;
    } else {
        // prints out the elements using count
        cout << "[ ";
        for(int i = 0;i < count; i++) {
            cout << v[i] <<", ";
        }
        cout<< "]" << endl;
    }
}

/**
 * Removes an element to the current vector.
 *
 * - Removes an element at the end of the array vector
 * @param None
 * @return	None
 */
void Vector1::RemoveElement()
{
    // check to make sure the array is not empty
    if( count == 0 ) {
        cout<<"There are no elements to be removed in the array"<<endl;
    } else {	// remove an element and resize the array if necessary
        count--;
        if (count < (size * .3)) {
            Shrink();
        }
        cout << "Element removed" << endl;
    }
}

/**
 * Reduces the size of the current vector by a factor of two.
 *
 * - Uses new and delete to allocate larger memory for the vector
 * - Releases the old shorter memory
 * @param None
 * @return	None
 */
void Vector1::Shrink()
{
    try {
        double *new_vector = new double[size / 2];
        // transfer elements to the new array
        for (int i = 0; i < count; i++) {
            new_vector[i] = v[i];
        }
        // release the old memory and reassign pointers
        delete[] v;
        v = new_vector;
        cout << "Vector shrunk:" << endl;
        cout << "Previous capacity: " << size << " elements" << endl;
        size = size / 2;
        cout << "New capacity: " << size << " elements" << endl;
    } catch(bad_alloc &e) {
        cerr << "Error shrinking vector. Not enough memory!" << endl;
    }
}

/**
 * Main function to operate on the vector.
 *
 * - Creates a vector object to operate on the vector
 * @param None
 * @return		int value to indicate success or not
 */
int main()
{
    Vector1 vect;
    int choice = 0; // Define an integer to hold input choice

    //Repeat the menu prompt until the exit command is selected
    while(choice != 4) {
        //Print the main menu
        cout << endl << endl << "Main menu:" << endl;
        cout << "1. Print the array" << endl;
        cout << "2. Add one element" << endl;
        cout << "3. Remove last element" << endl;
        cout << "4. Exit" << endl << endl;
        cout << "Select an option: ";

        // Get and check for input errors
        while(!(cin >> choice) || (cin.get() != '\n')) {
            cout << "\nError: Input must be an integer! Try again: " ;
            cin.clear();
            cin.ignore(65535, '\n');
        }

        // Carry appropriate action based on the input
        switch(choice){
            case 1:
                vect.PrintVector();
                break;
            case 2:
                vect.AddElement();
                break;
            case 3:
                vect.RemoveElement();
                break;
            case 4:
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        } // end switch
    } // end while
    cout << "Program Terminating..." << endl;
}