/*****************************************************************//**
 * \file   GfxSdlEffects.h
 * \brief  Implement effects (shaders) with SDL / OpenGL.
 *			Special thanks to: https://github.com/AugustoRuiz/sdl2glsl
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <string>
#include <Assets/Defs.h>
#include <Assets/Types/Config.h>
#include <Assets/Types/Effect.h>

struct SDL_Renderer;

namespace bon
{
	namespace gfx
	{
		/**
		 * The gfx effects implementor class.
		 */
		class GfxSdlEffects
		{
		public:

			/**
			 * Initialize the effects manager.
			 */
			void Initialize(SDL_Renderer* renderer);

			/**
			 * Load and return default shader.
			 */
			bon::assets::EffectAsset LoadDefaultProgram();

			/**
			 * Load and return default shader for drawing shapes.
			 */
			bon::assets::EffectAsset LoadDefaultShapesProgram();
		};
	}
}