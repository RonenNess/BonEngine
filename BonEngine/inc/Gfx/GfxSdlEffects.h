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
#include <Gfx/Defs.h>

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
			 * Get current effect handle.
			 */
			void* GetCurrentEffectHandle();

			/**
			 * Set current effect from handle.
			 */
			void SetCurrentEffectFromHandle(void* handle);

			/**
			 * Called when a renderer changes.
			 * You don't need to call this after 'Initialize()', only if you change renderer since init.
			 */
			void UpdateRenderer(SDL_Renderer* renderer);

			/**
			 * Start using the built-in shapes effect.
			 */
			void UseDefaultShapesEffect(bool onlyIfDefault);

			/**
			 * Start using the built-in textures effect.
			 */
			void UseDefaultTexturesEffect(bool onlyIfDefault);

			/**
			 * Start using an effect.
			 */
			void UseEffect(const assets::EffectAsset& effect);

			/**
			 * Set shapes drawing color.
			 */
			void SetShapesColor(const framework::Color& color);

			/**
			 * Stop using effects and restore the default SDL effect.
			 */
			void RestoreDefaultEffect();
			
			/**
			 * Draw texture using currently active effect.
			 */
			void DrawTexture(const SDL_Rect* destRect, const SDL_Rect* sourceRect, SDL_Texture* texture, const framework::Color& color, int textW, int textH, BlendModes blend, int flip);
			
			/**
			 * Draw2 a polygon.
			 */
			void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend);

			/**
			 * Call this after every update frame when it starts.
			 */
			void OnFrameStart();
			
			/**
			 * Update blend mode directly in openGL.
			 */
			void SetBlendMode(BlendModes blend);

		private:

			// active renderer
			SDL_Renderer* _renderer = NULL;

			// default program to restore to after using effect.
			int _defaultProgram = 0;
		};
	}
}