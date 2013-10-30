//
//  replace.h
//  string-c
//
//  Created by Cator Vee on 10/28/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_replace_h
#define string_c_replace_h

#include "string.h"

/**
 * 转换指定字符
 *
 * @param str 待转换的字符串
 * @param from 字符串中与将要被转换的目的字符`to`相对应的源字符
 * @param to 字符串中与将要被转换的字符`from`相对应的目的字符
 * @return 返回转换后的字符串
 */
string_t strtr(string_t *str, const string_t from, const string_t to);

/**
 * 子字符串替换
 *
 * @param search 查找的目标值
 * @param replace `search`的替换值
 * @param subject 执行替换的数组或者字符串
 * @param ignorecase 是否忽略大小写
 * @return 该函数返回替换后的数组或者字符串
 */
string_t copy_strreplace(const string_t search, const string_t replace, const string_t subject, const bool ignorecase);

/**
 * 子字符串替换
 *
 * @param search 查找的目标值
 * @param replace `search`的替换值
 * @param subject 执行替换的数组或者字符串
 * @return 该函数返回替换后的数组或者字符串
 */
#define copy_replace(search, replace, subject) copy_strreplace(search, replace, subject, false)

/**
 * 子字符串替换(忽略大小写)
 *
 * @param search 查找的目标值
 * @param replace `search`的替换值
 * @param subject 执行替换的数组或者字符串
 * @return 该函数返回替换后的数组或者字符串
 */
#define copy_ireplace(search, replace, subject) copy_strreplace(search, replace, subject, true)

#endif
