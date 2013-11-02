//
//  strpos.h
//  string-c
//
//  Created by Cator Vee on 10/22/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_strpos_h
#define string_c_strpos_h

#include "string.h"

long _strpos(const string_t haystack,const string_t needle, bool ignorecase, bool from_right);

/**
 * 在字符串`haystack`中查找子字符串`needle`的索引位置
 *
 * @param haystack (const string_t) 被搜索的字符串
 * @param needle (const string_t) 查找的子字符串
 * @return 返回字符串`needle`所在的索引位置，如果未找到，返回-1.
 */
#define strpos(haystack, needle) _strpos(haystack, needle, false, false)

/**
 * 在字符串`haystack`中查找子字符串`needle`的索引位置，不区分大小写字母
 *
 * @param haystack (const string_t) 被搜索的字符串
 * @param needle (const string_t) 查找的子字符串
 * @return 返回字符串`needle`所在的索引位置，如果未找到，返回-1.
 */
#define stripos(haystack, needle) _strpos(haystack, needle, true, false)

/**
 * 在字符串`haystack`中查找子字符串`needle`的索引位置，从字符串右侧开始搜索
 *
 * @param haystack (const string_t) 被搜索的字符串
 * @param needle (const string_t) 查找的子字符串
 * @return 返回字符串`needle`所在的索引位置，如果未找到，返回-1.
 */
#define strrpos(haystack, needle) _strpos(haystack, needle, false, true)

/**
 * 在字符串`haystack`中查找子字符串`needle`的索引位置，从字符串右侧开始搜索，
 * 且不区分大小写字母
 *
 * @param haystack (const string_t) 被搜索的字符串
 * @param needle (const string_t) 查找的子字符串
 * @return 返回字符串`needle`所在的索引位置，如果未找到，返回-1.
 */
#define strripos(haystack, needle) _strpos(haystack, needle, true, true)

#endif
