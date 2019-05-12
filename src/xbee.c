//
// Created by ajinkya on 5/11/19.
//

#include "xbee.h"
#include <string.h>
#include <stdint.h>

#include "device.h"
#include "common.h"

#define XBEE_

/* Caution do not modify the header without modifying the macro for size*/
//Todo: Deal with struct packing
#define XBEE_TRANSMIT_REQUEST_FRAME_HEADER_SIZE 17
#define XBEE_TRANSMIT_REQUEST_FRAME_HEADER_DELIIMITER_SIZE 1
#define XBEE_TRANSMIT_REQUEST_FRAME_HEADER_LENGTH_SIZE 2
#define XBEE_DELIMITER 0x7E
typedef struct {
  unsigned char delimiter;
  unsigned char lengthMSB;
  unsigned char lengthLSB;
  unsigned char apiFrameFormat;
  unsigned char frameID;
  unsigned char destinationMacID[XBEE_MAC_ID_SIZE];
  unsigned char destinationNetworkAddr[XBEE_NETWORK_ADDR_SIZE];
  unsigned char broadcastRadius;
  unsigned char options;
}xbee_transmit_request_frame_header;

/* Global variables for the module*/
static struct {
  xbee_init_config config;
  xbee_mac_id_network_addr_pair addressList[XBEE_STORED_ADDR_LIST_SIZE];
  bool isAddressListPositionOccupied[XBEE_STORED_ADDR_LIST_SIZE];
  unsigned char lastUsedFrameId;
}mod;

/// Creates new frame id and returns it
static unsigned char xbee_generate_new_frame_id(){
  mod.lastUsedFrameId++;
  return mod.lastUsedFrameId;
}


xbee_init_status xbee_init(xbee_init_config config)
{
  mod.config = config;
  mod.lastUsedFrameId = 0;
  for (int i = 0; i < XBEE_STORED_ADDR_LIST_SIZE; i++) {
    common_set_char_array_to_zero(mod.addressList[i].destinationMacID, XBEE_MAC_ID_SIZE);
    common_set_char_array_to_zero(mod.addressList[i].destinationNetworkAddr,
                                  XBEE_NETWORK_ADDR_SIZE);
  }
  return XBEE_INIT_SUCCESSFUL;
}

bool xbee_get_network_addr_from_mac_id(const unsigned char* macID,
                                       unsigned char* networkAddress)
{
  int i;
  for (i = 0; i < XBEE_STORED_ADDR_LIST_SIZE; i++)
  {
    if(common_compare_char_arrays(macID, mod.addressList[i].destinationMacID,
                                  XBEE_NETWORK_ADDR_SIZE))
    {
      common_copy_char_array(mod.addressList[i].destinationNetworkAddr,
                             networkAddress,
                             XBEE_NETWORK_ADDR_SIZE);
      return true;
    }
  }

  return false;
}

bool xbee_add_network_addr_mac_id_pair(const xbee_mac_id_network_addr_pair pair, int *index)
{
  int i=0;
  while(mod.isAddressListPositionOccupied[i] && i < XBEE_STORED_ADDR_LIST_SIZE) i++;
  if(i == XBEE_STORED_ADDR_LIST_SIZE)
  {
    DEVICE_LOG_ERROR("Xbee Address space full");
    return false;
  }

  mod.addressList[i] = pair;
  mod.isAddressListPositionOccupied[i] = true;
  *index = i;

  return true;
}

void xbee_remove_network_addr_from_mac_pair(int index)
{
  mod.isAddressListPositionOccupied[index] = false;
}

unsigned char xbee_calculate_checksum(const unsigned char* data, int size)
{
  char checksum = 0;
  int i;
  for (i = 0; i < size; i++) {
    checksum += data[i];
  }

  return (unsigned char)(-checksum);
}

xbee_create_transmit_request_status
xbee_create_transmit_request(const unsigned char destinationMacID[XBEE_MAC_ID_SIZE],
                             const common_string payload,
                             common_string* frame, unsigned char* frameId)
{
  /* Weird but valid syntax warning. Casting char array as a xbee_transmit_request_frame_header
   * structure to make assembling the frame easier */
  xbee_transmit_request_frame_header* formattedMsg =
      (xbee_transmit_request_frame_header*) (frame->data);

  formattedMsg->delimiter = XBEE_DELIMITER;
  formattedMsg->apiFrameFormat = mod.config.apiFrameFormat;
  formattedMsg->broadcastRadius = mod.config.broadcastRadius;
  formattedMsg->options = mod.config.options;
  *frameId = xbee_generate_new_frame_id();
  formattedMsg->frameID = *frameId;

  int length = (XBEE_TRANSMIT_REQUEST_FRAME_HEADER_SIZE
                - XBEE_TRANSMIT_REQUEST_FRAME_HEADER_DELIIMITER_SIZE
                - XBEE_TRANSMIT_REQUEST_FRAME_HEADER_LENGTH_SIZE) + payload.size;

  /* Converting to bigendien to make sure portability */
  device_convert_number_to_bigendien((char*)&length,
                                     XBEE_TRANSMIT_REQUEST_FRAME_HEADER_LENGTH_SIZE,
                                     (char*)(&formattedMsg->lengthMSB));

  common_copy_char_array(destinationMacID,
                         formattedMsg->destinationMacID,
                         XBEE_MAC_ID_SIZE);

  if(!xbee_get_network_addr_from_mac_id(destinationMacID, formattedMsg->destinationNetworkAddr))
  {
    DEVICE_LOG_ERROR("Could not find network id");
    return XBEE_CREATE_TRANMIT_REQUEST_COULD_NOT_FIND_NETWORK_ID;
  }

  common_copy_char_array(payload.data, (frame->data + XBEE_TRANSMIT_REQUEST_FRAME_HEADER_SIZE), payload.size);
  frame->data[XBEE_TRANSMIT_REQUEST_FRAME_HEADER_SIZE + payload.size]
      = xbee_calculate_checksum(&formattedMsg->apiFrameFormat, length);
  frame->size = XBEE_TRANSMIT_REQUEST_FRAME_HEADER_SIZE + payload.size + 1;

  return XBEE_CREATE_TRANMIT_REQUEST_SUCCESSFUL;
}
