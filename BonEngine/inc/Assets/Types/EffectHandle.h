/*****************************************************************//**
 * \file   EffectHandle.h
 * \brief  Define an effect handle.
 *
 * \author Ronen Ness
 * \date   August 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"


namespace bon
{
	namespace assets
	{
		/**
		 * Define the interface for an effect internal handle.
		 * To create new effect asset types, you must implement this API.
		 */
		class BON_DLLEXPORT _EffectHandle
		{
		public:

			/**
			 * Get if this handle is valid.
			 *
			 * \return If effect is valid.
			 */
			virtual bool IsValid() const = 0;

			/**
			 * Get if this effect use textures.
			 *
			 * \return If this effect uses textures
			 */
			virtual bool UseTexture() const = 0;

			/**
			 * Get if this effect use vertex color.
			 *
			 * \return If this effect uses vertex color
			 */
			virtual bool UseVertexColor() const = 0;

			/**
			 * Get the path of the fragment shader file.
			 *
			 * \return Fragment shader file path.
			 */
			virtual const char* FragmentShaderPath() const = 0;

			/**
			 * Get the path of the vertex shader file.
			 *
			 * \return Vertex shader file path.
			 */
			virtual const char* VertexShaderPath() const = 0;

			/**
			 * Get if should flip texture coords on Y axis.
			 *
			 * \return If should flip texture coords v.
			 */
			virtual bool FlipTextureCoordsV() const = 0;
		};
	}
}