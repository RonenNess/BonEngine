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
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Effect; }
		};
	}
}