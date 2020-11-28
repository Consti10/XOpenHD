//
// Created by consti10 on 28.11.20.
//

#include "WFBTransmitter.h"
#include <iostream>


void WFBTransmitter::sendPacket(const uint8_t *data, const std::size_t dataLen, const uint8_t multiplexIndex) {
    std::cout << "Send packet" << std::endl;
}

int WFBTransmitter::pb_transmit_packet(int seq_nr, uint8_t *packet_transmit_buffer, int packet_header_len,
                                       const uint8_t *packet_data, int packet_length, int num_interfaces,
                                       int param_transmission_mode, int best_adapter) {
    int i = 0;


    /*
     * Add header outside of FEC
     */
    wifi_packet_header_t *wph = (wifi_packet_header_t *)(packet_transmit_buffer + packet_header_len);

    wph->sequence_number = seq_nr;


    memcpy(packet_transmit_buffer + packet_header_len + sizeof(wifi_packet_header_t), packet_data, packet_length);

    int plen = packet_length + packet_header_len + sizeof(wifi_packet_header_t);


    /*
     * TODO: fix magic number, 5 means "all interfaces"
     */
    if (best_adapter == 5) {
        for (i = 0; i < num_interfaces; ++i) {
            //if (write(socks[i], packet_transmit_buffer, plen) < 0 ) fprintf(stderr, "!");
            if (write(socks[i], packet_transmit_buffer, plen) < 0) {
                return 1;
            }
        }
    } else {
        //if (write(socks[best_adapter], packet_transmit_buffer, plen) < 0 ) fprintf(stderr, "!");
        if (write(socks[best_adapter], packet_transmit_buffer, plen) < 0) {
            return 1;
        }
    }

    return 0;
}
