/*****************************************************************//**
 * \file   UIImage.h
 * \brief  A simple UI image.
 *
 * \author Ronen Ness
 * \date   June 2020
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
		 * Simple UI image class.
		 */
		class BON_DLLEXPORT _UIImage : public _UIElement
		{
		public:
			/**
			 * Image to draw.
			 */
			assets::ImageAsset Image;

			/**
			 * Image source rectangle to draw.
			 */
			framework::RectangleI SourceRect;

			/**
			 * Image source rectangle to draw while highlight.
			 */
			framework::RectangleI SourceRectHighlight;

			/**
			 * Image source rectangle to draw while pressed.
			 */
			framework::RectangleI SourceRectPressed;

			/**
			 * Image blend mode.
			 */
			gfx::BlendModes BlendMode;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from base UIElement stylesheet file, you can add the following:
			 *				*	[image]
			 *				*		- image_path = Image path to use.
			 *				*		- color = Image color, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_highlight = Image color, while being pointed on / highlighted, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- color_pressed = Image color, while being pressed down, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- source_rect = Image source rect (x,y,width,height).
			 *				*		- source_rect_highlight = Image source rect while being highlighted / point on (x,y,width,height).
			 *				*		- source_rect_pressed = Image source rect while being pressed down (x,y,width,height).
			 *				*		- blend = Image blend mode (opaque / alpha / additive / mod / multiply).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

		protected:
			/**
			 * Get image source rect based on element state.
			 */
			const framework::RectangleI& GetCurrentStateSourceRect() const;

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf() override;
		};
	}
}

#pragma warning (pop)