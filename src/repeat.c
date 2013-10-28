//
//  repeat.c
//  string-c
//
//  Created by Cator Vee on 10/25/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "repeat.h"

string_t copy_repeat(string_t input, size_t multiplier)
{
  string_t result;
  string_t p;
  size_t i;
  
  size_t len = strlen(input);
  
  result = (string_t)malloc(sizeof(char) * (len * multiplier + 1));
  
  p = result;
  for (i = 0; i < multiplier; i++) {
    memcpy(p, input, len);
    p += len;
  }
  *p = '\0';
  
  return result;
}

string_t copy_strpad(string_t input, size_t pad_length, string_t pad_string, unsigned pad_type)
{
  size_t input_len = strlen(input);
  size_t pad_str_len = strlen(pad_string);
  size_t left = 0;
  size_t right;
  size_t i;
  
  if (pad_length <= input_len) {
    return copy_str(input);
  }
  
  string_t result = (string_t)malloc(sizeof(char) * (pad_length + 1));
  
  if (pad_type & STR_PAD_RIGHT) {
    left = pad_length - input_len;
    if (pad_type & STR_PAD_LEFT) {
      left /= 2;
    }
  }
  
  memcpy(result + left, input, input_len);
  
  right = left + input_len;
  for (i = 0; i < pad_length; i++) {
    if (i < left || i >= right) {
      *(result + i) = *(pad_string + (i % pad_str_len));
    } else {
      i += input_len - 1;
    }
  }
  
  *(result + pad_length) = '\0';
  
  return result;
}