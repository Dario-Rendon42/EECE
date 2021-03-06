#include <iostream>
using namespace std;

class Vector;


int main() {
    Vector v;
    string options[] = {
            "Print the array",
            "Add one element",
            "Remove last element",
            "Exit"
    };
    while(true) {
        cout << "Main menu:" << endl;
        cout << endl;
        cout << "1. " + options[0] << endl;
        cout << "2. " + options[1] << endl;
        cout << "3. " + options[2] << endl;
        cout << "4. " + options[3] << endl;
        int choice;
        cout << "Select an option: ";
        cin >> choice;
        cout << endl;
        switch(choice) {
            case 1:
                cout << "You selected \"" + options[0] + "\"" << endl;
                v.PrintVector();
                break;
            case 2:
                cout << "You selected \"" + options[1] + "\"" << endl;
                v.AddElement();
                break;
            case 3:
                cout << "You selected \"" + options[2] + "\"" << endl;
                v.RemoveElement();
                break;
            case 4:
                cout << "You selected \"" + options[3] + "\"" << endl;
                delete v;
                return 0;
            default:
                cout << "Please choose one of the options" << endl;
        }
    }
}


class Vector {
private:
    int v_count;
    int v_size;
    double* v;

    void Grow() {
        double* nv = new double[v_size * 2];
        for(int i = 0; i < v_count; i++) {
            nv[i] = v[i];
        }
        delete [] v;
        v = nv;
        cout << "Vector grown" << endl;
        cout << "Previous capacity: " << v_size << " elements" << endl;
        v_size *= 2;
        cout << "New capacity: " << v_size << " elements" << endl;
    }

    void Shrink() {
        cout << "Vector shrunk" << endl;
        cout << "Previous capacity: " << v_size << " elements" << endl;
        v_size /= 2;
        cout << "New capacity: " << v_size << " elements" << endl;
        double* nv = new double[v_size];
        for(int i = 0; i < v_count; i++) {
            nv[i] = v[i];
        }
        delete [] v;
        v = nv;
    }

public:
    Vector() {
        v_count = 0;
        v_size = 2;
        v = new double[v_size];
    }

    ~Vector() {
        delete [] v;
    }

    void AddElement() {
        if (v_count +  1>= v_size) {
            Grow();
        }
        cout << "Enter the new element: ";
        cin >> v[v_count];
        v_count++;
    }

    void PrintVector() {
        for(int i = 0; i < v_count; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    void RemoveElement() {
        if(v_count > 0) {
            v[v_count] = NULL;
            v_count--;
            if(v_count < .3 * v_size) {
                Shrink();
            }
        }
    }
};
