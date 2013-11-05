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
