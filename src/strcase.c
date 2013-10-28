//
//  strcase.c
//  string-c
//
//  Created by Cator Vee on 10/23/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "strcase.h"

string_t strcase(string_t *str, size_t length, bool to_lower)
{
  string_t p = *str;
  if (p != NULL) {
    int (*tocase)(int _c) = to_lower ? tolower : toupper;
    
    size_t len = strlen(p);
    if (length > 0 && length < len) {
      len = length;
    }
    
    string_t end = p + len;
    
    while (p < end) {
      *p = tocase(*p);
      p++;
    }
  }
  
  return *str;
}


string_t ucwords(string_t *str)
{
  if (str != NULL) {
    size_t len = strlen(*str);
    
    string_t p = *str;
    string_t end = p + len;
    
    while (p < end) {
      while (!isalpha(*p) && p < end) {
        p++;
      }
      if (p < end) {
        if (p == *str || isspace(*(p - 1))) {
          *p = toupper(*p);
        }
        while (isalpha(*p) && p < end) {
          p++;
        }
      }
    }
  }
  return *str;
}
