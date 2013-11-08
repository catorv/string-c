//
//  md5.c
//  string-c
//
//  Created by Cator Vee on 11/6/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include "md5.h"

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
   Rotation is separate from addition to prevent recomputation. */
#define FF(a, b, c, d, x, s, ac) {  (a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac);  (a) = ROTATE_LEFT ((a), (s));  (a) += (b); }
#define GG(a, b, c, d, x, s, ac) {  (a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac);  (a) = ROTATE_LEFT ((a), (s));  (a) += (b); }
#define HH(a, b, c, d, x, s, ac) {  (a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac);  (a) = ROTATE_LEFT ((a), (s));  (a) += (b); }
#define II(a, b, c, d, x, s, ac) {  (a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac);  (a) = ROTATE_LEFT ((a), (s));  (a) += (b); }

/* Encodes input (uint32_t) into output (unsigned char). Assumes len is
   a multiple of 4. */
static void _encode(unsigned char *output, uint32_t *input, size_t len)
{
  size_t i, j;
  
  for(i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* Decodes input (unsigned char) into output (uint32_t). Assumes len is
   a multiple of 4. */
static void _decode(uint32_t *output, unsigned char *input, size_t len)
{
  size_t i, j;
  
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
                (((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
  }
}

/* MD5 basic transformation. Transforms state based on block. */
static void md5transform(uint32_t state[4], unsigned char block[64])
{
  uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];
  
  _decode(x, block, 64);
  
  /* Round 1 */
  FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
  
  /* Round 2 */
  GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG(d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
  
  /* Round 3 */
  HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH(b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
  
  /* Round 4 */
  II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
  
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  
  /* Zeroize sensitive information. */
  memset((unsigned char *)x, 0, sizeof(x));
}



/* MD5 initialization. Begins an MD5 operation, writing a new context. */
void md5init(md5context_t *context)
{
  /* 将当前的有效信息的长度设成0,这个很简单,还没有有效信息,长度当然是0了 */
  context->count[0] = context->count[1] = 0;
  
  /* Load magic initialization constants. */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
   operation, processing another message block, and updating the
   context. */
void md5update(md5context_t *context, string_t input, size_t length)
{
  unsigned int i, index, partLen;
  
  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);
  
  /* Update number of bits *//*更新已有信息的bits长度*/
  if ((context->count[0] += ((uint32_t)length << 3)) < ((uint32_t)length << 3)) {
    context->count[1]++;
  }
  context->count[1] += ((uint32_t)length >> 29);
  
  /*计算已有的字节数长度还差多少字节可以 凑成64的整倍数*/
  partLen = 64 - index;
  
  /* Transform as many times as possible. */
  if (length >= partLen) {
    /* 用当前输入的内容把context->buffer的内容补足512bits */
    memcpy((unsigned char *)&context->buffer[index],
           (unsigned char *)input,
           partLen);
    /* 用基本函数对填充满的512bits（已经保存到context->buffer中）
       做一次转换，转换结果保存到context->state中 */
    md5transform(context->state, context->buffer);
    
    /*
     对当前输入的剩余字节做转换（如果剩余的字节<在输入的input缓冲区中>大于512bits的话 ），
     转换结果保存到context->state中
     */
    for(i = partLen; i + 63 < length; i += 64 ) {
      md5transform(context->state, (unsigned char *)&input[i]);
    }
    
    index = 0;
  } else {
    i = 0;
  }
  
  /* Buffer remaining input */
  memcpy((unsigned char *)&context->buffer[index],
         (unsigned char *)&input[i],
         length - i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
   the message digest and zeroizing the context. */
void md5final(unsigned char digest[16], md5context_t *context)
{
  unsigned char bits[8];
  unsigned int index, padLen;
  
  /* Save number of bits */
  /*将要被转换的信息(所有的)的bits长度拷贝到bits中*/
  _encode(bits, context->count, 8);
  
  /* Pad out to 56 mod 64. */
  /* 计算所有的bits长度的字节数的模64, 64bytes=512bits*/
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  /*计算需要填充的字节数，padLen的取值范围在1-64之间*/
  padLen = (index < 56) ? (56 - index) : (120 - index);
  /*这一次函数调用绝对不会再导致MD5Transform的被调用，因为这一次不会填满512bits*/
  md5update(context, (string_t)PADDING, padLen);
  
  /* Append length (before padding) */
  md5update(context, (string_t)bits, 8);
  
  /* Store state in digest */
  _encode(digest, context->state, 16);
  
  /* Zeroize sensitive information. */
  memset((unsigned char *)context, 0, sizeof(*context));
}

string_t copy_md5(const string_t input)
{
  static md5context_t md5;
  bool inited = false;
  
  if (!inited) {
    md5init(&md5);
    inited = true;
  }
  
  unsigned char decrypt[16];
  const size_t len = strlen(input);
  const string_t result = (string_t)malloc(sizeof(char) * (32 + 1));
  
  md5update(&md5, input, len);
  md5final(decrypt, &md5);
  
  int i;
  for(i = 0; i < 16; i++) {
    sprintf(result + i * 2, "%02x", decrypt[i]);
  }
  
  return result;
}