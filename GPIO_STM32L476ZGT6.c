// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#if defined( STM32L476xx )

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include <stdbool.h>

    #include "../../GPIO_Internal.h"
    #include "GPIO_STM32L476ZGT6.h"

    #include "stm32l4xx.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum GPIO_STM32L476ZGT6_Event
{
    GPIO_STM32L476ZGT6_Event_None = 0,
    GPIO_STM32L476ZGT6_Event_ExternalInterrupt = UTIL_BIT( 0 ),
} GPIO_STM32L476ZGT6_Event_t;

typedef struct GPIO_STM32L476ZGT6_Instance
{
    GPIO_TypeDef * GPIOx;
    GPIO_InitTypeDef InitType;
    GPIO_STM32L476ZGT6_Event_t Event;
    GPIO_STM32L476ZGT6_OnInterrupt_t OnInterrupt;
} GPIO_STM32L476ZGT6_Instance_t;

typedef struct GPIO_STM32L476ZGT6_Context
{
    bool IsInitialized;
    GPIO_STM32L476ZGT6_Instance_t Instance[ GPIO_STM32L476ZGT6_Count ];
} GPIO_STM32L476ZGT6_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin );

void EXTI0_IRQHandler( void );
void EXTI1_IRQHandler( void );
void EXTI2_IRQHandler( void );
void EXTI3_IRQHandler( void );
void EXTI4_IRQHandler( void );
void EXTI9_5_IRQHandler( void );
void EXTI15_10_IRQHandler( void );

static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_Initialize( void );
static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_Cycle( void );
static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_DeInitialize( void );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static GPIO_STM32L476ZGT6_Context_t GPIO_STM32L476ZGT6_Context = {
    .IsInitialized = false,
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
    const GPIO_STM32L476ZGT6_t GPIO_PIN_0_Pool[] = {
        GPIO_STM32L476ZGT6_12, // PH0
        GPIO_STM32L476ZGT6_15, // PC0
        GPIO_STM32L476ZGT6_23, // PA0
        GPIO_STM32L476ZGT6_35, // PB0
        GPIO_STM32L476ZGT6_81, // PD0
        GPIO_STM32L476ZGT6_97, // PE0
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_1_Pool[] = {
        GPIO_STM32L476ZGT6_13, // PH1
        GPIO_STM32L476ZGT6_16, // PC1
        GPIO_STM32L476ZGT6_24, // PA1
        GPIO_STM32L476ZGT6_36, // PB1
        GPIO_STM32L476ZGT6_82, // PD1
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_2_Pool[] = {
        GPIO_STM32L476ZGT6_1,  // PE2
        GPIO_STM32L476ZGT6_17, // PC2
        GPIO_STM32L476ZGT6_25, // PA2
        GPIO_STM32L476ZGT6_37, // PB2
        GPIO_STM32L476ZGT6_83, // PD2
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_3_Pool[] = {
        GPIO_STM32L476ZGT6_2,  // PE3
        GPIO_STM32L476ZGT6_18, // PC3
        GPIO_STM32L476ZGT6_26, // PA3
        GPIO_STM32L476ZGT6_84, // PD3
        GPIO_STM32L476ZGT6_89, // PB3
        GPIO_STM32L476ZGT6_94, // PH3
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_4_Pool[] = {
        GPIO_STM32L476ZGT6_3,  // PE4
        GPIO_STM32L476ZGT6_29, // PA4
        GPIO_STM32L476ZGT6_33, // PC4
        GPIO_STM32L476ZGT6_85, // PD4
        GPIO_STM32L476ZGT6_90, // PB4
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_5_Pool[] = {
        GPIO_STM32L476ZGT6_4,  // PE5
        GPIO_STM32L476ZGT6_30, // PA5
        GPIO_STM32L476ZGT6_34, // PC5
        GPIO_STM32L476ZGT6_86, // PD5
        GPIO_STM32L476ZGT6_91, // PB5
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_6_Pool[] = {
        GPIO_STM32L476ZGT6_5,  // PE6
        GPIO_STM32L476ZGT6_31, // PA6
        GPIO_STM32L476ZGT6_63, // PC6
        GPIO_STM32L476ZGT6_87, // PD6
        GPIO_STM32L476ZGT6_92, // PB6
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_7_Pool[] = {
        GPIO_STM32L476ZGT6_32, // PA7
        GPIO_STM32L476ZGT6_38, // PE7
        GPIO_STM32L476ZGT6_64, // PC7
        GPIO_STM32L476ZGT6_88, // PD7
        GPIO_STM32L476ZGT6_93, // PB7
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_8_Pool[] = {
        GPIO_STM32L476ZGT6_39, // PE8
        GPIO_STM32L476ZGT6_55, // PD8
        GPIO_STM32L476ZGT6_65, // PC8
        GPIO_STM32L476ZGT6_67, // PA8
        GPIO_STM32L476ZGT6_95, // PB8
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_9_Pool[] = {
        GPIO_STM32L476ZGT6_40, // PE9
        GPIO_STM32L476ZGT6_56, // PD9
        GPIO_STM32L476ZGT6_66, // PC9
        GPIO_STM32L476ZGT6_68, // PA9
        GPIO_STM32L476ZGT6_96, // PB9
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_10_Pool[] = {
        GPIO_STM32L476ZGT6_41, // PE10
        GPIO_STM32L476ZGT6_47, // PB10
        GPIO_STM32L476ZGT6_57, // PD10
        GPIO_STM32L476ZGT6_69, // PA10
        GPIO_STM32L476ZGT6_78, // PC10
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_11_Pool[] = {
        GPIO_STM32L476ZGT6_42, // PE11
        GPIO_STM32L476ZGT6_58, // PD11
        GPIO_STM32L476ZGT6_70, // PA11
        GPIO_STM32L476ZGT6_79, // PC11
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_12_Pool[] = {
        GPIO_STM32L476ZGT6_43, // PE12
        GPIO_STM32L476ZGT6_51, // PB12
        GPIO_STM32L476ZGT6_59, // PD12
        GPIO_STM32L476ZGT6_71, // PA12
        GPIO_STM32L476ZGT6_80, // PC12
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_13_Pool[] = {
        GPIO_STM32L476ZGT6_7,  // PC13
        GPIO_STM32L476ZGT6_44, // PE13
        GPIO_STM32L476ZGT6_52, // PB13
        GPIO_STM32L476ZGT6_60, // PD13
        GPIO_STM32L476ZGT6_72, // PA13
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_14_Pool[] = {
        GPIO_STM32L476ZGT6_8,  // PC14
        GPIO_STM32L476ZGT6_45, // PE14
        GPIO_STM32L476ZGT6_53, // PB14
        GPIO_STM32L476ZGT6_61, // PD14
        GPIO_STM32L476ZGT6_76, // PA14
    };
    const GPIO_STM32L476ZGT6_t GPIO_PIN_15_Pool[] = {
        GPIO_STM32L476ZGT6_9,  // PC15
        GPIO_STM32L476ZGT6_46, // PE15
        GPIO_STM32L476ZGT6_54, // PB15
        GPIO_STM32L476ZGT6_62, // PD15
        GPIO_STM32L476ZGT6_77, // PA15
    };

    do
    {
        const GPIO_STM32L476ZGT6_t * GPIO_Pool = NULL;
        uint32_t GPIO_PoolSize = 0;
        switch ( GPIO_Pin )
        {
            case GPIO_PIN_0:
                GPIO_Pool = GPIO_PIN_0_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_0_Pool );
                break;

            case GPIO_PIN_1:
                GPIO_Pool = GPIO_PIN_1_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_1_Pool );
                break;

            case GPIO_PIN_2:
                GPIO_Pool = GPIO_PIN_2_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_2_Pool );
                break;

            case GPIO_PIN_3:
                GPIO_Pool = GPIO_PIN_3_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_3_Pool );
                break;

            case GPIO_PIN_4:
                GPIO_Pool = GPIO_PIN_4_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_4_Pool );
                break;

            case GPIO_PIN_5:
                GPIO_Pool = GPIO_PIN_5_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_5_Pool );
                break;

            case GPIO_PIN_6:
                GPIO_Pool = GPIO_PIN_6_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_6_Pool );
                break;

            case GPIO_PIN_7:
                GPIO_Pool = GPIO_PIN_7_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_7_Pool );
                break;

            case GPIO_PIN_8:
                GPIO_Pool = GPIO_PIN_8_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_8_Pool );
                break;

            case GPIO_PIN_9:
                GPIO_Pool = GPIO_PIN_9_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_9_Pool );
                break;

            case GPIO_PIN_10:
                GPIO_Pool = GPIO_PIN_10_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_10_Pool );
                break;

            case GPIO_PIN_11:
                GPIO_Pool = GPIO_PIN_11_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_11_Pool );
                break;

            case GPIO_PIN_12:
                GPIO_Pool = GPIO_PIN_12_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_12_Pool );
                break;

            case GPIO_PIN_13:
                GPIO_Pool = GPIO_PIN_13_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_13_Pool );
                break;

            case GPIO_PIN_14:
                GPIO_Pool = GPIO_PIN_14_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_14_Pool );
                break;

            case GPIO_PIN_15:
                GPIO_Pool = GPIO_PIN_15_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_15_Pool );
                break;

            default:
                break;
        }
        if ( GPIO_Pool == NULL )
        {
            break;
        }

        // Loop over port pin numbers equal to `GPIO_Pin` ex: GPIO_Pin=0, should loop over PA0, PB0, PC0, PD0, PE0, ...etc
        for ( uint32_t GPIO_Index = 0; GPIO_Index < GPIO_PoolSize; ++GPIO_Index )
        {
            GPIO_STM32L476ZGT6_t GPIO_x = GPIO_Pool[ GPIO_Index ];
            GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIO_x ];
            GPIO_InitTypeDef * InitType = &Instance->InitType;

            if ( InitType->Pin == GPIO_Pin
                 && ( InitType->Mode == GPIO_MODE_IT_RISING
                      || InitType->Mode == GPIO_MODE_IT_FALLING
                      || InitType->Mode == GPIO_MODE_IT_RISING_FALLING ) )
            {
                Instance->Event |= GPIO_STM32L476ZGT6_Event_ExternalInterrupt;

                if ( Instance->OnInterrupt.Callback )
                {
                    Instance->OnInterrupt.Callback( GPIO_x, Instance->OnInterrupt.Context );
                }
            }
        }
    }
    while ( 0 );
}

void EXTI0_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_0 );
}

void EXTI1_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_1 );
}

void EXTI2_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_2 );
}

void EXTI3_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_3 );
}

void EXTI4_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_4 );
}

void EXTI9_5_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_5 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_6 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_7 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_8 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_9 );
}

void EXTI15_10_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_10 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_11 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_12 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_13 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_14 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_15 );
}

static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_Initialize( void )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        if ( GPIO_STM32L476ZGT6_Context.IsInitialized )
        {
            // Already initialized
            break;
        }

        // FIXME Remove the usage of `MX_GPIO_Init()`
    #if 1
        extern void MX_GPIO_Init( void );
        MX_GPIO_Init( );
    #endif

        // TODO Enable All External Interrupts

        GPIO_STM32L476ZGT6_Context.IsInitialized = true;
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_Cycle( void )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( GPIO_STM32L476ZGT6_Context );
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Context_DeInitialize( void )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( GPIO_STM32L476ZGT6_Context );

        // TODO Disable All External Interrupts
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Initialize( GPIO_STM32L476ZGT6_t GPIOx )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        if ( ( Status = GPIO_STM32L476ZGT6_Context_Initialize( ) ) != GPIO_STM32L476ZGT6_Status_Success )
        {
            break;
        }

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];
        GPIO_InitTypeDef * InitType = &Instance->InitType;

        Instance->GPIOx = NULL;
        Instance->Event = GPIO_STM32L476ZGT6_Event_None;
        Instance->OnInterrupt = ( GPIO_STM32L476ZGT6_OnInterrupt_t ) {
            .Callback = NULL,
            .Context = NULL,
        };

        switch ( GPIOx )
        {
            case GPIO_STM32L476ZGT6_1:
            case GPIO_STM32L476ZGT6_2:
            case GPIO_STM32L476ZGT6_3:
            case GPIO_STM32L476ZGT6_4:
            case GPIO_STM32L476ZGT6_5:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_2 << ( GPIOx - GPIO_STM32L476ZGT6_1 );
                break;

            case GPIO_STM32L476ZGT6_6:
                break;

            case GPIO_STM32L476ZGT6_7:
            case GPIO_STM32L476ZGT6_8:
            case GPIO_STM32L476ZGT6_9:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_13 << ( GPIOx - GPIO_STM32L476ZGT6_7 );
                break;

            case GPIO_STM32L476ZGT6_10:
            case GPIO_STM32L476ZGT6_11:
            case GPIO_STM32L476ZGT6_12:
            case GPIO_STM32L476ZGT6_13:
            case GPIO_STM32L476ZGT6_14:
            case GPIO_STM32L476ZGT6_15:
                __HAL_RCC_GPIOF_CLK_ENABLE( );
                Instance->GPIOx = GPIOF;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_10 );
                break;

            case GPIO_STM32L476ZGT6_16:
            case GPIO_STM32L476ZGT6_17:
                break;

            case GPIO_STM32L476ZGT6_18:
            case GPIO_STM32L476ZGT6_19:
            case GPIO_STM32L476ZGT6_20:
            case GPIO_STM32L476ZGT6_21:
            case GPIO_STM32L476ZGT6_22:
                __HAL_RCC_GPIOF_CLK_ENABLE( );
                Instance->GPIOx = GPIOF;
                InitType->Pin = GPIO_PIN_6 << ( GPIOx - GPIO_STM32L476ZGT6_18 );
                break;

            case GPIO_STM32L476ZGT6_23:
            case GPIO_STM32L476ZGT6_24:
                __HAL_RCC_GPIOH_CLK_ENABLE( );
                Instance->GPIOx = GPIOH;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_23 );
                break;

            case GPIO_STM32L476ZGT6_25:
                break;

            case GPIO_STM32L476ZGT6_26:
            case GPIO_STM32L476ZGT6_27:
            case GPIO_STM32L476ZGT6_28:
            case GPIO_STM32L476ZGT6_29:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_26 );
                break;

            case GPIO_STM32L476ZGT6_30:
            case GPIO_STM32L476ZGT6_31:
            case GPIO_STM32L476ZGT6_32:
            case GPIO_STM32L476ZGT6_33:
                break;

            case GPIO_STM32L476ZGT6_34:
            case GPIO_STM32L476ZGT6_35:
            case GPIO_STM32L476ZGT6_36:
            case GPIO_STM32L476ZGT6_37:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_34 );
                break;

            case GPIO_STM32L476ZGT6_38:
            case GPIO_STM32L476ZGT6_39:
                break;

            case GPIO_STM32L476ZGT6_40:
            case GPIO_STM32L476ZGT6_41:
            case GPIO_STM32L476ZGT6_42:
            case GPIO_STM32L476ZGT6_43:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_4 << ( GPIOx - GPIO_STM32L476ZGT6_40 );
                break;

            case GPIO_STM32L476ZGT6_44:
            case GPIO_STM32L476ZGT6_45:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_4 << ( GPIOx - GPIO_STM32L476ZGT6_44 );
                break;

            case GPIO_STM32L476ZGT6_46:
            case GPIO_STM32L476ZGT6_47:
            case GPIO_STM32L476ZGT6_48:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_46 );
                break;

            case GPIO_STM32L476ZGT6_49:
            case GPIO_STM32L476ZGT6_50:
                __HAL_RCC_GPIOF_CLK_ENABLE( );
                Instance->GPIOx = GPIOF;
                InitType->Pin = GPIO_PIN_11 << ( GPIOx - GPIO_STM32L476ZGT6_49 );
                break;

            case GPIO_STM32L476ZGT6_51:
            case GPIO_STM32L476ZGT6_52:
                break;

            case GPIO_STM32L476ZGT6_53:
            case GPIO_STM32L476ZGT6_54:
            case GPIO_STM32L476ZGT6_55:
                __HAL_RCC_GPIOF_CLK_ENABLE( );
                Instance->GPIOx = GPIOF;
                InitType->Pin = GPIO_PIN_13 << ( GPIOx - GPIO_STM32L476ZGT6_53 );
                break;

            case GPIO_STM32L476ZGT6_56:
            case GPIO_STM32L476ZGT6_57:
                __HAL_RCC_GPIOG_CLK_ENABLE( );
                Instance->GPIOx = GPIOG;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_56 );
                break;

            case GPIO_STM32L476ZGT6_58:
            case GPIO_STM32L476ZGT6_59:
            case GPIO_STM32L476ZGT6_60:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_7 << ( GPIOx - GPIO_STM32L476ZGT6_58 );
                break;

            case GPIO_STM32L476ZGT6_61:
            case GPIO_STM32L476ZGT6_62:
                break;

            case GPIO_STM32L476ZGT6_63:
            case GPIO_STM32L476ZGT6_64:
            case GPIO_STM32L476ZGT6_65:
            case GPIO_STM32L476ZGT6_66:
            case GPIO_STM32L476ZGT6_67:
            case GPIO_STM32L476ZGT6_68:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_10 << ( GPIOx - GPIO_STM32L476ZGT6_63 );
                break;

            case GPIO_STM32L476ZGT6_69:
            case GPIO_STM32L476ZGT6_70:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_10 << ( GPIOx - GPIO_STM32L476ZGT6_69 );
                break;

            case GPIO_STM32L476ZGT6_71:
            case GPIO_STM32L476ZGT6_72:
                break;

            case GPIO_STM32L476ZGT6_73:
            case GPIO_STM32L476ZGT6_74:
            case GPIO_STM32L476ZGT6_75:
            case GPIO_STM32L476ZGT6_76:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_12 << ( GPIOx - GPIO_STM32L476ZGT6_73 );
                break;

            case GPIO_STM32L476ZGT6_77:
            case GPIO_STM32L476ZGT6_78:
            case GPIO_STM32L476ZGT6_79:
            case GPIO_STM32L476ZGT6_80:
            case GPIO_STM32L476ZGT6_81:
            case GPIO_STM32L476ZGT6_82:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L476ZGT6_77 );
                break;

            case GPIO_STM32L476ZGT6_83:
            case GPIO_STM32L476ZGT6_84:
                break;

            case GPIO_STM32L476ZGT6_85:
            case GPIO_STM32L476ZGT6_86:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_14 << ( GPIOx - GPIO_STM32L476ZGT6_85 );
                break;

            case GPIO_STM32L476ZGT6_87:
            case GPIO_STM32L476ZGT6_88:
            case GPIO_STM32L476ZGT6_89:
            case GPIO_STM32L476ZGT6_90:
            case GPIO_STM32L476ZGT6_91:
            case GPIO_STM32L476ZGT6_92:
            case GPIO_STM32L476ZGT6_93:
                __HAL_RCC_GPIOG_CLK_ENABLE( );
                Instance->GPIOx = GPIOG;
                InitType->Pin = GPIO_PIN_2 << ( GPIOx - GPIO_STM32L476ZGT6_87 );
                break;

            case GPIO_STM32L476ZGT6_94:
            case GPIO_STM32L476ZGT6_95:
                break;

            case GPIO_STM32L476ZGT6_96:
            case GPIO_STM32L476ZGT6_97:
            case GPIO_STM32L476ZGT6_98:
            case GPIO_STM32L476ZGT6_99:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_6 << ( GPIOx - GPIO_STM32L476ZGT6_96 );
                break;

            case GPIO_STM32L476ZGT6_100:
            case GPIO_STM32L476ZGT6_101:
            case GPIO_STM32L476ZGT6_102:
            case GPIO_STM32L476ZGT6_103:
            case GPIO_STM32L476ZGT6_104:
            case GPIO_STM32L476ZGT6_105:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L476ZGT6_100 );
                break;

            case GPIO_STM32L476ZGT6_106:
            case GPIO_STM32L476ZGT6_107:
            case GPIO_STM32L476ZGT6_108:
                break;

            case GPIO_STM32L476ZGT6_109:
            case GPIO_STM32L476ZGT6_110:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_14 << ( GPIOx - GPIO_STM32L476ZGT6_109 );
                break;

            case GPIO_STM32L476ZGT6_111:
            case GPIO_STM32L476ZGT6_112:
            case GPIO_STM32L476ZGT6_113:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_10 << ( GPIOx - GPIO_STM32L476ZGT6_111 );
                break;

            case GPIO_STM32L476ZGT6_114:
            case GPIO_STM32L476ZGT6_115:
            case GPIO_STM32L476ZGT6_116:
            case GPIO_STM32L476ZGT6_117:
            case GPIO_STM32L476ZGT6_118:
            case GPIO_STM32L476ZGT6_119:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_114 );
                break;

            case GPIO_STM32L476ZGT6_120:
            case GPIO_STM32L476ZGT6_121:
                break;

            case GPIO_STM32L476ZGT6_122:
            case GPIO_STM32L476ZGT6_123:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_6 << ( GPIOx - GPIO_STM32L476ZGT6_122 );
                break;

            case GPIO_STM32L476ZGT6_124:
            case GPIO_STM32L476ZGT6_125:
            case GPIO_STM32L476ZGT6_126:
            case GPIO_STM32L476ZGT6_127:
            case GPIO_STM32L476ZGT6_128:
            case GPIO_STM32L476ZGT6_129:
                __HAL_RCC_GPIOG_CLK_ENABLE( );
                Instance->GPIOx = GPIOG;
                InitType->Pin = GPIO_PIN_9 << ( GPIOx - GPIO_STM32L476ZGT6_124 );
                break;

            case GPIO_STM32L476ZGT6_130:
            case GPIO_STM32L476ZGT6_131:
                break;

            case GPIO_STM32L476ZGT6_132:
                __HAL_RCC_GPIOG_CLK_ENABLE( );
                Instance->GPIOx = GPIOG;
                InitType->Pin = GPIO_PIN_15 << ( GPIOx - GPIO_STM32L476ZGT6_132 );
                break;

            case GPIO_STM32L476ZGT6_133:
            case GPIO_STM32L476ZGT6_134:
            case GPIO_STM32L476ZGT6_135:
            case GPIO_STM32L476ZGT6_136:
            case GPIO_STM32L476ZGT6_137:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_3 << ( GPIOx - GPIO_STM32L476ZGT6_133 );
                break;

            case GPIO_STM32L476ZGT6_138:
                break;

            case GPIO_STM32L476ZGT6_139:
            case GPIO_STM32L476ZGT6_140:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L476ZGT6_139 );
                break;

            case GPIO_STM32L476ZGT6_141:
            case GPIO_STM32L476ZGT6_142:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L476ZGT6_141 );
                break;

            case GPIO_STM32L476ZGT6_143:
            case GPIO_STM32L476ZGT6_144:
                break;

            default:
                Status = GPIO_STM32L476ZGT6_Status_NotSupported;
                break;
        }

        if ( Status != GPIO_STM32L476ZGT6_Status_Success )
        {
            break;
        }

        // TODO Check the applicability of the following on special function IOs
        InitType->Mode = GPIO_MODE_ANALOG;
        InitType->Pull = GPIO_NOPULL;

        // FIXME This overwrites what MX_GPIO_Init is doing
        // Status = GPIO_STM32L476ZGT6_Commit( GPIOx );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Cycle( GPIO_STM32L476ZGT6_t GPIOx )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        if ( ( Status = GPIO_STM32L476ZGT6_Context_Cycle( ) ) != GPIO_STM32L476ZGT6_Status_Success )
        {
            break;
        }

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];
        GPIO_STM32L476ZGT6_Event_t Event = Instance->Event; // CAUTION: Has to copy events occurred at the early start of the cycle, so as to be cleared at the end of the cycle,
                                                            //          which let events occurs after that for the next cycle call
        Instance->Event &= ~Event;                          //          Clear captured events

        if ( ( Event & GPIO_STM32L476ZGT6_Event_ExternalInterrupt ) == GPIO_STM32L476ZGT6_Event_ExternalInterrupt )
        {
            Event &= ~GPIO_STM32L476ZGT6_Event_ExternalInterrupt;
            GPIO_Debug( "External Interrupt: GPIO=%d", GPIOx );
        }

        if ( Event )
        {
            GPIO_Warning( "Not handled events %X: GPIOx=%d", Event, GPIOx );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_DeInitialize( GPIO_STM32L476ZGT6_t GPIOx )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        // TODO De-Initialize & Disable
        // TODO Apply Lowest Power Mode

        Status = GPIO_STM32L476ZGT6_Context_DeInitialize( );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetOnInterrupt( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_OnInterrupt_t OnInterrupt )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, OnInterrupt={Callback=%p, Context=%p} )", __FUNCTION__, GPIOx, OnInterrupt.Callback, OnInterrupt.Context );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        Instance->OnInterrupt = OnInterrupt;
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetMode( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Mode_t Mode )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Mode=%d )", __FUNCTION__, GPIOx, Mode );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        switch ( Mode )
        {
            case GPIO_STM32L476ZGT6_Mode_Input:
                Instance->InitType.Mode = GPIO_MODE_INPUT;
                break;

            case GPIO_STM32L476ZGT6_Mode_Output:
                Instance->InitType.Mode = GPIO_MODE_OUTPUT_PP;
                break;

            case GPIO_STM32L476ZGT6_Mode_OutputOpenDrain:
                Instance->InitType.Mode = GPIO_MODE_OUTPUT_OD;
                break;

            case GPIO_STM32L476ZGT6_Mode_Interrupt:
                Instance->InitType.Mode = GPIO_MODE_IT_RISING_FALLING;
                break;

            case GPIO_STM32L476ZGT6_Mode_InterruptRising:
                Instance->InitType.Mode = GPIO_MODE_IT_RISING;
                break;

            case GPIO_STM32L476ZGT6_Mode_InterruptFalling:
                Instance->InitType.Mode = GPIO_MODE_IT_FALLING;
                break;

            case GPIO_STM32L476ZGT6_Mode_Event:
                Instance->InitType.Mode = GPIO_MODE_EVT_RISING_FALLING;
                break;

            case GPIO_STM32L476ZGT6_Mode_EventRising:
                Instance->InitType.Mode = GPIO_MODE_EVT_RISING;
                break;

            case GPIO_STM32L476ZGT6_Mode_EventFalling:
                Instance->InitType.Mode = GPIO_MODE_EVT_FALLING;
                break;

            case GPIO_STM32L476ZGT6_Mode_Alternate:
                Instance->InitType.Mode = GPIO_MODE_AF_PP;
                break;

            case GPIO_STM32L476ZGT6_Mode_AlternateOpenDrain:
                Instance->InitType.Mode = GPIO_MODE_AF_OD;
                break;

            case GPIO_STM32L476ZGT6_Mode_Analog:
                Instance->InitType.Mode = GPIO_MODE_ANALOG;
                break;

            case GPIO_STM32L476ZGT6_Mode_AnalogADC:
                Instance->InitType.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
                break;

            default:
                Status = GPIO_STM32L476ZGT6_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetPull( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Pull_t Pull )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Pull=%d )", __FUNCTION__, GPIOx, Pull );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        switch ( Pull )
        {
            case GPIO_STM32L476ZGT6_Pull_None:
                Instance->InitType.Pull = GPIO_NOPULL;
                break;

            case GPIO_STM32L476ZGT6_Pull_Up:
                Instance->InitType.Pull = GPIO_PULLUP;
                break;

            case GPIO_STM32L476ZGT6_Pull_Down:
                Instance->InitType.Pull = GPIO_PULLDOWN;
                break;

            default:
                Status = GPIO_STM32L476ZGT6_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetSpeed( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Speed_t Speed )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Speed=%d )", __FUNCTION__, GPIOx, Speed );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        switch ( Speed )
        {
            case GPIO_STM32L476ZGT6_Speed_Low:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_LOW;
                break;

            case GPIO_STM32L476ZGT6_Speed_Medium:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_MEDIUM;
                break;

            case GPIO_STM32L476ZGT6_Speed_High:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_HIGH;
                break;

            case GPIO_STM32L476ZGT6_Speed_VeryHigh:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                break;

            default:
                Status = GPIO_STM32L476ZGT6_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetFunction( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Function_t Function )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Function=%d )", __FUNCTION__, GPIOx, Function );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        switch ( Function )
        {
            case GPIO_STM32L476ZGT6_Function_0:
            case GPIO_STM32L476ZGT6_Function_1:
            case GPIO_STM32L476ZGT6_Function_2:
            case GPIO_STM32L476ZGT6_Function_3:
            case GPIO_STM32L476ZGT6_Function_4:
            case GPIO_STM32L476ZGT6_Function_5:
            case GPIO_STM32L476ZGT6_Function_6:
            case GPIO_STM32L476ZGT6_Function_7:
            case GPIO_STM32L476ZGT6_Function_8:
            case GPIO_STM32L476ZGT6_Function_9:
            case GPIO_STM32L476ZGT6_Function_10:
            case GPIO_STM32L476ZGT6_Function_11:
            case GPIO_STM32L476ZGT6_Function_12:
            case GPIO_STM32L476ZGT6_Function_13:
            case GPIO_STM32L476ZGT6_Function_14:
            case GPIO_STM32L476ZGT6_Function_15:
                // TODO Verify Alternate Function Application
                break;

            default:
                Status = GPIO_STM32L476ZGT6_Status_NotSupported;
                break;
        }
        if ( Status != GPIO_STM32L476ZGT6_Status_Success )
        {
            break;
        }

        Instance->InitType.Alternate = Function;
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Commit( GPIO_STM32L476ZGT6_t GPIOx )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx != NULL )
        {
            HAL_GPIO_Init( Instance->GPIOx, &Instance->InitType );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Write( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Value_t Value )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Value=%d )", __FUNCTION__, GPIOx, Value );

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx != NULL )
        {
            HAL_GPIO_WritePin( Instance->GPIOx, Instance->InitType.Pin, Value );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Read( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Value_t * Value )
{
    GPIO_STM32L476ZGT6_Status_t Status = GPIO_STM32L476ZGT6_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Value=%p )", __FUNCTION__, GPIOx, Value );

        if ( Value == NULL )
        {
            Status = GPIO_STM32L476ZGT6_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L476ZGT6_Instance_t * Instance = &GPIO_STM32L476ZGT6_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx == NULL )
        {
            // Bypass not assigned
            break;
        }

        *Value = HAL_GPIO_ReadPin( Instance->GPIOx, Instance->InitType.Pin );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char GPIO_STM32L476ZGT6_VERSION[] = "0.0.0.v20261101-1429";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* defined( STM32L476xx ) */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
