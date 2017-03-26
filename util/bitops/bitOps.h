#ifndef _H_BITOPS_H_
#define _H_BITOPS_H_
#include "basetypes.h"

#define SET_NTH_BIT_8BIT(var,pos)            ( uint8_t ) ( var | ( uint8_t )( 1 << pos ) )
#define CLR_NTH_BIT_8BIT(var,pos)            ( uint8_t ) ( var & (~( uint8_t )( 1 << pos ) ) ) 
#define GET_NTH_BIT_8BIT(var,pos)            ( uint8_t ) ( ( uint8_t )( var >> pos ) & ( uint8_t )( 0x01  )  )

#define SET_NTH_BIT_16BIT(var,pos)            ( uint16_t ) ( var | ( uint16_t )( 1 << pos ) )
#define CLR_NTH_BIT_16BIT(var,pos)            ( uint16_t ) ( var & (~( uint16_t )( 1 << pos ) ) ) 
#define GET_NTH_BIT_16BIT(var,pos)            ( uint16_t ) ( ( uint16_t )( var >> pos ) & ( uint16_t )( 0x01  )  )

#define SET_NTH_BIT_32BIT(var,pos)            ( uint32_t ) ( var | ( uint32_t )( 1 << pos ) )
#define CLR_NTH_BIT_32BIT(var,pos)            ( uint32_t ) ( var & (~( uint32_t )( 1 << pos ) ) ) 
#define GET_NTH_BIT_32BIT(var,pos)            ( uint32_t ) ( ( uint32_t )( var >> pos ) & ( uint32_t )( 0x01  )  )

#define SET_RANGE_BIT_8BIT(var, start, end)   ( uint8_t ) ( var | ( uint8_t )( ( uint8_t ) ( ( uint8_t ) ( ~0 ) >> start ) << end ) )
#define CLR_RANGE_BIT_8BIT(var, start, end)   ( uint8_t ) ( var & ( ( uint8_t ) ( ~( ( uint8_t )( ( uint8_t ) ( ( uint8_t ) ( ~0 ) >> start ) << end ) ) ) ) ) 
#define GET_RANGE_BIT_8BIT(var, start, end)   ( uint8_t ) ( ( uint8_t ) ( var >> start ) << end )

#define SET_RANGE_BIT_16BIT(var, start, end)   ( uint16_t ) ( var | ( uint16_t )( ( uint16_t ) ( ( uint16_t ) ( ~0 ) >> start ) << end ) )
#define CLR_RANGE_BIT_16BIT(var, start, end)   ( uint16_t ) ( var & ( ( uint16_t ) ( ~( ( uint16_t )( ( uint16_t) ( ( uint16_t ) ( ~0 ) >> start ) << end ) ) ) ) ) 
#define GET_RANGE_BIT_16BIT(var, start, end)   ( uint16_t ) ( ( uint16_t ) ( var >> start ) << end )

#define SET_RANGE_BIT_32BIT(var, start, end)   ( uint32_t ) ( var | ( uint32_t )( ( uint32_t ) ( ( uint32_t ) ( ~0 ) >> start ) << end ) )
#define CLR_RANGE_BIT_32BIT(var, start, end)   ( uint32_t ) ( var & ( ( uint32_t ) ( ~( ( uint32_t )( ( uint32_t ) ( ( uint32_t ) ( ~0 ) >> start ) << end ) ) ) ) ) 
#define GET_RANGE_BIT_32BIT(var, start, end)   ( uint32_t ) ( ( uint32_t ) ( var >> start ) << end )

#endif
