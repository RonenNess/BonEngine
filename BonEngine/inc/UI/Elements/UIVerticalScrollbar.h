/*****************************************************************//**
 * \file   UIVerticalScrollbar.h
 * \brief  A vertical scrollbar element.
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
		 * A UI vertical scrollbar.
		 */
		class BON_DLLEXPORT _UIVerticalScrollbar : public _UIImage
		{
		private:
			// scrollbar handle image.
			UIImage _handle;

			// current value
			int _value = 0;

		public:

			/**
			 * Title text element.
			 */
			UIText Title;

			/**
			 * Scrollbar max value.
			 */
			int MaxValue = 10;

			/**
			 * Get current scrollbar value.
			 * 
			 * \return Scrollbar value.
			 */
			int Value() const { return _value; }

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[scrollbar]
			 *				*		- handle_style = Stylesheet to use for handle (image).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

			/**
			 * Update the UI element and children.
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void Update(double deltaTime);
		};
	}
}