//
//  trim.c
//  string-c
//
//  Created by Cator Vee on 10/24/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "trim.h"

string_t strtrim(string_t *str, unsigned flags, string_t chars)
{
  string_t s = *str;
  size_t len = strlen(s);
  
  if (flags & STR_TRIM_FLAGS_LEFT) {
    size_t pos = strspn(s, chars);
    if (pos < len) {
      len -= pos;
      memmove(s, s + pos, len + 1);
    }
  }
  
  if (flags & STR_TRIM_FLAGS_RIGHT) {
    string_t p = s + len - 1;
    while (p != s && strchr(chars, *p) != NULL) {
      p--;
    }
    *(p + 1) = '\0';
  }
  
  return s;
}