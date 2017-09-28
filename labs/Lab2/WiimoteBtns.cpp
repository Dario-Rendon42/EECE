#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main() {
    WiimoteBtns *wmb1;
    wmb1->Listen();
    delete wmb1;
}

class WiimoteBtns {
private:
    int fd;
public:
    WiimoteBtns() {
        // Open Wiimote event file
        fd = open("/dev/input/event2", O_RDONLY);
        if (fd == -1) {
            std::cerr << "Error: Could not open event file - forgot sudo?\n";
            exit(1);
        }
    }

    // Close Wiimote event file
    ~WiimoteBtns() {
        close(fd);
        return 0;
    }

    void Listen() {
        while (true) {
            // Read a packet of 32 bytes from Wiimote
            char buffer[32];
            read(fd, buffer, 32);

            // Extract code (byte 10) and value (byte 12) from packet
            ButtonEvent(buffer[10], buffer[12]);
        }
    }

    void ButtonEvent(int code, int value) {
        // Print them
        std::cout << "Code = " << code << ", value = " << value << '\n';
    }
};