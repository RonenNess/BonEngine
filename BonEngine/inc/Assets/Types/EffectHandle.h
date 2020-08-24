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

			/**
			 * Set float uniform.
			 */
			virtual void SetUniformFloat(const char* name, float value) = 0;

			/**
			 * Set vector2 uniform.
			 */
			virtual void SetUniformVector2(const char* name, float x, float y) = 0;

			/**
			 * Set vector3 uniform.
			 */
			virtual void SetUniformVector3(const char* name, float x, float y, float z) = 0;

			/**
			 * Set vector4 uniform.
			 */
			virtual void SetUniformVector4(const char* name, float x, float y, float z, float w) = 0;

			/**
			 * Set float uniform.
			 */
			virtual void SetUniformInt(const char* name, int value) = 0;

			/**
			 * Set vector2 uniform.
			 */
			virtual void SetUniformVector2(const char* name, int x, int y) = 0;

			/**
			 * Set vector3 uniform.
			 */
			virtual void SetUniformVector3(const char* name, int x, int y, int z) = 0;

			/**
			 * Set vector4 uniform.
			 */
			virtual void SetUniformVector4(const char* name, int x, int y, int z, int w) = 0;

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix2(const char* name, int count, bool transpose, const float* values) = 0;

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix3(const char* name, int count, bool transpose, const float* values) = 0;

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix4(const char* name, int count, bool transpose, const float* values) = 0;
		};
	}
}