/********************************************************************************
 *  File Name:
 *    thor_user_config.hpp
 *
 *  Description:
 *    Enables only the necessary peripherals for configuring Thor
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_THOR_PERIPHERAL_CONFIGURATION_HPP
#define DC_THOR_PERIPHERAL_CONFIGURATION_HPP

/*-------------------------------------------------
Peripheral Support
-------------------------------------------------*/
#define DC_NEED_ADC   0
#define DC_NEED_GPIO  1
#define DC_NEED_SPI   0
#define DC_NEED_INT   1
#define DC_NEED_WDG   0

/*----------------------------------------------
High Level Driver Support
----------------------------------------------*/
#if DC_NEED_ADC
#define THOR_HLD_ADC
#define THOR_LLD_ADC
#endif

#if DC_NEED_GPIO
#define THOR_HLD_GPIO
#define THOR_LLD_GPIO
#endif

#if DC_NEED_INT
#define THOR_HLD_INT
#define THOR_LLD_INT
#endif

#if DC_NEED_SPI
#define THOR_HLD_SPI
#define THOR_LLD_SPI
#endif

#if DC_NEED_WDG
#define THOR_HLD_IWDG
#define THOR_LLD_IWDG
#endif

#ifndef THOR_HLD_CLK
#define THOR_HLD_CLK
#endif

#ifndef THOR_HLD_SYSTEM
#define THOR_HLD_SYSTEM
#endif

/*----------------------------------------------
Low Level Driver Support
----------------------------------------------*/
#ifndef THOR_LLD_DES
#define THOR_LLD_DES
#endif

#ifndef THOR_LLD_EXTI
#define THOR_LLD_EXTI
#endif

#ifndef THOR_LLD_FLASH
#define THOR_LLD_FLASH
#endif

#ifndef THOR_LLD_PWR
#define THOR_LLD_PWR
#endif

#ifndef THOR_LLD_RCC
#define THOR_LLD_RCC
#endif

#ifndef THOR_LLD_SYSCFG
#define THOR_LLD_SYSCFG
#endif

#endif /* !DC_THOR_PERIPHERAL_CONFIGURATION_HPP */
