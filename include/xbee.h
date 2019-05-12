//
// Created by ajinkya on 5/11/19.
// Xbee specific API only xbee code should go here
//

#ifndef SWARM_XBEE_H
#define SWARM_XBEE_H

#include <stdbool.h>

#define XBEE_MAC_ID_SIZE 8
#define XBEE_NETWORK_ADDR_SIZE 2
#define XBEE_STORED_ADDR_LIST_SIZE 10

//Definitions for xbee_msg_settings.apiFrameFormat
#define XBEE_API_FRAME_FORMAT_WITHOUT_ESCAPE_CHARACTERS  0
#define XBEE_API_FRAME_FORMAT_WITH_ESCAPE_CHARACTERS  1
//Definitions for xbee_msg_settings.options
#define XBEE_API_OPTIONS_DISABLE_RETRIES 0x10
#define XBEE_API_OPTIONS_ENABLE_APS_ENCRIPTION 0x20
#define XBEE_API_OPTIONS_USE_EXTENDED_TIMEOUT 0x40
typedef enum{
  XBEE_INIT_SUCCESSFUL = 1
}xbee_init_status;
typedef struct{
  unsigned char apiFrameFormat; //Use macros above
  unsigned char broadcastRadius;
  unsigned char options; //Use macros above
}xbee_init_config;
/// Initializes Xbee module. Returns status
/// \param[IN] config Configuration to be used for transmiting
xbee_init_status xbee_init(xbee_init_config config);

typedef enum{
  XBEE_CREATE_TRANMIT_REQUEST_SUCCESSFUL = 1,
  XBEE_CREATE_TRANMIT_REQUEST_PAYLOAD_TOO_LONG = -1,
  XBEE_CREATE_TRANMIT_REQUEST_COULD_NOT_FIND_NETWORK_ID = -2
}xbee_create_transmit_request_status;
/// Constructs Xbee frame using given data. Returns success.
/// Caution this creates a transmit request frame.
/// Call xbee_init() and xbee_add_network_addr_from_mac_pair) before using
/// \param[IN] destinationMacID Hardware address for
/// \param[IN] payload Contains actual message to be sent
/// \param[out] frame contains the formated frame that can be sent to xbee
/// \param[out] size size of frame
xbee_create_transmit_request_status
xbee_create_transmit_request(const unsigned char destinationMacID[XBEE_MAC_ID_SIZE],
                             const unsigned char* payload,
                             unsigned char* frame, int* size);

/// Retrives network ID from mac id. Returns false if address is not stored
/// \param[IN] macID Machine Address of Xbee
/// \param[OUT] networkAddress Network Address of Xbee
bool xbee_get_network_addr_from_mac_id(const unsigned char* macID,
                                       unsigned char* networkAddress);

typedef struct {
  unsigned char destinationMacID[XBEE_MAC_ID_SIZE];
  unsigned char destinationNetworkAddr[XBEE_NETWORK_ADDR_SIZE];
}xbee_mac_id_network_addr_pair;
/// Saves the xbee_mac_id_network_addr_pair to be used when constructing frames
/// Returns false if list is full
/// \param[IN] pair Pair of network Address and Machine ID to be stored
/// \param[OUT] index Index for future reference
bool xbee_add_network_addr_mac_id_pair(const xbee_mac_id_network_addr_pair pair, int *index);

/// Removes xbee_mac_id_network_addr_pair from the list
/// \param[IN] index Index of pair to be removed.
void xbee_remove_network_addr_from_mac_pair(int index);

#endif //SWARM_XBEE_H
