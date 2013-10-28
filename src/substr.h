//
//  substr.h
//  string-c
//
//  Created by Cator Vee on 10/23/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_substr_h
#define string_c_substr_h

#include "string.h"

/**
 * 返回字符串 str 由 start 和 length 参数指定的子字符串。
 *
 * @param str 输入字符串。如果 str 为 NULL 或空串，则将返回 NULL。
 * @param start 如果 start 是非负数，返回的字符串将从 str 的 start 位置开始，\
 *              从 0 开始计算。\
 *              如果 start 是负数，返回的字符串将从 str 结尾处向前数\
 *              第 start 个字符开始。\
 *              如果 str 的长度小于或等于 start，将返回 NULL。
 * @param length 如果提供了正数的 length，返回的字符串将从 start 处开始最多包括 \
 *               length 个字符（取决于 str 的长度）。\
 *               如果提供了负数的 length，那么 str 末尾处的许多字符将会被漏掉\
 *              （若 start 是负数则从字符串尾部算起）。如果 start 不在这段文本中，\
 *               那么将返回 NULL。\
 *               如果提供了值为 0，将返回空字符串（"\0"）。
 * @return 返回提取的子字符串， 或者在失败时返回 NULL。
 */
string_t copy_substr(const string_t str, long start, long length);

/**
 * 复制字符串
 *
 * @param str (const string_t) 输入字符串。如果 str 为 NULL 或空串，则将返回 NULL。
 * @return 返回复制字符串的首地址，或者在失败时返回 NULL。
 */
#define copy_str(str) copy_substr(str, 0, strlen(str))

/**
 * 计算字串出现的次数。注意 needle 区分大小写。
 *
 * @param haystack 在此字符串中进行搜索
 * @param needle 要搜索的字符串
 * @return 返回子字符串needle 在字符串 haystack 中出现的次数
 */
long substr_count(const string_t haystack, const string_t needle);

#endif
