/*****************************************************************//**
 * \file   IUI.h
 * \brief  Define the API for the UI manager class.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "../Assets/Types/Image.h"
#include "../Assets/Types/Config.h"
#include "../Framework/Point.h"
#include "../Framework/Color.h"
#include "../Framework/Rectangle.h"
#include "../Gfx/Sprite.h"
#include "Elements/Defs.h"
#include "Elements/UIElement.h"
#include "Elements/UIImage.h"
#include "Elements/UIText.h"

namespace bon
{
	namespace ui
	{
		using namespace bon::assets;
		using namespace bon::framework;

		/**
		 * Interface for the UI manager.
		 * This manager responsible to draw and manage UI elements.
		 */
		class BON_DLLEXPORT IUI : public IManager
		{
		public:
			/**
			 * Set cursor to render.
			 * 
			 * \param image Cursor image.
			 * \param size Cursor drawing size.
			 * \param offset Cursor image offset from cursor position.
			 */
			virtual void SetCursor(const assets::ImageAsset& image, framework::PointI size, framework::PointI offset) = 0;

			/**
			 * Set cursor to render from sprite.
			 * 
			 * \param sprite Sprite to draw as cursor.
			 */
			virtual void SetCursor(const gfx::Sprite& sprite) = 0;

			/**
			 * Draw cursor, based on what set with SetCursor().
			 */
			virtual void DrawCursor() = 0;

			/**
			 * Draw a UI system or element.
			 * 
			 * \param root Root UI element to draw.
			 * \param drawCursor Set to true to draw cursor (will just call DrawCursor() internally).
			 */
			virtual void Draw(UIElement root, bool drawCursor) = 0;

			/**
			 * Update a UI system and to all interactions.
			 * 
			 * \param root Root UI element to update.
			 */
			virtual void UpdateUI(UIElement root) = 0;
			
			/**
			 * Create and return a new root element.
			 * \return New element pointer.
			 */
			virtual UIElement CreateRoot() = 0;

			/**
			 * Create and return an empty container element.
			 * 
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created empty container.
			 */
			virtual UIElement CreateContainer(const char* stylesheet = nullptr, UIElement parent = nullptr) = 0;

			/**
			 * Create and return an image element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created image.
			 */
			virtual UIImage CreateImage(const char* stylesheet = nullptr, UIElement parent = nullptr) = 0;

			/**
			 * Create and return a text element.
			 *
			 * \param stylesheet Optional stylesheet path to load.
			 * \param parent Optional parent to set.
			 * \return Newly created text.
			 */
			virtual UIText CreateText(const char* stylesheet = nullptr, UIElement parent = nullptr) = 0;

		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "ui"; }
		};
	}
}