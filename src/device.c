#include "device.h"

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#include "common.h"

#if DEVICE_TYPE == DEVICE_TYPE_x86 || DEVICE_TYPE == DEVICE_TYPE_x86_TEST

device_init_status device_init(unsigned long baudrate)
{
  UNUSED(baudrate);
  return DEVICE_INIT_SUCCESSFUL;
}

void device_sleep_ms(unsigned long timeInMilliseconds)
{
  #warning "Using Linux. Sleep resolution is in seconds. Max sleep time is 4,294,967,295"

  unsigned timeInSeconds = (unsigned int) (timeInMilliseconds/1000);
  /* Make sure the processor sleeps*/
  if(timeInSeconds == 0)
    timeInSeconds = 1;

  sleep(timeInSeconds);
}

device_status device_get_status()
{
  return DEVICE_STATUS_OK;
}

/// Converts log level to string for human readable output
/// \param[in] level Level of log
static char* device_convert_log_level_to_string(device_log_level level)
{
  if(level == DEVICE_LOG_LEVEL_ERROR) return "ERROR";
  if(level == DEVICE_LOG_LEVEL_INFO) return "INFO";
}

void device_print_debug(device_log_level level , const char* file, int line, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  printf("%s:%d", file, line);
  printf(" [%s]: ", device_convert_log_level_to_string(level));
  vprintf(format, args);
  va_end(args);
}

void device_convert_number_to_bigendien(const char* in, long sizeInBytes, char* out)
{
  //x86 is little endien
  for (int i = 0; i < sizeInBytes; ++i) {
    out[i] = in[sizeInBytes - i];
  }
}

void device_serial_send(const char* data, int size)
{
  //Todo: Implement sending via Termial

  DEVICE_LOG_INFO("Data Stream : \r\n");
  for (int i = 0; i < size; ++i) {
    printf("%hhX ", data[i]);
  }
  printf("\r\n");
}

#endif
