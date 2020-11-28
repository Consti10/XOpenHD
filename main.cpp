#include <iostream>
#include "WFBTransmitter.h"

int main() {
    WFBTransmitter wfbTransmitter({0});
    wfbTransmitter.sendPacket(nullptr,0,0);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
