//
//  trim.h
//  string-c
//
//  Created by Cator Vee on 10/24/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_trim_h
#define string_c_trim_h

#include "string.h"

#define STR_TRIM_CHARS " \r\n\t\v"
#define STR_TRIM_FLAGS_LEFT 0x01
#define STR_TRIM_FLAGS_RIGHT 0x02


string_t strtrim(string_t *str, unsigned flags, string_t chars);

/**
 * 删除字符串开头的空白字符
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回一个删除了 str 最左边的空白字符的字符串。
 */
#define ltrim(str) strtrim(str, STR_TRIM_FLAGS_LEFT, STR_TRIM_CHARS)

/**
 * 删除字符串末端的空白字符
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回一个删除了 str 最右边的空白字符的字符串。
 */
#define rtrim(str) strtrim(str, STR_TRIM_FLAGS_RIGHT, STR_TRIM_CHARS)

/**
 * 删除字符串首尾处的空白字符
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回一个删除了 str 首尾处的空白字符的字符串。
 */
#define trim(str) strtrim(str, STR_TRIM_FLAGS_LEFT | STR_TRIM_FLAGS_RIGHT, STR_TRIM_CHARS)

#endif
