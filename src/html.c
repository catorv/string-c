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
  const size_t len = strlen(str);
  const string_t se = str + len;
  register string_t s = str;
  register string_t p;
  
  string_t result = (string_t)malloc(sizeof(char) * (len * 6 + 1));
  
  s = str;
  p = result;
  while (s < se) {
    switch (*s) {
      case '&':
        memcpy(p, "&amp;", 5);
        p += 5;
        break;
        
      case '"':
      case '\'':
        if (skip_quotes) {
          *p++ = *s;
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
        *p++ = *s;
        break;
    }
    s++;
  }
  
  *p = '\0';
  
  return result;
}

typedef struct htmlentity_t {
  string_t entity;
  size_t length;
  unsigned char c1;
  unsigned char c2;
} htmlentity_t;

string_t htmldecode(string_t *str)
{
  string_t s = *str;
  string_t p = s;
  
  htmlentity_t htmlentities[] = {
    {"&amp;",  5, 0, '&'},
    {"&quot;", 6, 0, '"'},
    {"&apos;", 6, 0, '\''},
    {"&lt;",   4, 0, '<'},
    {"&gt;",   4, 0, '>'}
  };
  int htmlentity_count = sizeof(htmlentities) / sizeof(htmlentity_t);
  
  int i;
  htmlentity_t entity;
  
  while (*s != '\0') {
    if (*s == '&') {
      for (i = 0; i < htmlentity_count; i++) {
        entity = htmlentities[i];
        if (strncasecmp(s, entity.entity, entity.length) == 0) {
          if (entity.c1 != 0) {
            *p++ = entity.c1;
          }
          *p++ = entity.c2;
          s += entity.length;
          break;
        }
      }
      if (i < htmlentity_count) {
        continue;
      }
    }
    *p++ = *s++;
  }
  
  *p = '\0';
  
  return *str;
}