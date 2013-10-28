//
//  strcase.h
//  string-c
//
//  Created by Cator Vee on 10/23/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_strcase_h
#define string_c_strcase_h

#include "string.h"

string_t strcase(string_t *str, size_t length, bool to_lower);

/**
 * 将字符串转化为小写
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以这里不允许传入字符串常量。
 * @return 返回转换后的字符串
 */
#define strtolower(str) strcase(str, 0, true)

/**
 * 将字符串转化为大写
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回转换后的字符串
 */
#define strtoupper(str) strcase(str, 0, false)

/**
 * 使一个字符串的第一个字符小写
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回转换后的字符串
 */
#define lcfirst(str) strcase(str, 1, true)

/**
 * 将字符串的首字母转换为大写
 *
 * @param str (string_t *) 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回转换后的字符串
 */
#define ucfirst(str) strcase(str, 1, false)

/**
 * 将字符串中每个单词的首字母转换为大写
 *
 * @param str 输入字符串，str本身的值会被改变，所以str必须是保存在heap上的。
 * @return 返回转换后的字符串
 */
string_t ucwords(string_t *str);

#endif
