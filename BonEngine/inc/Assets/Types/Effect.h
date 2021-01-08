/*****************************************************************//**
 * \file   Effect.h
 * \brief  Define an effect asset. Used for rendering.
 *
 * \author Ronen Ness
 * \date   August 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include "../../Framework/Color.h"
#include "../../Framework/Rectangle.h"
#include "IAsset.h"
#include "../Defs.h"
#include "EffectHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * An Effect asset.
		 * Applied when drawing textures to make special rendering effects.
		 * For example, you can implement an effect to draw everything in grayscale.
		 */
		class BON_DLLEXPORT _Effect : public IAsset
		{
		public:

			/**
			 * Get effect handle.
			 *
			 * \return Effect handle.
			 */
			inline _EffectHandle* Handle() { return (_EffectHandle*)_untypedHandle; }

			/**
			 * Get effect handle.
			 *
			 * \return Effect handle.
			 */
			inline const _EffectHandle* Handle() const { return (const _EffectHandle*)_untypedHandle; }

			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Effect(const char* path);

			/**
			 * Create the effect from handle.
			 * 
			 * \param handle Effect handle.
			 */
			_Effect(_EffectHandle* handle) { _SetHandle(handle); }

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const override
			{
				return _untypedHandle != nullptr && Handle()->IsValid();
			}

			/**
			 * Return if this effect uses textures.
			 * 
			 * \return True if effect uses textures.
			 */
			bool UseTextures() const
			{
				return Handle()->UseTexture();
			}

			/**
			 * Return if this effect uses vertex color.
			 *
			 * \return True if effect uses vertex color.
			 */
			bool UseVertexColor() const
			{
				return Handle()->UseVertexColor();
			}

			/**
			 * Return if this effect flips texture coords on Y axis.
			 *
			 * \return True if effect flips texture.
			 */
			bool FlipTextureCoordsV() const
			{
				return Handle()->FlipTextureCoordsV();
			}

			/**
			 * Return if this effect uses a texture.
			 *
			 * \return True if effect uses a texture.
			 */
			bool UseTexture() const
			{
				return Handle()->UseTexture();
			}

			/**
			 * Set float uniform.
			 */
			void SetUniformFloat(const char* name, float value)
			{
				ValidateActive();
				Handle()->SetUniformFloat(name, value);
			}

			/**
			 * Set vector2 uniform.
			 */
			void SetUniformVector2(const char* name, float x, float y)
			{
				ValidateActive();
				Handle()->SetUniformVector2(name, x, y);
			}

			/**
			 * Set vector3 uniform.
			 */
			void SetUniformVector3(const char* name, float x, float y, float z)
			{
				ValidateActive();
				Handle()->SetUniformVector3(name, x, y, z);
			}

			/**
			 * Set vector4 uniform.
			 */
			void SetUniformVector4(const char* name, float x, float y, float z, float w)
			{
				ValidateActive();
				Handle()->SetUniformVector4(name, x, y, z, w);
			}

			/**
			 * Set int uniform.
			 */
			void SetUniformInt(const char* name, int value)
			{
				ValidateActive();
				Handle()->SetUniformInt(name, value);
			}

			/**
			 * Set vector2 uniform.
			 */
			void SetUniformVector2(const char* name, int x, int y)
			{
				ValidateActive();
				Handle()->SetUniformVector2(name, x, y);
			}

			/**
			 * Set vector3 uniform.
			 */
			void SetUniformVector3(const char* name, int x, int y, int z)
			{
				ValidateActive();
				Handle()->SetUniformVector3(name, x, y, z);
			}

			/**
			 * Set vector4 uniform.
			 */
			void SetUniformVector4(const char* name, int x, int y, int z, int w)
			{
				ValidateActive();
				Handle()->SetUniformVector4(name, x, y, z, w);
			}

			/**
			 * Set color uniform.
			 */
			void SetUniformColor(const char* name, const bon::framework::Color& color, bool includeAlpha)
			{
				ValidateActive();
				if (includeAlpha)
				{
					SetUniformVector4(name, color.R, color.G, color.B, color.A);
				}
				else
				{
					SetUniformVector3(name, color.R, color.G, color.B);
				}
			}

			/**
			 * Set a matrix uniform.
			 */
			void SetUniformMatrix2(const char* name, int count, bool transpose, const float* values)
			{
				ValidateActive();
				Handle()->SetUniformMatrix2(name, count, transpose, values);
			}

			/**
			 * Set a matrix uniform.
			 */
			void SetUniformMatrix3(const char* name, int count, bool transpose, const float* values)
			{
				ValidateActive();
				Handle()->SetUniformMatrix2(name, count, transpose, values);
			}

			/**
			 * Set a matrix uniform.
			 */
			void SetUniformMatrix4(const char* name, int count, bool transpose, const float* values)
			{
				ValidateActive();
				Handle()->SetUniformMatrix2(name, count, transpose, values);
			}

			/**
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Effect; }

		private:

			/**
			* Make sure this effect is valid before setting uniforms.
			* If effect is not active, throw exception.
			*/
			void ValidateActive() const;
		};
	}
}