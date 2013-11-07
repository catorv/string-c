//
//  md5.h
//  string-c
//
//  Created by Cator Vee on 11/6/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_md5_h
#define string_c_md5_h

#include "string.h"

/* MD5 context */
typedef struct {
  uint32_t state[4];
  uint32_t count[2];
  unsigned char buffer[64];
} md5context_t;

void md5init(md5context_t *context);
void md5update(md5context_t *context, string_t input, size_t length);
void md5final(unsigned char digest[16], md5context_t *context);

/**
 * 生成MD5字符串
 *
 * @param input 输入字符串
 * @return 返回32字节的十六进制MD5字符串
 */
string_t copy_md5(const string_t input);

#endif
