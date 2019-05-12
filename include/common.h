//
// Created by ajinkya on 5/11/19.
// Common utility functions
//


#ifndef SWARM_COMMON_H
#define SWARM_COMMON_H
#include <stdbool.h>

/// Used to supress unused warning for intentionally unused variables
#define UNUSED(x) (void)(x)

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

#endif //SWARM_COMMON_H
