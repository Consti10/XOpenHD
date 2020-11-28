//
// Created by consti10 on 28.11.20.
//

#ifndef XOPENHD_WFBTRANSMITTER_H
#define XOPENHD_WFBTRANSMITTER_H


#include <vector>
#include "WFBHelper.hpp"


class WFBTransmitter {
public:
    explicit WFBTransmitter(std::vector<int> socks1):socks(socks1){

    }
    void sendPacket(const uint8_t* data,const std::size_t dataLen,const uint8_t multiplexIndex);
private:
    const std::vector<int> socks;
private:
    int pb_transmit_packet(int seq_nr, uint8_t *packet_transmit_buffer, int packet_header_len, const uint8_t *packet_data, int packet_length, int num_interfaces, int param_transmission_mode, int best_adapter);
};


#endif //XOPENHD_WFBTRANSMITTER_H
