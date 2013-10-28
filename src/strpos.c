//
//  strpos.c
//  string-c
//
//  Created by Cator Vee on 10/22/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "strpos.h"

long _strpos(const string_t haystack,const string_t needle, bool ignorecase, bool from_right)
{
  size_t hlen = strlen(haystack);
  size_t nlen = strlen(needle);
  
  if (nlen > hlen) {
    return -1;
  }
  
  int (* cmp)(const char *, const char *, size_t) = ignorecase ? strncasecmp : strncmp;
  size_t len = hlen - nlen;
  register long i = from_right ? len : 0;
  
  while (i >= 0 && i <= len) {
    if (cmp(haystack + i, needle, nlen) == 0) {
      return i;
    }
    if (from_right) {
      i--;
    } else {
      i++;
    }
  }
  
  return  -1;
}