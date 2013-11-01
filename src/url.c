//
//  url.c
//  string-c
//
//  Created by Cator Vee on 11/1/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "url.h"

string_t copy_urlencode(const string_t str)
{
  if (str == NULL) {
    return NULL;
  }

  register char c;
  register size_t i = 0;
  size_t len = strlen(str);
	string_t result = (string_t)malloc(sizeof(char) * (len * 3 + 1));
  register string_t p = result;
  
  while ((c = *(str + i++)) != 0) {
		if (c == ' ') {
      *p++ = '+';
		} else if (!isalnum(c) && strchr("_-.", c) == NULL) {
      sprintf(p, "%%%02X", (unsigned char)c);
			p += 3;
		} else {
			*p++ = c;
		}
	}
  
	*p = '\0';
  
	return result;
}

static char hexdec(char c)
{
  if (c>='0' && c<='9') return c - '0';
  if (c>='a' && c<='z') return c - 'a' + 10;
  if (c>='A' && c<='Z') return c - 'A' + 10;
  
  return 0;
}

string_t urldecode(string_t *str)
{
  register string_t s = *str;
  register string_t p = s;
  string_t end = *str + strlen(*str) - 1;
  
	while (*s != 0) {
		if (*s == '+') {
			*p = ' ';
		} else if (*s == '%' && (end - s) >= 2 && isxdigit((int) *(s + 1))
                                           && isxdigit((int) *(s + 2))) {
      *p = hexdec(*(s + 1)) * 16 + hexdec(*(s + 2));
			s += 2;
		} else {
			*p = *s;
		}
		s++;
		p++;
	}
  
	*p = 0;

  return *str;
}