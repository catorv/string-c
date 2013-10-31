//
//  html.h
//  string-c
//
//  Created by Cator Vee on 10/30/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_html_h
#define string_c_html_h

#include "string.h"

/**
 * 从字符串中去除 HTML 标记
 *
 * @param str 输入字符串
 * @return 返回处理后的字符串
 */
string_t striptags(string_t *str);

/**
 * HTML特殊字符编码
 * 
 * @param str 输入字符串
 * @param skip_quotes 是否跳过单引号和双引号
 * @return 返回编码后的字符串
 */
string_t copy_htmlencode(const string_t str, bool skip_quotes);

/**
 * HTML特殊字符解码
 *
 * @param str 输入字符串（也是输出字符串）
 * @return 返回解码后的字符串
 */
string_t htmldecode(string_t *str);

#endif
