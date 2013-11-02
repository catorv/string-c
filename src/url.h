//
//  url.h
//  string-c
//
//  Created by Cator Vee on 11/1/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#ifndef string_c_url_h
#define string_c_url_h

#include "string.h"

typedef struct urlcomponents_t {
  string_t scheme;      // 协议名称
  string_t user;        // 用户名
  string_t password;    // 密码
  string_t host;        // 主机名或域名
  unsigned short port;  // 端口号
  string_t path;        // 路径
  string_t query;       // 在问号 ? 之后的部分
  string_t fragment;    // 在散列符号 # 之后的部分
} urlcompoments_t;

/**
 * 此函数便于将字符串编码并将其用于 URL 的请求部分，同时它还便于将变量传递给下一页。
 *
 * @param str 要编码的字符串
 * @return 返回字符串，此字符串中除了 -_. 之外的所有非字母数字字符都将被替换成百分号（%）后跟两位十六进制数，空格则编码为加号（+）。
 */
string_t copy_urlencode(const string_t str);

/**
 * 解码给出的已编码字符串中的任何 %##。 加号（'+'）被解码成一个空格字符。
 *
 * @param str 要解码的字符串
 * @return 返回解码后的字符串
 */
string_t urldecode(string_t *str);

/**
 * 解析URL字符串并返回URL的各个部分。
 *
 * @param str 要解析的URL
 * @return 如果解析失败，返回NULL，否则返回一个`urlcompoments_t`指针
 */
urlcompoments_t *copy_urlcompoments(string_t str);

/**
 * 释放`urlcompoments_t`变量占用的内存
 * 
 * @param components 要释放的`urlcompoments_t`变量
 */
void free_urlcomponents(urlcompoments_t *components);

#endif
