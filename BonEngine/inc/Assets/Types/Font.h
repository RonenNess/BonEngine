/*****************************************************************//**
 * \file   Font.h
 * \brief  Define a font asset. Used for rendering text.
 *
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include "IAsset.h"
#include "../Defs.h"
#include "FontHandle.h"


namespace bon
{
	namespace assets
	{
		/**
		 * A font asset.
		 * Used to draw text.
		 */
		class _Font : public IAsset
		{
		public:

			/**
			 * Get font handle.
			 *
			 * \return font handle.
			 */
			_FontHandle* Handle() { return (_FontHandle*)_untypedHandle; }

			/**
			 * Get font handle.
			 *
			 * \return font handle.
			 */
			const _FontHandle* Handle() const { return (const _FontHandle*)_untypedHandle; }

			/**
			 * Create the asset.
			 *
			 * \param path Asset's path.
			 */
			_Font(const char* path) : IAsset(path) {
			}

			/**
			 * Return if this asset is properly loaded / valid.
			 */
			virtual bool IsValid() const override
			{
				return _untypedHandle != nullptr && Handle()->IsValid();
			}

			/**
			 * Get asset type.
			 *
			 * \return Asset type identifier.
			 */
			virtual AssetTypes AssetType() const override { return AssetTypes::Font; }

			/**
			 * Get loaded font native size.
			 * 
			 * \return Font size.
			 */
			inline int FontSize() const { return Handle()->FontSize(); }

		};
	}
}