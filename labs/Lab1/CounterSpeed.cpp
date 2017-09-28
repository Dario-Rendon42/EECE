#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <ctime>

using namespace std;

// Physical base address of GPIO 
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window 
const unsigned gpio_size = 0xff;

const int gpio_led1_offset = 0x12C;  // Offset for LED1 
const int gpio_led2_offset = 0x130;  // Offset for LED2 
const int gpio_led3_offset = 0x134;  // Offset for LED3 
const int gpio_led4_offset = 0x138;  // Offset for LED4 
const int gpio_led5_offset = 0x13C;  // Offset for LED5 
const int gpio_led6_offset = 0x140;  // Offset for LED6 
const int gpio_led7_offset = 0x144;  // Offset for LED7 
const int gpio_led8_offset = 0x148;  // Offset for LED8 

const int gpio_sw1_offset = 0x14C;  // Offset for Switch 1 
const int gpio_sw2_offset = 0x150;  // Offset for Switch 2 
const int gpio_sw3_offset = 0x154;  // Offset for Switch 3 
const int gpio_sw4_offset = 0x158;  // Offset for Switch 4 
const int gpio_sw5_offset = 0x15C;  // Offset for Switch 5 
const int gpio_sw6_offset = 0x160;  // Offset for Switch 6 
const int gpio_sw7_offset = 0x164;  // Offset for Switch 7 
const int gpio_sw8_offset = 0x168;  // Offset for Switch 8 

const int gpio_pbtnl_offset = 0x16C;  // Offset for left push button 
const int gpio_pbtnr_offset = 0x170;  // Offset for right push button 
const int gpio_pbtnu_offset = 0x174;  // Offset for up push button 
const int gpio_pbtnd_offset = 0x178;  // Offset for down push button 
const int gpio_pbtnc_offset = 0x17C;  // Offset for center push button 

class ZedBoard {
private:
    char *pBase;
    int fd;
public:

    /**
     * Initialize general-purpose I/O
     *  - Opens access to physical memory /dev/mem
     *  - Maps memory at offset 'gpio_address' into virtual address space
     */
    ZedBoard() {
        fd = open("/dev/mem", O_RDWR);
        pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                              fd, gpio_address);

        // Check error
        if (pBase == MAP_FAILED) {
            cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
            exit(1); // Returns 1 to the operating system;
        }
    }

    /**
     * Close general-purpose I/O.
     */
    ~ZedBoard() {
        munmap(pBase, gpio_size);
        close(fd);
    }

    /**
     * Write a 4-byte value at the specified general-purpose I/O location.
     *
     * @parem offset	Offset where device is mapped.
     * @param value	Value to be written.
     */
    void RegisterWrite(int offset, int value) {
        *(int *) (pBase + offset) = value;
    }

    /**
     * Read a 4-byte value from the specified general-purpose I/O location.
     *
     * @param offset	Offset where device is mapped.
     * @return		Value read.
     */
    int RegisterRead(int offset) {
        return *(int *) (pBase + offset);
    }

    /** Changes the state of an LED (ON or OFF)
    * @param ledNum LED number (0 to 7)
    * @param state State to change to (ON or OFF)
    */
    void Write1Led(int ledNum, int state) {
        int ledOffset = 0x4 * ledNum + gpio_led1_offset;
        RegisterWrite(ledOffset, state);
    }

    /** Reads the value of a switch
     * - Uses base address of I/O
     * @param switchNum Switch number (0 to 7)
     * @return Switch value read
     */
    int Read1Switch(int switchNum) {
        int switchOffset = 0x4 * switchNum + gpio_sw1_offset;
        return RegisterRead(switchOffset);
    }


    /** Read the state of the buttons
     *
     */
    int PushButtonGet() {
        for (int i = 0; i < 5; i++) {
            int value = RegisterRead(gpio_pbtnl_offset + 4 * i);
            if (value != 0) {
                return i + 1;
            }
        }
        return 0;
    }


    /**
     * Set the state of the LEDs with the given value.
     *
     * @param value Value between 0 and 255 written to the LEDs
     */
    void WriteAllLeds(int value) {
        for (int ledIndex = 0; ledIndex < 8; ledIndex++) {
            int ledState = value % 2;
            value = value / 2;
            Write1Led(ledIndex, ledState);
        }
    }

    /** Reads all the switches and returns their value in a single integer.
     *
     * @return A value that represents the value of the switches
     */
    int ReadAllSwitches() {
        int sum = 0;
        for (int i = 7; i >= 0; i--) {
            sum *= 2;
            sum += Read1Switch(i);
        }
        return sum;
    }
};


/** 
 * Main function to interact with I/O Interfaces
 */
int main() {

    // Initialize
    ZedBoard *z1 = new ZedBoard();


    int ledValue = z1->ReadAllSwitches();
    int prevButtonValue = 0;
    int nextButtonValue = 0;
    int counterSpeed = 0;
    int counterDirection = 1;
    clock_t startTime = clock();
    while (true) {
        double elapsedSeconds = double(clock() - startTime) / CLOCKS_PER_SEC;
        if (counterSpeed > 0) {
            double counterTime = 1.0 / counterSpeed;
            if (elapsedSeconds > counterTime) {
                startTime = clock();
                ledValue += counterDirection;
            }
        }
        z1->WriteAllLeds(ledValue);
        nextButtonValue = z1->PushButtonGet();
        if (nextButtonValue != prevButtonValue) {
            prevButtonValue = nextButtonValue;
            cout << nextButtonValue << endl;
            switch (nextButtonValue) {
                // Left
                case 1:
                    counterDirection = -1;
                    break;
                    // Right
                case 2:
                    counterDirection = 1;
                    break;
                    // Up
                case 3:
                    counterSpeed++;
                    break;
                    // Down
                case 4:
                    counterSpeed--;
                    counterSpeed = counterSpeed < 0 ? 0 : counterSpeed;
                    break;
                    // Center
                case 5:
                    ledValue = z1->ReadAllSwitches();
                    break;
            }
        }
    }


    // Done
    delete z1;
}
