/*****************************************************************//**
 * \file   UIText.h
 * \brief  A UI text paragraph.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "UIElement.h"
#include "../../Assets/Types/Font.h"
#include "../../Assets/Defs.h"
#include "../../Framework/RectangleI.h"
#include "../../Framework/Color.h"
#include "../../Gfx/Defs.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * UI text.
		 */
		class BON_DLLEXPORT _UIText : public _UIElement
		{
		private:

			// text to draw
			char* _text = nullptr;

			// actual calculated bounding box of the ui text.
			framework::RectangleI _actualDestRect;

		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::Text; }

			/**
			 * Font to draw text with.
			 */
			assets::FontAsset Font;

			/**
			 * Text outline color.
			 */
			framework::Color OutlineColor;

			/**
			 * Text outline color while being hightlighted / point on.
			 */
			framework::Color OutlineColorHighlight;

			/**
			 * Text outline color while being pressed on / interacted with.
			 */
			framework::Color OutlineColorPressed;

			/**
			 * Outline width.
			 */
			int OutlineWidth = 2;

			/**
			 * Outline width while being hightlighted / point on.
			 */
			int OutlineWidthHighlight = 2;

			/**
			 * Outline width while being pressed on / interacted with.
			 */
			int OutlineWidthPressed = 2;

			/**
			 * Font drawing size.
			 * Use 0 to use loaded font default.
			 */
			int FontSize = 0;

			/**
			 * If true, will wrap text (break line) if exceed element width.
			 * If false, text can "overflow" out of the element boundaries.
			 */
			bool WordWrap = true;

			/**
			 * Text alignment.
			 */
			UITextAlignment Alignment = UITextAlignment::Left;

			/**
			 * Set text to draw.
			 *
			 * \param text Text to draw.
			 */
			void SetText(const char* text);

			/**
			 * Get text we draw.
			 *
			 * \return Text to draw.
			 */
			const char* GetText() const;

			/**
			 * Get the actual destination rect as calculated by the Update() method.
			 * This would usually be the same as GetCalculatedDestRect(), but might be different for some UI elements.
			 */
			virtual framework::RectangleI GetActualDestRect() const override { return _actualDestRect.CloneWithOffset(_ExtraPixelsOffset); }

			/**
			 * Destroy the text.
			 */
			virtual ~_UIText();

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from base UIElement stylesheet file, you can add the following:
			 *				*	[text]
			 *				*		- font_path = Font path to use.
			 *				*		- font_native_size = Native font size to use when loading font from font path.
			 *				*		- font_size = Font drawing size.
			 *				*		- alignment = Text alignment (left / right / center).
			 *				*		- color = Text color, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_highlight = Text color, while being pointed on / highlighted, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_pressed = Text color, while being pressed down, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- outline_color = Text outline color, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- outline_color_highlight = Text outline color, while being pointed on / highlighted, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- outline_color_pressed = Text outline color, while being pressed down, with values ranging from 0 to 255 (r,g,b,a).
			 * 				*		- outline_width = Text outline width.
			 * 				*		- outline_width_highlight = Text outline width, while being pointed on / highlighted.
			 * 				*		- outline_width_pressed = Text outline width, while being pressed on / interacted with.
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config) override;

			/**
			 * Update the UI element and children.
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void Update(double deltaTime) override;

		protected:

			/**
			 * Draw text or calc actual dest rect.
			 */
			void DrawOrCalcActualRect(bool draw, bool calcActualRect);

			/**
			 * Get outline color based on current state.
			 */
			const framework::Color& GetCurrentStateOutlineColor() const;

			/**
			 * Get outline width based on current state.
			 */
			int GetCurrentStateOutlineWidth() const;

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf() override;
		};
	}
}