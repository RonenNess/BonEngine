/*****************************************************************//**
 * \file   UISlider.h
 * \brief  A horizontal slider element.
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
		 * A UI horizontal slider.
		 */
		class BON_DLLEXPORT _UISlider : public _UIImage
		{
		private:
			// slider handle image.
			UIImage _handle;

			// current value
			int _value = 0;

		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::Slider; }

			/**
			 * Slider max value.
			 */
			int MaxValue = 10;

			/**
			 * Get current slider value.
			 *
			 * \return Slider value.
			 */
			int Value() const { return _value; }

			/**
			 * Set current slider value.
			 * 
			 * \param value New value to set.
			 */
			void SetValue(int value);

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[slider]
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