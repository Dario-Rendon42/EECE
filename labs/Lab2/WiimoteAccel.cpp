#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main()
{
    WiimoteAcell* wma1;
    wma1->Listen();
    delete wma1;
}

class WiimoteAcell {
private:
    int fd; // Wiimote event file
public:
    WiimoteAcell() {
        // Open Wiimote event file
        fd = open("/dev/input/event0", O_RDONLY);
        if (fd == -1)
        {
            std::cerr << "Error: Could not open event file - forgot sudo?\n";
            exit(1);
        }
    }

    ~WiimoteAcell() {
        // Close Wiimote event file
        close(fd);
        return 0;
    }

    void Listen() {
        // Read a packet of 16 bytes from Wiimote
        char buffer[16];
        read(fd, buffer, 16);

        // Extract code (byte 10) and value (byte 12) from packet
        int code = buffer[10];
        short acceleration = * (short *) (buffer + 12);

        AccelerationEvent(code, acceleration);
    }

    virtual void AccelerationEvent(int code, short acceleration) {
        // Print them
        std::cout << "Code = " << code << ", acceleration = " << acceleration << '\n';
    }
};