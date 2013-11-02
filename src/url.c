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
  register char c;
  register size_t i = 0;
  size_t len = strlen(str);
  string_t result = (string_t)malloc(sizeof(char) * (len * 3 + 1));
  register string_t p = result;
  
  while ((c = *(str + i++)) != '\0') {
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
  string_t se = *str + strlen(*str) - 1;
  
  while (s <= se) {
    if (*s == '+') {
      *p = ' ';
    } else if (*s == '%' && (se - s) >= 2 && isxdigit((int) *(s + 1))
                                          && isxdigit((int) *(s + 2))) {
      *p = hexdec(*(s + 1)) * 16 + hexdec(*(s + 2));
      s += 2;
    } else {
      *p = *s;
    }
    s++;
    p++;
  }
  
  *p = '\0';

  return *str;
}

/* 参考PHP parse_url() 源代码 */
urlcompoments_t *copy_urlcompoments(string_t str)
{
  char port_buf[6];
  urlcompoments_t *result = calloc(1, sizeof(urlcompoments_t));
  char const *s, *e, *p, *pp, *ue;
  size_t len = strlen(str);
  
  s = str;
  ue = s + len;
  
  /* parse scheme */
  if ((e = memchr(s, ':', len)) && (e - s)) {
    /* validate scheme */
    p = s;
    while (p < e) {
      /* scheme = 1*[ lowalpha | digit | "+" | "-" | "." ] */
      if (!isalpha(*p) && !isdigit(*p) && *p != '+' && *p != '.' && *p != '-') {
        if (e + 1 < ue) {
          goto parse_port;
        } else {
          goto just_path;
        }
      }
      p++;
    }
    
    if (*(e + 1) == '\0') { /* only scheme is available */
      result->scheme = strndup(s, (e - s));
      goto end;
    }
    
    /*
     * certain schemas like mailto: and zlib: may not have any / after them
     * this check ensures we support those.
     */
    if (*(e+1) != '/') {
      /* check if the data we get is a port this allows us to
       * correctly parse things like a.com:80
       */
      p = e + 1;
      while (isdigit(*p)) {
        p++;
      }
      
      if ((*p == '\0' || *p == '/') && (p - e) < 7) {
        goto parse_port;
      }
      
      result->scheme = strndup(s, (e-s));
      
      len -= ++e - s;
      s = e;
      goto just_path;
    } else {
      result->scheme = strndup(s, (e-s));
      
      if (*(e+2) == '/') {
        s = e + 3;
        if (!strncasecmp("file", result->scheme, sizeof("file"))) {
          if (*(e + 3) == '/') {
            /* support windows drive letters as in:
             file:///c:/somedir/file.txt
             */
            if (*(e + 5) == ':') {
              s = e + 4;
            }
            goto nohost;
          }
        }
      } else {
        if (!strncasecmp("file", result->scheme, sizeof("file"))) {
          s = e + 1;
          goto nohost;
        } else {
          len -= ++e - s;
          s = e;
          goto just_path;
        }
      }
    }
  } else if (e) { /* no scheme; starts with colon: look for port */
  parse_port:
    p = e + 1;
    pp = p;
    
    while (pp-p < 6 && isdigit(*pp)) {
      pp++;
    }
    
    if (pp - p > 0 && pp - p < 6 && (*pp == '/' || *pp == '\0')) {
      long port;
      memcpy(port_buf, p, (pp - p));
      port_buf[pp - p] = '\0';
      port = strtol(port_buf, NULL, 10);
      if (port > 0 && port <= 65535) {
        result->port = (unsigned short) port;
      } else {
        free(result->scheme);
        free(result);
        return NULL;
      }
    } else if (p == pp && *pp == '\0') {
      free(result->scheme);
      free(result);
      return NULL;
    } else {
      goto just_path;
    }
  } else {
  just_path:
    ue = s + len;
    goto nohost;
  }
  
  e = ue;
  
  if (!(p = memchr(s, '/', (ue - s)))) {
    char *query, *fragment;
    
    query = memchr(s, '?', (ue - s));
    fragment = memchr(s, '#', (ue - s));
    
    if (query && fragment) {
      if (query > fragment) {
        p = e = fragment;
      } else {
        p = e = query;
      }
    } else if (query) {
      p = e = query;
    } else if (fragment) {
      p = e = fragment;
    }
  } else {
    e = p;
  }
  
  /* check for login and password */
  if ((p = strrchr(s, '@'))) {
    if ((pp = memchr(s, ':', (p-s)))) {
      if ((pp-s) > 0) {
        result->user = strndup(s, (pp-s));
      }
      
      pp++;
      if (p-pp > 0) {
        result->password = strndup(pp, (p-pp));
      }
    } else {
      result->user = strndup(s, (p-s));
    }
    
    s = p + 1;
  }
  
  /* check for port */
  if (*s == '[' && *(e-1) == ']') {
    /* Short circuit portscan,
     we're dealing with an
     IPv6 embedded address */
    p = s;
  } else {
    /* memrchr is a GNU specific extension
     Emulate for wide compatability */
    for(p = e; *p != ':' && p >= s; p--);
  }
  
  if (p >= s && *p == ':') {
    if (!result->port) {
      p++;
      if (e-p > 5) { /* port cannot be longer then 5 characters */
        free(result->scheme);
        free(result->user);
        free(result->password);
        free(result);
        return NULL;
      } else if (e - p > 0) {
        long port;
        memcpy(port_buf, p, (e - p));
        port_buf[e - p] = '\0';
        port = strtol(port_buf, NULL, 10);
        if (port > 0 && port <= 65535) {
          result->port = (unsigned short)port;
        } else {
          free(result->scheme);
          free(result->user);
          free(result->password);
          free(result);
          return NULL;
        }
      }
      p--;
    }
  } else {
    p = e;
  }
  
  /* check if we have a valid host, if we don't reject the string as url */
  if ((p-s) < 1) {
    free(result->scheme);
    free(result->user);
    free(result->password);
    free(result);
    return NULL;
  }
  
  result->host = strndup(s, (p-s));
  
  if (e == ue) {
    goto end;
  }
  
  s = e;
  
nohost:
  
  if ((p = memchr(s, '?', (ue - s)))) {
    pp = strchr(s, '#');
    
    if (pp && pp < p) {
      if (pp - s) {
        result->path = strndup(s, (pp-s));
      }
      p = pp;
      goto label_parse;
    }
    
    if (p - s) {
      result->path = strndup(s, (p-s));
    }
    
    if (pp) {
      if (pp - ++p) {
        result->query = strndup(p, (pp-p));
      }
      p = pp;
      goto label_parse;
    } else if (++p - ue) {
      result->query = strndup(p, (ue-p));
    }
  } else if ((p = memchr(s, '#', (ue - s)))) {
    if (p - s) {
      result->path = strndup(s, (p-s));
    }
    
  label_parse:
    p++;
    
    if (ue - p) {
      result->fragment = strndup(p, (ue-p));
    }
  } else {
    result->path = strndup(s, (ue-s));
  }
end:
  if (result->port == 0 && result->scheme) {
    len = strlen(result->scheme);
    if (len == 4 && strncasecmp(result->scheme, "http", 4) == 0) {
      result->port = 80;
    } else if (len == 5 && strncasecmp(result->scheme, "https", 5) == 0) {
      result->port = 443;
    } else if (len == 3 && strncasecmp(result->scheme, "ftp", 3) == 0) {
      result->port = 21;
    }
  }
  return result;
}

void free_urlcomponents(urlcompoments_t *components)
{
  if (components) {
    if (components->scheme) {
      free(components->scheme);
    }
    if (components->user) {
      free(components->user);
    }
    if (components->password) {
      free(components->password);
    }
    if (components->host) {
      free(components->host);
    }
    if (components->path) {
      free(components->path);
    }
    if (components->query) {
      free(components->query);
    }
    if (components->fragment) {
      free(components->fragment);
    }
    free(components);
  }
}