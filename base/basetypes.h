#ifndef _H_BASETYPES_H_
#define _H_BASETYPES_H_
enum boolean
{
    FALSE = 0,
    TRUE  = 1
};

typedef enum boolean BOOLEAN;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
#define NULL  (0)
void memcopy(uint8_t * dst, uint8_t * src, uint32_t len);
void memset( uint8_t * pSrc, uint8_t val, uint32_t size );
BOOLEAN memcompare( uint8_t * pSrc, uint8_t val, uint32_t size );
#endif
