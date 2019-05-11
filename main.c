#include <stdio.h>
#include "include/xbee.h"
#include "device.h"

int main() {

  device_init_status deviceInitStatus = device_init(9600);
  if(deviceInitStatus !=DEVICE_INIT_SUCCESSFUL)
  {
    device_print_debug("Device Init Failed with code : %d", deviceInitStatus);
    return -1;
  }

  xbee_init_config xbeeInitConfig =
      {.options = XBEE_API_OPTIONS_DISABLE_RETRIES,
       .broadcastRadius = 0,
       .apiFrameFormat = XBEE_API_OPTIONS_DISABLE_RETRIES};

  xbee_init_status xbeeInitStatus = xbee_init(xbeeInitConfig);
  if(xbeeInitStatus != XBEE_INIT_SUCCESSFUL)
  {
    device_print_debug("Xbee Init Failed with code : %d", xbeeInitStatus);
  }

  device_sleep_ms(100);

  xbee_mac_id_network_addr_pair device = {
      .destinationNetworkAddr = {0xFF, 0xFE},
      .destinationMacID = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xA2, 0x09, 0xA3}
  };
  int deviceIndex;
  xbee_add_network_addr_from_mac_pair(device, &deviceIndex);

  unsigned char frame[500];
  int size;
  
  device_status deviceStatus;
  /* Weird but valid syntax warning. Device status is stored in deviceStatus and then
   * checked if it is DEVICE_STATUS_OK */
  while(1)
  {
    deviceStatus = device_get_status();
    if(deviceStatus != DEVICE_STATUS_OK)
    {
      device_print_debug("Device Failed with code %d", deviceStatus);
      return -1;
    }

    xbee_create_transmit_request_status createTransmitRequestStatus
      = xbee_create_transmit_request(device.destinationMacID, "Hello World", frame);

    if(createTransmitRequestStatus != XBEE_CREATE_TRANMIT_REQUEST_SUCCESSFUL)
    {
      device_print_debug("Could not create transmit request", deviceStatus);
      return -1;
    }

    device_serial_send(frame, size);

  }

  return 0;
