#ifndef _H_SYSTICK_H_
#define _H_SYSTICK_H_
#include <basetypes.h>
#include <bitOps.h>

#define SYSTICK_BASE_ADDRESS       (0xE000E010U)
#define SYSTICK_CTRL_OFFSET        (0x00000000U)
#define SYSTICK_LOAD_OFFSET        (0x00000004U)

#define SYSTICK_CTRL_ADDRESS       ( volatile uint32_t * )( SYSTICK_BASE_ADDRESS + SYSTICK_CTRL_OFFSET )
#define SYSTICK_LOAD_ADDRESS       ( volatile uint32_t * )( SYSTICK_BASE_ADDRESS + SYSTICK_LOAD_OFFSET )

#define SYSTICK_CTRL_VAL           ( *( SYSTICK_CTRL_ADDRESS ) )
#define SYSTICK_LOAD_VAL           ( *( SYSTICK_LOAD_ADDRESS ) )

#define SYSTICK_COUNTER_ENABLE()          ( SYSTICK_CTRL_VAL = SET_NTH_BIT_32BIT( SYSTICK_CTRL_VAL, 0 ) )
#define SYSTICK_TICKINT_COUNT_TO_ZERO()   ( SYSTICK_CTRL_VAL = SET_NTH_BIT_32BIT( SYSTICK_CTRL_VAL, 1 ) )
#define SYSTICK_CLK_SRC_AHB()             ( SYSTICK_CTRL_VAL = SET_NTH_BIT_32BIT( SYSTICK_CTRL_VAL, 2 ) )

#define SYSTICK_SET_LOAD_COUNTER(var)        ( SYSTICK_LOAD_VAL = var )

/* Base address of Reset and clock control */
#define RCC_BASE_ADDRESS                         (0x40021000U)

/* Ofsset for different Reset and clock control registers */

#define RCC_CR_OFFSET                            (0x00000000U)
#define RCC_CFGR_OFFSET                          (0x00000004U)
#define RCC_CIR_OFFSET                           (0x00000008U)
#define RCC_APB2RSTR_OFFSET                      (0x0000000CU)
#define RCC_APB1RSTR_OFFSET                      (0x00000010U)
#define RCC_AHBENR_OFFSET                        (0x00000014U)
#define RCC_APB2ENR_OFFSET                       (0x00000018U)
#define RCC_APB1ENR_OFFSET                       (0x0000001CU)
#define RCC_BDCR_OFFSET                          (0x00000020U)
#define RCC_CSR_OFFSET                           (0x00000024U)
#define RCC_AHBRSTR_OFFSET                       (0x00000028U)
#define RCC_CFGR2_OFFSET                         (0x0000002CU)

/* Addresses of different registers of Reset and clock control */

#define RCC_CR_ADDRESS                           ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CR_OFFSET )
#define RCC_CFGR_ADDRESS                         ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CFGR_OFFSET )
#define RCC_CIR_ADDRESS                          ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CIR_OFFSET )
#define RCC_APB2RSTR_ADDRESS                     ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB2RSTR_OFFSET )
#define RCC_APB1RSTR_ADDRESS                     ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB1RSTR_OFFSET )
#define RCC_AHBENR_ADDRESS                       ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_AHBENR_OFFSET )
#define RCC_APB2ENR_ADDRESS                      ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB2ENR_OFFSET )
#define RCC_APB1ENR_ADDRESS                      ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET )
#define RCC_BDCR_ADDRESS                         ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_BDCR_OFFSET )
#define RCC_CSR_ADDRESS                          ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CSR_OFFSET )
#define RCC_AHBRSTR_ADDRESS                      ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_AHBRSTR_OFFSET )
#define RCC_CFGR2_ADDRESS                        ( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CFGR2_OFFSET )

#define RCC_CR_VAL                               ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CR_OFFSET ) )
#define RCC_CFGR_VAL                             ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CFGR_OFFSET ) )
#define RCC_CIR_VAL                              ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CIR_OFFSET ) )
#define RCC_APB2RSTR_VAL                         ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB2RSTR_OFFSET ) )
#define RCC_APB1RSTR_VAL                         ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB1RSTR_OFFSET ) )
#define RCC_AHBENR_VAL                           ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_AHBENR_OFFSET ) )
#define RCC_APB2ENR_VAL                          ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB2ENR_OFFSET ) )
#define RCC_APB1ENR_VAL                          ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET ) )
#define RCC_BDCR_VAL                             ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_BDCR_OFFSET ) )
#define RCC_CSR_VAL                              ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CSR_OFFSET ) )
#define RCC_AHBRSTR_VAL                          ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_AHBRSTR_OFFSET ) )
#define RCC_CFGR2_VAL                            ( *( volatile uint32_t * )( RCC_BASE_ADDRESS + RCC_CFGR2_OFFSET ) )

#define RCC_SET_HSI_CLK()                        ( RCC_CR_VAL = SET_NTH_BIT_32BIT( RCC_CR_VAL, 0 ) )
#define RCC_CLR_HSI_CLK()                        ( RCC_CR_VAL = CLR_NTH_BIT_32BIT( RCC_CR_VAL, 0 ) )
#define RCC_GET_HSI_STATUS()                     GET_NTH_BIT_32BIT( RCC_CR_VAL, 1 )
#define RCC_SET_PLL_CLK()                        ( RCC_CR_VAL = SET_NTH_BIT_32BIT( RCC_CR_VAL, 24 ) )
#define RCC_CLR_PLL_CLK()                        ( RCC_CR_VAL = CLR_NTH_BIT_32BIT( RCC_CR_VAL, 24 ) )
#define RCC_GET_PLL_STATUS()                     GET_NTH_BIT_32BIT( RCC_CR_VAL, 25 )
#define RCC_SET_PLL2_CLK()                       ( RCC_CR_VAL = SET_NTH_BIT_32BIT( RCC_CR_VAL, 26 ) )
#define RCC_CLR_PLL2_CLK()                       ( RCC_CR_VAL = CLR_NTH_BIT_32BIT( RCC_CR_VAL, 26 ) )
#define RCC_GET_PLL2_STATUS()                    GET_NTH_BIT_32BIT( RCC_CR_VAL, 27 )
#define RCC_SET_PLL3_CLK()                       ( RCC_CR_VAL = SET_NTH_BIT_32BIT( RCC_CR_VAL, 28 ) )
#define RCC_CLR_PLL3_CLK()                       ( RCC_CR_VAL = CLR_NTH_BIT_32BIT( RCC_CR_VAL, 28 ) )
#define RCC_GET_PLL3_STATUS()                    GET_NTH_BIT_32BIT( RCC_CR_VAL, 29 )

#define RCC_SET_PLL_SRC_TO_HSI()                 ( RCC_CFGR_VAL = CLR_NTH_BIT_32BIT( RCC_CFGR_VAL, 16 ) )
#define RCC_SET_PLL_MUL_FACTOR_BIT1()            ( RCC_CFGR_VAL = SET_NTH_BIT_32BIT(RCC_CFGR_VAL, 18 ) )
#define RCC_SET_PLL_MUL_FACTOR_BIT2()            ( RCC_CFGR_VAL = SET_NTH_BIT_32BIT(RCC_CFGR_VAL, 19 ) )
#define RCC_SET_PLL_MUL_FACTOR_BIT3()            ( RCC_CFGR_VAL = SET_NTH_BIT_32BIT(RCC_CFGR_VAL, 20 ) )
#define RCC_SET_PLL_MUL_FACTOR_BIT4()            ( RCC_CFGR_VAL = SET_NTH_BIT_32BIT(RCC_CFGR_VAL, 21 ) )
#define RCC_SET_SYS_CLK_TO_PLL()                 { RCC_CFGR_VAL = CLR_NTH_BIT_32BIT( RCC_CFGR_VAL, 0 ); RCC_CFGR_VAL = SET_NTH_BIT_32BIT( RCC_CFGR_VAL, 1 ); }
#define RCC_SET_SYS_CLK_TO_HSI()                 { RCC_CFGR_VAL = CLR_NTH_BIT_32BIT( RCC_CFGR_VAL, 0 ); RCC_CFGR_VAL = CLR_NTH_BIT_32BIT( RCC_CFGR_VAL, 1 ); }
void systickSetup(void);
void clockSetup(void);
void systickInterruptFunction(void); 
void interruptInit( void );
#endif

