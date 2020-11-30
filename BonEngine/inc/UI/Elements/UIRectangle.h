/*****************************************************************//**
 * \file   UIRectangle.h
 * \brief  A simple UI rectangle shape.
 *
 * \author Ronen Ness
 * \date   November 2020
 *********************************************************************/
#pragma once
#include "UIElement.h"
#include "../../Assets/Types/Image.h"
#include "../../Framework/RectangleI.h"
#include "../../Gfx/Defs.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * Simple UI rectangle shape class.
		 */
		class BON_DLLEXPORT _UIRectangle : public _UIElement
		{
		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::Rectangle; }

			/**
			 * Rectangle blend mode.
			 */
			gfx::BlendModes BlendMode = gfx::BlendModes::AlphaBlend;

			/**
			 * If true, this rectangle will be filled. If false, it will just be outline.
			 */
			bool Filled = true;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from base UIElement stylesheet file, you can add the following:
			 *				*	[rectangle]
			 *				*		- color = Rectangle color, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_highlight = Rectangle color, while being pointed on / highlighted, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_pressed = Rectangle color, while being pressed down, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- blend = Rectangle blend mode (opaque / alpha / additive / mod / multiply).
			 *				*		- filled = If true, will draw filled rectangle. If false, will only draw outline.
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config) override;

		protected:

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf() override;
		};
	}
}

#pragma warning (pop)