/*****************************************************************//**
 * \file   UIButton.h
 * \brief  A UI button.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "UIImage.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * A UI button element with background image and caption.
		 */
		class BON_DLLEXPORT _UIButton : public _UIImage
		{
		public:

			/**
			 * Caption text element.
			 */
			UIText Caption;

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[button]
			 *				*		- caption_stylesheet = Stylesheet to use for button text.
			 *				*		- caption_offset = button text offset (x,y).
			 *				*		- caption_anchor = if provided, will override button's text anchor (x,y).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);
		};
	}
}