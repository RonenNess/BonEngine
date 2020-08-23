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
#include <Framework/RectangleF.h>
#include <Framework/Color.h>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

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
			 * Called when a renderer changes.
			 * You don't need to call this after 'Initialize()', only if you change renderer since init.
			 */
			void UpdateRenderer(SDL_Renderer* renderer);

			/**
			 * Start using an effect.
			 */
			void UseEffect(const assets::EffectAsset& effect);

			/**
			 * Stop using effects and restore the default SDL effect.
			 */
			void RestoreDefaultEffect();
			
			/**
			 * Draw texture using currently active effect.
			 */
			void DrawTexture(const SDL_Rect* destRect, const SDL_Rect* sourceRect, SDL_Texture* texture, const framework::Color& color, int textW, int textH);

			/**
			 * Call this after every update frame when it starts.
			 */
			void OnFrameStart();

		private:

			// active renderer
			SDL_Renderer* _renderer;

			// default program to restore to after using effect.
			int _defaultProgram;

			// currently active effect
			assets::EffectAsset _effect;
		};
	}
}