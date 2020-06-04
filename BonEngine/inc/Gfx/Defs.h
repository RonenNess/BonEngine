/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc defs and enum related to GFX.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	namespace gfx
	{
		/**
		 * Window modes.
		 */
		enum class BON_DLLEXPORT WindowModes
		{
			Windowed,
			WindowedBorderless,
			Fullscreen,
		};

		/**
		 * Blending modes.
		 */
		enum class BON_DLLEXPORT BlendModes
		{
			// render without any transparency or opacity.
			Opaque = 0,

			// render with alpha channels.
			AlphaBlend = 1,

			// render with additive (lighten) effect.
			Additive = 2,

			// render with mod effect.
			Mod = 3,

			// render with multiply (darken) effect.
			Multiply = 4,

			// blend modes count
			_Count = 5,
		};
	}
}