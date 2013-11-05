//
//  base64.c
//  string-c
//
//  Created by Cator Vee on 11/5/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "base64.h"

string_t copy_base64encode(const string_t str)
{
  size_t len = strlen(str);
  size_t nlen = sizeof(char) * ((len + 2) / 3 * 4);
  
  const string_t result = (string_t)malloc(nlen + sizeof(char));
  
  static string_t table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
  
  int32_t i;
  for (i=0; i < len; i += 3) {
    int32_t value = 0;
    int32_t j;
    for (j = i; j < (i + 3); j++) {
      value <<= 8;
      
      if (j < len) {
        value |= (0xFF & str[j]);
      }
    }
    
    int32_t index = (i / 3) * 4;
    result[index + 0] = table[(value >> 18) & 0x3F];
    result[index + 1] = table[(value >> 12) & 0x3F];
    result[index + 2] = (i + 1) < len ? table[(value >> 6)  & 0x3F] : '=';
    result[index + 3] = (i + 2) < len ? table[(value >> 0)  & 0x3F] : '=';
  }
  
  result[nlen] = '\0';
  
  return result;
}

string_t base64decode(string_t *str)
{
  static uint8_t table[256];
  static bool table_inited = false;
  if (!table_inited) {
    int i;
    for (i = 0; i < 256; ++i) {
      table[i] = (uint8_t)0x80;
    }
    for (i = 'A'; i <= 'Z'; ++i) {
      table[i] = 0 + (i - 'A');
    }
    for (i = 'a'; i <= 'z'; ++i) {
      table[i] = 26 + (i - 'a');
    }
    for (i = '0'; i <= '9'; ++i) {
      table[i] = 52 + (i - '0');
    }
    table[(uint8_t)'+'] = 62;
    table[(uint8_t)'/'] = 63;
    table[(uint8_t)'='] = 0;
    table_inited = true;
  }
  
  const string_t input = *str;
  size_t len = strlen(input);
  
  
  int k = 0;
  int m, n;
  for (m = 0; m < len; m += 4) {
    uint8_t c[4];
    for (n = 0; n < 4; ++n) {
      c[n] = table[(uint8_t)input[n + m]];
      if ((c[n] & 0x80) != 0) {
        c[n] = 0;
      }
    }
    
    input[k++] = (c[0] << 2) | (c[1] >> 4);
    input[k++] = (c[1] << 4) | (c[2] >> 2);
    input[k++] = (c[2] << 6) | c[3];
  }
  input[k] = '\0';
  
  return *str;
}
