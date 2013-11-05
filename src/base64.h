//
//  base64.h
//  string-c
//
//  Created by Cator Vee on 11/5/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_base64_h
#define string_c_base64_h

#include "string.h"

/**
 * 对字符串进行BASE64编码
 *
 * @param str 要进行编码的字符串
 * @return 返回编码后的字符串
 */
string_t copy_base64encode(const string_t str);

/**
 * 对字符串进行BASE64解码
 *
 * @param str 要进行解码的字符串
 * @return 返回解码后的字符串
 */
string_t base64decode(string_t *str);

#endif
