//
//  repeat.h
//  string-c
//
//  Created by Cator Vee on 10/25/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_repeat_h
#define string_c_repeat_h

#include "string.h"

#define STR_PAD_LEFT  0x01
#define STR_PAD_RIGHT 0x02
#define STR_PAD_BOTH  0x03

/**
 * 重复一个字符串
 *
 * @param input 待操作的字符串
 * @param multiplier `input`被重复的次数
 * @return 返回`input`重复`multiplier`次后的结果
 */
string_t copy_repeat(string_t input, size_t multiplier);

/**
 * 使用另一个字符串填充字符串为指定长度
 *
 * @param input 输入字符串
 * @param pad_length 如果`pad_length`的值是负数，小于或者等于输入字符串的长度，不会发生任何填充
 * @param pad_string 如果填充字符的长度不能被`pad_string`整除，那么`pad_string`可能会被缩短
 * @param pad_type 填充对齐的方式，可能值为 STR_PAD_RIGHT，STR_PAD_LEFT 或 STR_PAD_BOTH
 * @return 返回填充后的字符串
 */
string_t copy_strpad(string_t input, size_t pad_length, string_t pad_string, unsigned pad_type);

#endif
