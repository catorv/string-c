//
//  slashes.c
//  string-c
//
//  Created by Cator Vee on 11/8/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "slashes.h"

string_t copy_addslashes(const string_t str)
{
  size_t len = strlen(str);
  string_t result = (string_t)malloc(sizeof(char) * (len * 2 + 1));
  register string_t s = str;
  register string_t p = result;
  
  while (*s != '\0') {
    if (*s == '\'' || *s == '"' || *s == '\\') {
      *p++ = '\\';
    }
    *p++ = *s++;
  }

  result[p - result] = '\0';
  
  return result;
}

string_t stripslashes(string_t *str)
{
  register string_t s = *str;
  register string_t p = s;
  size_t len = strlen(s);
  const string_t se = s + len;
  
  while (s < se) {
    if (s[0] == '\\' && s[1] != '\0') {
      s++;
    } else {
      *p++ = *s++;
    }
  }
  
  *p = '\0';
  
  return *str;
}