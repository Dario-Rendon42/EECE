#include <iostream>

using namespace std;

class Led {
private:
    int data;
    int *parr;

public:
    int getData() {
        return data;
    }
    void setData(int val);
    Led();
    Led(int val);
    ~Led();
};

void Led::setData(int val) {
    data = val;
}

Led::Led() {
    data = 50;
}

Led::Led(int val) {
    data = val;
    parr = new int;
}

Led::~Led() {
    delete parr;
}

int main() {
    Led led1; // auto calls default constructor
    led1.setData(3);
    Led led2(10); // calls a specific constructor
    Led led3[5]; // makes an array of 5 Led elements and calls default constructor for each
//    cout << led1.data; // won't work because .data isn't public
    cout << led1.getData() << endl;
    cout << led2.getData() << endl;
    for(int i = 0; i < 5; i++) {
        cout << led3[i].getData() << endl;
    }
}