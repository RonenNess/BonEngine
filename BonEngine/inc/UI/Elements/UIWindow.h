/*****************************************************************//**
 * \file   UIWindow.h
 * \brief  A simple UI image.
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
		 * A UI window with background image and title.
		 */
		class BON_DLLEXPORT _UIWindow : public _UIImage
		{
		public:

			/**
			 * Title text element.
			 */
			UIText Title;

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[window]
			 *				*		- title_stylesheet = Stylesheet to use for title text.
			 *				*		- title_offset = title text offset (x,y).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);
		};
	}
}