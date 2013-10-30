//
//  replace.c
//  string-c
//
//  Created by Cator Vee on 10/28/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "repeat.h"

string_t strtr(string_t *str, const string_t from, const string_t to)
{
  string_t s = *str;
  
  while (*s != '\0') {
    string_t p = strchr(from, *s);
    if (p != NULL) {
      *s = *(to + (p - from));
    }
    s++;
  }
  
  return *str;
}

string_t copy_strreplace(const string_t search, const string_t replace, const string_t subject, const bool ignorecase)
{
  size_t len_subject = strlen(subject);
  size_t len_search = strlen(search);
  size_t len_replace = strlen(replace);
  
  size_t count = substr_count(subject, search);
  
  size_t len = len_subject - len_search * count + len_replace + count;
  
  string_t result = (string_t)malloc(sizeof(char) * (len + 1));
  
  size_t i = 0;
  size_t c = 0;
  
  int (* cmp)(const char *, const char *, size_t) = ignorecase ? strncasecmp : strncmp;
  while (i <= len_subject) {
    if (cmp(subject + i, search, len_search) == 0) {
      memcpy(result + c, replace, len_replace);
      c += len_replace;
      i += len_search;
    } else {
      *(result + c) = *(subject + i);
      c++;
      i++;
    }
  }
  
  return result;
}

