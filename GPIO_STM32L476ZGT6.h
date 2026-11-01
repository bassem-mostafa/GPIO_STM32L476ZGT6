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

/**
 *  @file
 *
 *  @brief Platform GPIO STM32L476ZGT6 Driver
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_GPIO_Driver
 *
 *  @{
 */

/**
 *  @defgroup Platform_GPIO_STM32L476ZGT6 STM32L476ZGT6
 *
 *  @image html STM32L476Zx_LQFP144.png
 *
 *  @{
 */

#ifndef GPIO_STM32L476ZGT6_H_
    #define GPIO_STM32L476ZGT6_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief GPIO STM32L476ZGT6 Operation Status
     *
     *  @enum GPIO_STM32L476ZGT6_Status_t
     */
    typedef enum GPIO_STM32L476ZGT6_Status
    {
        GPIO_STM32L476ZGT6_Status_Success = 0,     ///< Success
        GPIO_STM32L476ZGT6_Status_ArgumentInvalid, ///< Argument Invalid
        GPIO_STM32L476ZGT6_Status_NotSupported,    ///< Not Supported
        GPIO_STM32L476ZGT6_Status_Error,           ///< General Error
        GPIO_STM32L476ZGT6_Status_Busy,            ///< Busy
        GPIO_STM32L476ZGT6_Status_Timeout,         ///< Timeout
    } GPIO_STM32L476ZGT6_Status_t;

    /**
     *  @brief GPIO STM32L476ZGT6
     *
     *  @enum GPIO_STM32L476ZGT6_t
     */
    typedef enum GPIO_STM32L476ZGT6
    {
        GPIO_STM32L476ZGT6_1 = 0, ///< GPIO 1 [PE2] (Minimum)
        GPIO_STM32L476ZGT6_2,     ///< GPIO 2 [PE3]
        GPIO_STM32L476ZGT6_3,     ///< GPIO 3 [PE4]
        GPIO_STM32L476ZGT6_4,     ///< GPIO 4 [PE5]
        GPIO_STM32L476ZGT6_5,     ///< GPIO 5 [PE6]
        GPIO_STM32L476ZGT6_6,     ///< GPIO 6 [VBAT]
        GPIO_STM32L476ZGT6_7,     ///< GPIO 7 [PC13]
        GPIO_STM32L476ZGT6_8,     ///< GPIO 8 [PC14-OSC32_IN]
        GPIO_STM32L476ZGT6_9,     ///< GPIO 9 [PC15-OSC32_OUT]
        GPIO_STM32L476ZGT6_10,    ///< GPIO 10 [PF0]
        GPIO_STM32L476ZGT6_11,    ///< GPIO 11 [PF1]
        GPIO_STM32L476ZGT6_12,    ///< GPIO 12 [PF2]
        GPIO_STM32L476ZGT6_13,    ///< GPIO 13 [PF3]
        GPIO_STM32L476ZGT6_14,    ///< GPIO 14 [PF4]
        GPIO_STM32L476ZGT6_15,    ///< GPIO 15 [PF5]
        GPIO_STM32L476ZGT6_16,    ///< GPIO 16 [VSS]
        GPIO_STM32L476ZGT6_17,    ///< GPIO 17 [VDD]
        GPIO_STM32L476ZGT6_18,    ///< GPIO 18 [PF6]
        GPIO_STM32L476ZGT6_19,    ///< GPIO 19 [PF7]
        GPIO_STM32L476ZGT6_20,    ///< GPIO 20 [PF8]
        GPIO_STM32L476ZGT6_21,    ///< GPIO 21 [PF9]
        GPIO_STM32L476ZGT6_22,    ///< GPIO 22 [PF10]
        GPIO_STM32L476ZGT6_23,    ///< GPIO 23 [PH0-OC_IN]
        GPIO_STM32L476ZGT6_24,    ///< GPIO 24 [PH1-OC_OUT]
        GPIO_STM32L476ZGT6_25,    ///< GPIO 25 [NRST]
        GPIO_STM32L476ZGT6_26,    ///< GPIO 26 [PC0]
        GPIO_STM32L476ZGT6_27,    ///< GPIO 27 [PC1]
        GPIO_STM32L476ZGT6_28,    ///< GPIO 28 [PC2]
        GPIO_STM32L476ZGT6_29,    ///< GPIO 29 [PC3]
        GPIO_STM32L476ZGT6_30,    ///< GPIO 30 [VSSA]
        GPIO_STM32L476ZGT6_31,    ///< GPIO 31 [VREF-]
        GPIO_STM32L476ZGT6_32,    ///< GPIO 32 [VREF+]
        GPIO_STM32L476ZGT6_33,    ///< GPIO 33 [VDDA]
        GPIO_STM32L476ZGT6_34,    ///< GPIO 34 [PA0]
        GPIO_STM32L476ZGT6_35,    ///< GPIO 35 [PA1]
        GPIO_STM32L476ZGT6_36,    ///< GPIO 36 [PA2]
        GPIO_STM32L476ZGT6_37,    ///< GPIO 37 [PA3]
        GPIO_STM32L476ZGT6_38,    ///< GPIO 38 [VSS]
        GPIO_STM32L476ZGT6_39,    ///< GPIO 39 [VDD]
        GPIO_STM32L476ZGT6_40,    ///< GPIO 40 [PA4]
        GPIO_STM32L476ZGT6_41,    ///< GPIO 41 [PA5]
        GPIO_STM32L476ZGT6_42,    ///< GPIO 42 [PA6]
        GPIO_STM32L476ZGT6_43,    ///< GPIO 43 [PA7]
        GPIO_STM32L476ZGT6_44,    ///< GPIO 44 [PC4]
        GPIO_STM32L476ZGT6_45,    ///< GPIO 45 [PC5]
        GPIO_STM32L476ZGT6_46,    ///< GPIO 46 [PB0]
        GPIO_STM32L476ZGT6_47,    ///< GPIO 47 [PB1]
        GPIO_STM32L476ZGT6_48,    ///< GPIO 48 [PB2]
        GPIO_STM32L476ZGT6_49,    ///< GPIO 49 [PF11]
        GPIO_STM32L476ZGT6_50,    ///< GPIO 50 [PF12]
        GPIO_STM32L476ZGT6_51,    ///< GPIO 51 [VSS]
        GPIO_STM32L476ZGT6_52,    ///< GPIO 52 [VDD]
        GPIO_STM32L476ZGT6_53,    ///< GPIO 53 [PF13]
        GPIO_STM32L476ZGT6_54,    ///< GPIO 54 [PF14]
        GPIO_STM32L476ZGT6_55,    ///< GPIO 55 [PF15]
        GPIO_STM32L476ZGT6_56,    ///< GPIO 56 [PG0]
        GPIO_STM32L476ZGT6_57,    ///< GPIO 57 [PG1]
        GPIO_STM32L476ZGT6_58,    ///< GPIO 58 [PE7]
        GPIO_STM32L476ZGT6_59,    ///< GPIO 59 [PE8]
        GPIO_STM32L476ZGT6_60,    ///< GPIO 60 [PE9]
        GPIO_STM32L476ZGT6_61,    ///< GPIO 61 [VSS]
        GPIO_STM32L476ZGT6_62,    ///< GPIO 62 [VDD]
        GPIO_STM32L476ZGT6_63,    ///< GPIO 63 [PE10]
        GPIO_STM32L476ZGT6_64,    ///< GPIO 64 [PE11]
        GPIO_STM32L476ZGT6_65,    ///< GPIO 65 [PE12]
        GPIO_STM32L476ZGT6_66,    ///< GPIO 66 [PE13]
        GPIO_STM32L476ZGT6_67,    ///< GPIO 67 [PE14]
        GPIO_STM32L476ZGT6_68,    ///< GPIO 68 [PE15]
        GPIO_STM32L476ZGT6_69,    ///< GPIO 69 [PB10]
        GPIO_STM32L476ZGT6_70,    ///< GPIO 70 [PB11]
        GPIO_STM32L476ZGT6_71,    ///< GPIO 71 [VSS]
        GPIO_STM32L476ZGT6_72,    ///< GPIO 72 [VDD]
        GPIO_STM32L476ZGT6_73,    ///< GPIO 73 [PB12]
        GPIO_STM32L476ZGT6_74,    ///< GPIO 74 [PB13]
        GPIO_STM32L476ZGT6_75,    ///< GPIO 75 [PB14]
        GPIO_STM32L476ZGT6_76,    ///< GPIO 76 [PB15]
        GPIO_STM32L476ZGT6_77,    ///< GPIO 77 [PD8]
        GPIO_STM32L476ZGT6_78,    ///< GPIO 78 [PD9]
        GPIO_STM32L476ZGT6_79,    ///< GPIO 79 [PD10]
        GPIO_STM32L476ZGT6_80,    ///< GPIO 80 [PD11]
        GPIO_STM32L476ZGT6_81,    ///< GPIO 81 [PD12]
        GPIO_STM32L476ZGT6_82,    ///< GPIO 82 [PD13]
        GPIO_STM32L476ZGT6_83,    ///< GPIO 83 [VSS]
        GPIO_STM32L476ZGT6_84,    ///< GPIO 84 [VDD]
        GPIO_STM32L476ZGT6_85,    ///< GPIO 85 [PD14]
        GPIO_STM32L476ZGT6_86,    ///< GPIO 86 [PD15]
        GPIO_STM32L476ZGT6_87,    ///< GPIO 87 [PG2]
        GPIO_STM32L476ZGT6_88,    ///< GPIO 88 [PG3]
        GPIO_STM32L476ZGT6_89,    ///< GPIO 89 [PG4]
        GPIO_STM32L476ZGT6_90,    ///< GPIO 90 [PG5]
        GPIO_STM32L476ZGT6_91,    ///< GPIO 91 [PG6]
        GPIO_STM32L476ZGT6_92,    ///< GPIO 92 [PG7]
        GPIO_STM32L476ZGT6_93,    ///< GPIO 93 [PG8]
        GPIO_STM32L476ZGT6_94,    ///< GPIO 94 [VSS]
        GPIO_STM32L476ZGT6_95,    ///< GPIO 95 [VDDIO2]
        GPIO_STM32L476ZGT6_96,    ///< GPIO 96 [PC6]
        GPIO_STM32L476ZGT6_97,    ///< GPIO 97 [PC7]
        GPIO_STM32L476ZGT6_98,    ///< GPIO 98 [PC8]
        GPIO_STM32L476ZGT6_99,    ///< GPIO 99 [PC9]
        GPIO_STM32L476ZGT6_100,   ///< GPIO 100 [PA8]
        GPIO_STM32L476ZGT6_101,   ///< GPIO 101 [PA9]
        GPIO_STM32L476ZGT6_102,   ///< GPIO 102 [PA10]
        GPIO_STM32L476ZGT6_103,   ///< GPIO 103 [PA11]
        GPIO_STM32L476ZGT6_104,   ///< GPIO 104 [PA12]
        GPIO_STM32L476ZGT6_105,   ///< GPIO 105 [PA13]
        GPIO_STM32L476ZGT6_106,   ///< GPIO 106 [VDDUSB]
        GPIO_STM32L476ZGT6_107,   ///< GPIO 107 [VSS]
        GPIO_STM32L476ZGT6_108,   ///< GPIO 108 [VDD]
        GPIO_STM32L476ZGT6_109,   ///< GPIO 109 [PA14]
        GPIO_STM32L476ZGT6_110,   ///< GPIO 110 [PA15]
        GPIO_STM32L476ZGT6_111,   ///< GPIO 111 [PC10]
        GPIO_STM32L476ZGT6_112,   ///< GPIO 112 [PC11]
        GPIO_STM32L476ZGT6_113,   ///< GPIO 113 [PC12]
        GPIO_STM32L476ZGT6_114,   ///< GPIO 114 [PD0]
        GPIO_STM32L476ZGT6_115,   ///< GPIO 115 [PD1]
        GPIO_STM32L476ZGT6_116,   ///< GPIO 116 [PD2]
        GPIO_STM32L476ZGT6_117,   ///< GPIO 117 [PD3]
        GPIO_STM32L476ZGT6_118,   ///< GPIO 118 [PD4]
        GPIO_STM32L476ZGT6_119,   ///< GPIO 119 [PD5]
        GPIO_STM32L476ZGT6_120,   ///< GPIO 120 [VSS]
        GPIO_STM32L476ZGT6_121,   ///< GPIO 121 [VDD]
        GPIO_STM32L476ZGT6_122,   ///< GPIO 122 [PD6]
        GPIO_STM32L476ZGT6_123,   ///< GPIO 123 [PD7]
        GPIO_STM32L476ZGT6_124,   ///< GPIO 124 [PG9]
        GPIO_STM32L476ZGT6_125,   ///< GPIO 125 [PG10]
        GPIO_STM32L476ZGT6_126,   ///< GPIO 126 [PG11]
        GPIO_STM32L476ZGT6_127,   ///< GPIO 127 [PG12]
        GPIO_STM32L476ZGT6_128,   ///< GPIO 128 [PG13]
        GPIO_STM32L476ZGT6_129,   ///< GPIO 129 [PG14]
        GPIO_STM32L476ZGT6_130,   ///< GPIO 130 [VSS]
        GPIO_STM32L476ZGT6_131,   ///< GPIO 131 [VDDIO2]
        GPIO_STM32L476ZGT6_132,   ///< GPIO 132 [PG15]
        GPIO_STM32L476ZGT6_133,   ///< GPIO 133 [PB3-JTDO-TRACESWO]
        GPIO_STM32L476ZGT6_134,   ///< GPIO 134 [PB4-NJTRST]
        GPIO_STM32L476ZGT6_135,   ///< GPIO 135 [PB5]
        GPIO_STM32L476ZGT6_136,   ///< GPIO 136 [PB6]
        GPIO_STM32L476ZGT6_137,   ///< GPIO 137 [PB7]
        GPIO_STM32L476ZGT6_138,   ///< GPIO 138 [BOOT0]
        GPIO_STM32L476ZGT6_139,   ///< GPIO 139 [PB8]
        GPIO_STM32L476ZGT6_140,   ///< GPIO 140 [PB9]
        GPIO_STM32L476ZGT6_141,   ///< GPIO 141 [PE0]
        GPIO_STM32L476ZGT6_142,   ///< GPIO 142 [PE1]
        GPIO_STM32L476ZGT6_143,   ///< GPIO 143 [VSS]
        GPIO_STM32L476ZGT6_144,   ///< GPIO 144 [VDD] (Maximum)
        GPIO_STM32L476ZGT6_Count  ///< Count
    } GPIO_STM32L476ZGT6_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Mode
     *
     *  @enum GPIO_STM32L476ZGT6_Mode_t
     */
    typedef enum GPIO_STM32L476ZGT6_Mode
    {
        GPIO_STM32L476ZGT6_Mode_Input = 0,          ///< Input (High Impedance)
        GPIO_STM32L476ZGT6_Mode_Output,             ///< Output (Push-Pull)
        GPIO_STM32L476ZGT6_Mode_OutputOpenDrain,    ///< Output (Open-Drain)
        GPIO_STM32L476ZGT6_Mode_Interrupt,          ///< Interrupt (On Change)
        GPIO_STM32L476ZGT6_Mode_InterruptRising,    ///< Interrupt (On Rising)
        GPIO_STM32L476ZGT6_Mode_InterruptFalling,   ///< Interrupt (On Falling)
        GPIO_STM32L476ZGT6_Mode_Event,              ///< Event (On Change)
        GPIO_STM32L476ZGT6_Mode_EventRising,        ///< Event (On Rising)
        GPIO_STM32L476ZGT6_Mode_EventFalling,       ///< Event (On Falling)
        GPIO_STM32L476ZGT6_Mode_Alternate,          ///< Alternate Function (Push-Pull)
        GPIO_STM32L476ZGT6_Mode_AlternateOpenDrain, ///< Alternate Function (Open-Drain)
        GPIO_STM32L476ZGT6_Mode_Analog,             ///< Analog
        GPIO_STM32L476ZGT6_Mode_AnalogADC,          ///< Analog (ADC Controlled)
    } GPIO_STM32L476ZGT6_Mode_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Pull
     *
     *  @enum GPIO_STM32L476ZGT6_Pull_t
     */
    typedef enum GPIO_STM32L476ZGT6_Pull
    {
        GPIO_STM32L476ZGT6_Pull_None = 0, ///< No Pull
        GPIO_STM32L476ZGT6_Pull_Up,       ///< Pull-Up
        GPIO_STM32L476ZGT6_Pull_Down,     ///< Pull-Down
    } GPIO_STM32L476ZGT6_Pull_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Speed
     *
     *  @enum GPIO_STM32L476ZGT6_Speed_t
     */
    typedef enum GPIO_STM32L476ZGT6_Speed
    {
        GPIO_STM32L476ZGT6_Speed_Low = 0,  ///< Low
        GPIO_STM32L476ZGT6_Speed_Medium,   ///< Medium
        GPIO_STM32L476ZGT6_Speed_High,     ///< High
        GPIO_STM32L476ZGT6_Speed_VeryHigh, ///< Very High
    } GPIO_STM32L476ZGT6_Speed_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Function
     *
     *  @enum GPIO_STM32L476ZGT6_Function_t
     */
    typedef enum GPIO_STM32L476ZGT6_Function
    {
        GPIO_STM32L476ZGT6_Function_0 = 0, ///< Function 0 (Minimum)
        GPIO_STM32L476ZGT6_Function_1,     ///<
        GPIO_STM32L476ZGT6_Function_2,     ///<
        GPIO_STM32L476ZGT6_Function_3,     ///<
        GPIO_STM32L476ZGT6_Function_4,     ///<
        GPIO_STM32L476ZGT6_Function_5,     ///<
        GPIO_STM32L476ZGT6_Function_6,     ///<
        GPIO_STM32L476ZGT6_Function_7,     ///<
        GPIO_STM32L476ZGT6_Function_8,     ///<
        GPIO_STM32L476ZGT6_Function_9,     ///<
        GPIO_STM32L476ZGT6_Function_10,    ///<
        GPIO_STM32L476ZGT6_Function_11,    ///<
        GPIO_STM32L476ZGT6_Function_12,    ///<
        GPIO_STM32L476ZGT6_Function_13,    ///<
        GPIO_STM32L476ZGT6_Function_14,    ///<
        GPIO_STM32L476ZGT6_Function_15,    ///< Function 15 (Maximum)
    } GPIO_STM32L476ZGT6_Function_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Value
     */
    typedef enum GPIO_STM32L476ZGT6_Value
    {
        GPIO_STM32L476ZGT6_Value_Low = 0,
        GPIO_STM32L476ZGT6_Value_High,
    } GPIO_STM32L476ZGT6_Value_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Callback Context
     */
    typedef void GPIO_STM32L476ZGT6_CallbackContext_t;

    /**
     *  @brief GPIO STM32L476ZGT6 Callback
     */
    typedef GPIO_STM32L476ZGT6_Status_t( GPIO_STM32L476ZGT6_Callback_t )( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_CallbackContext_t * Context );

    /**
     *  @brief GPIO STM32L476ZGT6 On Interrupt Configuration
     *
     *  @struct GPIO_OnInterrupt_t
     */
    typedef struct GPIO_STM32L476ZGT6_OnInterrupt
    {
        GPIO_STM32L476ZGT6_Callback_t * Callback;
        GPIO_STM32L476ZGT6_CallbackContext_t * Context;
    } GPIO_STM32L476ZGT6_OnInterrupt_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    /**
     *  @brief Initializes specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Initialize( GPIO_STM32L476ZGT6_t GPIOx );

    /**
     *  @brief Cycles specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Cycle( GPIO_STM32L476ZGT6_t GPIOx );

    /**
     *  @brief De-initializes specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_DeInitialize( GPIO_STM32L476ZGT6_t GPIOx );

    /**
     *  @brief Sets on-interrupt callback of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx       GPIO Instance
     *  @param[in] OnInterrupt On Interrupt Configuration
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetOnInterrupt( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_OnInterrupt_t OnInterrupt );

    /**
     *  @brief Sets mode of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *  @param[in] Mode  Mode
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetMode( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Mode_t Mode );

    /**
     *  @brief Sets pull of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *  @param[in] Pull  Pull
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetPull( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Pull_t Pull );

    /**
     *  @brief Sets speed of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *  @param[in] Speed Speed
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetSpeed( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Speed_t Speed );

    /**
     *  @brief Sets function of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *  @param[in] Function Function
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_SetFunction( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Function_t Function );

    /**
     *  @brief Commit settings of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Commit( GPIO_STM32L476ZGT6_t GPIOx );

    /**
     *  @brief Write value to specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in] GPIOx GPIO Instance
     *  @param[in] Value Value
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Write( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Value_t Value );

    /**
     *  @brief Read value of specified GPIO STM32L476ZGT6 Instance
     *
     *  @param[in]  GPIOx GPIO Instance
     *  @param[out] Value Value pointer
     *
     *  @return GPIO_STM32L476ZGT6_Status_t
     */
    GPIO_STM32L476ZGT6_Status_t GPIO_STM32L476ZGT6_Read( GPIO_STM32L476ZGT6_t GPIOx, GPIO_STM32L476ZGT6_Value_t * Value );

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char GPIO_STM32L476ZGT6_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* GPIO_STM32L476ZGT6_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
