//
// Created by consti10 on 28.11.20.
//

#ifndef XOPENHD_WFBHELPER_H
#define XOPENHD_WFBHELPER_H

#include <cstdlib>
#include <cstdint>
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

//TODO make defines constexpr
#define MAX_PACKET_LENGTH 4192
#define MAX_USER_PACKET_LENGTH 2278
#define MAX_DATA_OR_FEC_PACKETS_PER_BLOCK 32

#define IEEE80211_RADIOTAP_MCS_HAVE_BW 0x01
#define IEEE80211_RADIOTAP_MCS_HAVE_MCS 0x02
#define IEEE80211_RADIOTAP_MCS_HAVE_GI 0x04
#define IEEE80211_RADIOTAP_MCS_HAVE_FMT 0x08

#define IEEE80211_RADIOTAP_MCS_BW_20 0
#define IEEE80211_RADIOTAP_MCS_BW_40 1
#define IEEE80211_RADIOTAP_MCS_BW_20L 2
#define IEEE80211_RADIOTAP_MCS_BW_20U 3
#define IEEE80211_RADIOTAP_MCS_SGI 0x04
#define IEEE80211_RADIOTAP_MCS_FMT_GF 0x08
#define IEEE80211_RADIOTAP_MCS_HAVE_FEC 0x10
#define IEEE80211_RADIOTAP_MCS_HAVE_STBC 0x20

#define IEEE80211_RADIOTAP_MCS_FEC_LDPC 0x10
#define IEEE80211_RADIOTAP_MCS_STBC_MASK 0x60
#define IEEE80211_RADIOTAP_MCS_STBC_1 1
#define IEEE80211_RADIOTAP_MCS_STBC_2 2
#define IEEE80211_RADIOTAP_MCS_STBC_3 3
#define IEEE80211_RADIOTAP_MCS_STBC_SHIFT 5

namespace WFBHelper{
    // copy paste from tx_rawsock
    static u8 u8aRadiotapHeader[] = {
            0x00, 0x00,             // <-- radiotap version
            0x0c, 0x00,             // <- radiotap header length
            0x04, 0x80, 0x00, 0x00, // <-- radiotap present flags (rate + tx flags)
            0x00,                   // datarate (will be overwritten later in packet_header_init)
            0x00,                   // ??
            0x00, 0x00              // ??
    };
    static u8 u8aRadiotapHeader80211N[] __attribute__((unused)) = {
            0x00, 0x00,             // <-- radiotap version
            0x0d, 0x00,             // <- radiotap header length
            0x00, 0x80, 0x08, 0x00, // <-- radiotap present flags:  RADIOTAP_TX_FLAGS + RADIOTAP_MCS
            0x08, 0x00,             // RADIOTAP_F_TX_NOACK
            0, 0, 0                 // bitmap, flags, mcs_index
    };
    static u8 u8aIeeeHeader_data_short[] = {
            0x08, 0x01, 0x00, 0x00, // frame control field (2bytes), duration (2 bytes)
            0xff                    // port =  1st byte of IEEE802.11 RA (mac) must be something odd (wifi hardware determines broadcast/multicast through odd/even check)
    };
    static u8 u8aIeeeHeader_data[] = {
            0x08, 0x02, 0x00, 0x00,             // frame control field (2bytes), duration (2 bytes)
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, // port = 1st byte of IEEE802.11 RA (mac) must be something odd (wifi hardware determines broadcast/multicast through odd/even check)
            0x13, 0x22, 0x33, 0x44, 0x55, 0x66, // mac
            0x13, 0x22, 0x33, 0x44, 0x55, 0x66, // mac
            0x00, 0x00                          // IEEE802.11 seqnum, (will be overwritten later by Atheros firmware/wifi chip)
    };
    static u8 u8aIeeeHeader_rts[] = {
            0xb4, 0x01, 0x00, 0x00, // frame control field (2 bytes), duration (2 bytes)
            0xff,                   // port = 1st byte of IEEE802.11 RA (mac) must be something odd (wifi hardware determines broadcast/multicast through odd/even check)
    };
    static int packet_header_init80211N(uint8_t *packet_header, int type, int port) {
        u8 *pu8 = packet_header;

        int port_encoded = 0;

        memcpy(packet_header, u8aRadiotapHeader80211N, sizeof(u8aRadiotapHeader80211N));
        pu8 += sizeof(u8aRadiotapHeader80211N);

        switch (type) {
            case 0: {
                /*
                 * Short DATA frame
                 */
                fprintf(stderr, "using short DATA frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_data_short[4] = port_encoded;

                /*
                 * Copy data short header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_data_short, sizeof(u8aIeeeHeader_data_short));
                pu8 += sizeof(u8aIeeeHeader_data_short);

                break;
            }
            case 1: {
                /*
                 * Standard DATA frame
                 *
                 */
                fprintf(stderr, "using standard DATA frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_data[4] = port_encoded;

                /*
                 * Copy data header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_data, sizeof(u8aIeeeHeader_data));
                pu8 += sizeof(u8aIeeeHeader_data);

                break;
            }
            case 2: {
                /*
                 * RTS frame
                 *
                 */
                fprintf(stderr, "using RTS frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_rts[4] = port_encoded;

                /*
                 * Copy RTS header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_rts, sizeof(u8aIeeeHeader_rts));
                pu8 += sizeof(u8aIeeeHeader_rts);

                break;
            }
            default: {
                fprintf(stderr, "ERROR: Wrong or no frame type specified (see -t parameter)\n");

                exit(1);

                break;
            }
        }

        /*
         * The length of the header
         */
        return pu8 - packet_header;
    }
    static int packet_header_init(uint8_t *packet_header, int type, int rate, int port) {
        u8 *pu8 = packet_header;

        int port_encoded = 0;

        switch (rate) {
            case 1: {
                u8aRadiotapHeader[8] = 0x02;
                break;
            }
            case 2: {
                u8aRadiotapHeader[8] = 0x04;
                break;
            }
            case 5: {
                // 5.5
                u8aRadiotapHeader[8] = 0x0b;
                break;
            }
            case 6: {
                u8aRadiotapHeader[8] = 0x0c;
                break;
            }
            case 11: {
                u8aRadiotapHeader[8] = 0x16;
                break;
            }
            case 12: {
                u8aRadiotapHeader[8] = 0x18;
                break;
            }
            case 18: {
                u8aRadiotapHeader[8] = 0x24;
                break;
            }
            case 24: {
                u8aRadiotapHeader[8] = 0x30;
                break;
            }
            case 36: {
                u8aRadiotapHeader[8] = 0x48;
                break;
            }
            case 48: {
                u8aRadiotapHeader[8] = 0x60;
                break;
            }
            default: {
                fprintf(stderr, "ERROR: Wrong or no data rate specified (see -d parameter)\n");
                exit(1);

                break;
            }
        }

        memcpy(packet_header, u8aRadiotapHeader, sizeof(u8aRadiotapHeader));
        pu8 += sizeof(u8aRadiotapHeader);

        switch (type) {
            case 0: {
                /*
                 * Short DATA frame
                 */
                fprintf(stderr, "using short DATA frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_data_short[4] = port_encoded;

                /*
                 * Copy data short header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_data_short, sizeof(u8aIeeeHeader_data_short));
                pu8 += sizeof(u8aIeeeHeader_data_short);


                break;
            }
            case 1: {
                /*
                 * Standard DATA frame
                 */
                fprintf(stderr, "using standard DATA frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_data[4] = port_encoded;

                /*
                 * Copy data header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_data, sizeof(u8aIeeeHeader_data));
                pu8 += sizeof(u8aIeeeHeader_data);


                break;
            }
            case 2: {
                /*
                 * RTS frame
                 */
                fprintf(stderr, "using RTS frames\n");

                port_encoded = (port * 2) + 1;

                /*
                 * First byte of RA mac is the port
                 */
                u8aIeeeHeader_rts[4] = port_encoded;

                /*
                 * Copy RTS header to pu8
                 */
                memcpy(pu8, u8aIeeeHeader_rts, sizeof(u8aIeeeHeader_rts));
                pu8 += sizeof(u8aIeeeHeader_rts);


                break;
            }
            default:
                fprintf(stderr, "ERROR: Wrong or no frame type specified (see -t parameter)\n");

                exit(1);


                break;
        }

        /*
         * The length of just the header
         */
        return pu8 - packet_header;
    }
}

#endif //XOPENHD_WFBHELPER_H
