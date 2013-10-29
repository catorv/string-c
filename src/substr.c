//
//  substr.c
//  string-c
//
//  Created by Cator Vee on 10/23/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "substr.h"

string_t copy_substr(const string_t str, long start, long length)
{
  if (str == NULL) {
    return NULL;
  }
  
  size_t len = strlen(str);
  
  if (len == 0) {
    return NULL;
  }
  
  if (start < 0) {
    start += len;
  }
  
  if (start < 0) {
    start = 0;
  } else if (start >= len) {
    return NULL;
  }
  
  if (length < 0) {
    length = len + length - start;
    if (length < 0) {
      return NULL;
    }
  }
  
  if (start + length > len) {
    length = len - start;
  }
  
  string_t result = (string_t)calloc(sizeof(char), length + 1);
  
  memcpy(result, str + start, length);
  
  return result;
}

size_t substr_count(const string_t haystack, const string_t needle)
{
  size_t count = 0;
  
  long pos;
  string_t p = haystack;
  
  while ((pos = strpos(p, needle)) >= 0) {
    count++;
    p += pos + 1;
  }
  
  return count;
}
