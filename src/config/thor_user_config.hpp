/********************************************************************************
 *  File Name:
 *    thor_user_config.hpp
 *
 *  Description:
 *    Enables only the necessary peripherals for configuring Thor
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_THOR_PERIPHERAL_CONFIGURATION_HPP
#define DC_THOR_PERIPHERAL_CONFIGURATION_HPP

/*----------------------------------------------
High Level Driver Support
----------------------------------------------*/
#ifndef THOR_HLD_ADC
#define THOR_HLD_ADC
#endif

#ifndef THOR_HLD_CLK
#define THOR_HLD_CLK
#endif

#ifndef THOR_HLD_GPIO
#define THOR_HLD_GPIO
#endif

#ifndef THOR_HLD_SPI
#define THOR_HLD_SPI
#endif

#ifndef THOR_HLD_SYSTEM
#define THOR_HLD_SYSTEM
#endif

/*----------------------------------------------
Low Level Driver Support
----------------------------------------------*/
#ifndef THOR_LLD_ADC
#define THOR_LLD_ADC
#endif

#ifndef THOR_LLD_EXTI
#define THOR_LLD_EXTI
#endif

#ifndef THOR_LLD_FLASH
#define THOR_LLD_FLASH
#endif

#ifndef THOR_LLD_GPIO
#define THOR_LLD_GPIO
#endif

#ifndef THOR_LLD_IT
#define THOR_LLD_IT
#endif

#ifndef THOR_LLD_PWR
#define THOR_LLD_PWR
#endif

#ifndef THOR_LLD_RCC
#define THOR_LLD_RCC
#endif

#ifndef THOR_LLD_SPI
#define THOR_LLD_SPI
#endif

#ifndef THOR_LLD_SYSCFG
#define THOR_LLD_SYSCFG
#endif

#endif /* !DC_THOR_PERIPHERAL_CONFIGURATION_HPP */
