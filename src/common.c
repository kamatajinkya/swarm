//
// Created by ajinkya on 5/11/19.
//

#include "common.h"
#include "string.h"

bool common_compare_char_arrays(const unsigned char* arr1, const unsigned char* arr2, int size)
{
  while(size-- > 0) {
    if(arr1[size] != arr2[size])
      return false;
  }
  return true;
}

bool common_set_char_array_to_zero(unsigned char* array, int size)
{
  for(int i = 0; i < size; i++)
  {
    array[i] = 0;
  }
}

bool common_copy_char_array(const unsigned char* source, unsigned char* destination, int size)
{
  for(int i = 0; i < size; i++)
  {
    destination[i] = source[i];
  }
}

bool common_string_copy_from_null_terminated_string(common_string* string,
                                                    const char* nullTerminatedString)
{
  string->size = 0;
  while(nullTerminatedString[string->size] != '\0')
  {
    if(string->size >= string->maxSize)
      return false;

    string->data[string->size] = (unsigned char)nullTerminatedString[string->size];
    string->size++;
  }

  return true;
}