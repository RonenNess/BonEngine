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

namespace bon
{
	namespace assets
	{
		/**
		 * Define the interface for a font internal handle.
		 * To create new font asset types, you must implement this API.
		 */
		class DLLEXPORT _FontHandle
		{
		public:
			/**
			 * Loaded font (implementation dependent).
			 */
			void* Font = nullptr;

			/**
			 * Get if this handle is valid.
			 *
			 * \return If font is valid.
			 */
			virtual bool IsValid() const { return Font != nullptr; }

			/**
			 * Get loaded font native size.
			 *
			 * \return Font size.
			 */
			virtual int FontSize() const = 0;
		};
	}
}