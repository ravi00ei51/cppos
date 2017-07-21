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
void * memcpy(void * dst, void const * src, uint32_t len);
#endif
