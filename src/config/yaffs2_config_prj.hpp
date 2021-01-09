/********************************************************************************
 *  File Name:
 *    yaffs2_config_prj.hpp
 *
 *  Description:
 *    Yaffs configuration
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_YAFFS_CONFIGURATION_HPP
#define DC_YAFFS_CONFIGURATION_HPP

/* Aurora Includes */
#include <Aurora/memory>

/* Chimera Includes */
#include <Chimera/spi>

static constexpr Aurora::Flash::NOR::Chip YAFFS_DEVICE = Aurora::Flash::NOR::Chip::AT25SF081;

#endif  /* !DC_YAFFS_CONFIGURATION_HPP */
