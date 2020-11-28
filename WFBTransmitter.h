//
// Created by consti10 on 28.11.20.
//

#ifndef XOPENHD_WFBTRANSMITTER_H
#define XOPENHD_WFBTRANSMITTER_H


#include <cstdlib>
#include <cstdint>

class WFBTransmitter {
public:
    void sendPacket(const uint8_t* data,const std::size_t dataLen,const uint8_t multiplexIndex);
};


#endif //XOPENHD_WFBTRANSMITTER_H
