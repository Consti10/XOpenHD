#include <iostream>
#include "fec.h"
#include "openhdlib.h"
//
#include "fec.h"
#include "openhdlib.h"
#include "wifibroadcast.h"
#include <fcntl.h>
#include <getopt.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netpacket/packet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include "WFBTransmitter.h"

int main() {
    WFBTransmitter wfbTransmitter;
    wfbTransmitter.sendPacket(nullptr,0,0);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
