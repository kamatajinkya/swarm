//
// Created by ajinkya on 5/11/19.
// Common utility functions
//


#ifndef SWARM_COMMON_H
#define SWARM_COMMON_H
#include <stdbool.h>

/// Used to supress unused warning for intentionally unused variables
#define COMMON_UNUSED(x) (void)(x)

/// Compares char arrays. Returns true if same false different
/// \param[IN] arr1 First array
/// \param[IN] arr2 Second array
/// \param[IN] size Size of both the arrays
bool common_compare_char_arrays(const unsigned char* arr1, const unsigned char* arr2, int size);

/// Writes zeros to array
/// \param[OUT] array First array
/// \param[IN] size Size of both the arrays
bool common_set_char_array_to_zero(unsigned char* array, int size);

/// Copies char array
/// \param[IN] source First array
/// \param[IN] destination Second array
/// \param[IN] size Size of both the arrays
bool common_copy_char_array(const unsigned char* source, unsigned char* destination, int size);

typedef struct{
  int size;
  const int maxSize;
  unsigned char* const data;
}common_string;
/// Creates a string with name NAME and buffer max size of MAX_SIZE
/// Also creates a buffer with  name NAMEbuffer to store actual string data
/// e.g. COMMON_CREATE_STRING(example, 100) will create a string named example
///      and unsigned char array named exampleBuffer of size 100.
#define COMMON_CREATE_STRING(NAME, MAX_SIZE) \
  unsigned char NAME##Buffer[MAX_SIZE]; \
  common_string NAME = {      \
      .maxSize = MAX_SIZE,    \
      .data = NAME##Buffer    \
  }

/// Copies value from null terminated string to common_string.
/// Returns false if copy could not be completed
/// \param[out] string Destination of copy
/// \param[in] nullTerminatedString String to be copies
bool common_string_copy_from_null_terminated_string(common_string* string,
                    const char* nullTerminatedString);


#endif //SWARM_COMMON_H
