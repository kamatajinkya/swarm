//
// Created by ajinkya on 5/11/19.
//

#ifndef SWARM_DEVICE_H
#define SWARM_DEVICE_H

typedef enum{
  DEVICE_INIT_WRONG_BAUDRATE = -1,
  DEVICE_INIT_SUCCESSFUL = 1
}device_init_status;
/// Initializes device ei configures pins, setup uart etc returns status
/// \param[in] baudrate Baudrate in numbers for example 9600, 115200.
device_init_status device_init(unsigned long baudrate);

/// Halts thread/process for a few milliseconds
/// \param[in] timeInMilliseconds time for which process should halt
void device_sleep_ms(unsigned long timeInMilliseconds);

typedef enum{
  DEVICE_STATUS_OK = 1,
  DEVICE_STATUS_NOT_OK = -1
}device_status;
/// Returns the status of device
device_status device_get_status();

typedef enum{
  DEVICE_LOG_LEVEL_ERROR = 1,
  DEVICE_LOG_LEVEL_INFO = 2,
}device_log_level;
/// Prints debug statement to console. Do not use this function use the macros DEVICE_LOG_ERROR()
/// or DEVICE_LOG_INFO()
/// \param[in] format message to be printed in printf like format
void device_print_debug(device_log_level level ,const char* format, ...);
#define DEVICE_LOG_ERROR(x) device_print_debug(x);

#endif //SWARM_DEVICE_H
