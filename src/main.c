//
// Created by ajinkya on 5/11/19.
// main file application starts here
//

#include <stdio.h>
#include "xbee.h"
#include "device.h"

int main() {

  device_init_config deviceInitConfig = {
      .baudrate = 9600
  };
  device_init_status deviceInitStatus = device_init(deviceInitConfig);
  if (deviceInitStatus != DEVICE_INIT_SUCCESSFUL) {
    DEVICE_LOG_ERROR("Device Init Failed with code : %d", deviceInitStatus);
    return -1;
  }

  xbee_init_config xbeeInitConfig = {
      .options = XBEE_API_OPTIONS_DISABLE_RETRIES,
      .broadcastRadius = 0,
      .apiFrameFormat = XBEE_API_FRAME_FORMAT_WITH_ESCAPE_CHARACTERS};
  xbee_init_status xbeeInitStatus = xbee_init(xbeeInitConfig);
  if (xbeeInitStatus != XBEE_INIT_SUCCESSFUL) {
    DEVICE_LOG_ERROR("Xbee Init Failed with code : %d", xbeeInitStatus);
  }

  device_sleep_ms(100);

  xbee_mac_id_network_addr_pair xbee = {
      .destinationNetworkAddr = {0xFF, 0xFE},
      .destinationMacID = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xA2, 0x09, 0xA3}
  };

  int deviceIndex;
  xbee_add_network_addr_mac_id_pair(xbee, &deviceIndex);

  COMMON_CREATE_STRING(frame, 100);
  COMMON_CREATE_STRING(payload, 150);
  common_string_copy_from_null_terminated_string(&payload, "Hello World!!!");

  unsigned char frameId;

  device_status deviceStatus;
  while (1) {
    deviceStatus = device_get_status();
    if (deviceStatus != DEVICE_STATUS_OK) {
      DEVICE_LOG_ERROR("Device Failed with code %d", deviceStatus);
      return -1;
    }

    xbee_create_transmit_request_status createTransmitRequestStatus
        = xbee_create_transmit_request(xbee.destinationMacID, payload, &frame, &frameId);

    if (createTransmitRequestStatus != XBEE_CREATE_TRANMIT_REQUEST_SUCCESSFUL) {
      DEVICE_LOG_ERROR("Could not create transmit request", deviceStatus);
      return -1;
    }

    device_serial_send(frame);
    device_sleep_ms(1000);

  }

  return 0;
}
