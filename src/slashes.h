//
//  slashes.h
//  string-c
//
//  Created by Cator Vee on 11/8/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_slashes_h
#define string_c_slashes_h

#include "string.h"

/**
 * 返回字符串，该字符串为了数据库查询语句等的需要在某些字符前加上了反斜线。
 * 这些字符是单引号（'）、双引号（"）、反斜线（\）
 *
 * @param str 要转义的字符串
 * @return 返回转义后的字符串
 */
string_t copy_addslashes(const string_t str);

/**
 * 去除字符串的转义反斜线
 *
 * @param str 输入字符串
 * @return 返回一个去除转义反斜线后的字符串
 */
string_t stripslashes(string_t *str);

#endif
