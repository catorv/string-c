//
//  html.c
//  string-c
//
//  Created by Cator Vee on 10/30/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "html.h"


string_t striptags(string_t *str)
{
  string_t s = *str;
  string_t p = s;
  
  bool ouside = true;
  
  while (*p != '\0') {
    if (ouside && *p == '<') {
      ouside = false;
    } else if (!ouside && *p == '>') {
      ouside = true;
      p++;
      continue;
    }
    
    if (ouside && s != p) {
      *s = *p;
      s++;
      p++;
    } else {
      p++;
    }
  }
  
  *s = '\0';
  
  return *str;
}

string_t copy_htmlencode(const string_t str, bool skip_quotes)
{
  string_t result;
  size_t len = 0;
  string_t s = str;
  string_t p;
  
  while (*s != '\0') {
    switch (*s) {
      case '&':
        len += 5;
        break;
        
      case '"':
      case '\'':
        len += skip_quotes ? 1 : 6;
        break;
        
      case '<':
      case '>':
        len += 4;
        break;
        
      default:
        len++;
    }
    s++;
  }
  
  result = (string_t)malloc(sizeof(char) * (len + 1));
  
  s = str;
  p = result;
  while (*s != '\0') {
    switch (*s) {
      case '&':
        memcpy(p, "&amp;", 5);
        p += 5;
        break;
        
      case '"':
      case '\'':
        if (skip_quotes) {
          *p = *s;
          p++;
        } else {
          memcpy(p, *s == '"' ? "&quot;" : "&apos;", 6);
          p += 6;
        }
        break;
        
      case '<':
      case '>':
        memcpy(p, *s == '<' ? "&lt;" : "&gt;", 4);
        p += 4;
        break;
       
      default:
        *p = *s;
        p++;
        break;
    }
    s++;
  }
  
  *p = '\0';
  
  return result;
}

string_t htmldecode(string_t *str)
{
  string_t s = *str;
  string_t p = s;
  
  while (*s != '\0') {
    if (*s == '&') {
      if (strncasecmp(s, "&amp;", 5) == 0) {
        *p = '&';
        s += 5;
        p++;
        continue;
      } else if (strncasecmp(s, "&quot;", 6) == 0) {
        *p = '"';
        s += 6;
        p++;
        continue;
      } else if (strncasecmp(s, "&apos;", 6) == 0) {
        *p = '\'';
        s += 6;
        p++;
        continue;
      } else if (strncasecmp(s, "&lt;", 4) == 0) {
        *p = '<';
        s += 4;
        p++;
        continue;
      } else if (strncasecmp(s, "&gt;", 4) == 0) {
        *p = '>';
        s += 4;
        p++;
        continue;
      }
    }
    
    *p = *s;
    s++;
    p++;
  }
  
  *p = '\0';
  
  return *str;
}