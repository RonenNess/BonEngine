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

			// active part overlay to mark the parts of the slider which are selected
			UIImage _activePartOverlay;

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
			int MaxValue = 9;

			/**
			 * Get current slider value.
			 *
			 * \return Slider value.
			 */
			int GetValue() const { return _value; }

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
			 *				*		- active_slider_rect = Optional source rectangle for an overlay part that covers the active part of the slider (x,y,w,h).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);
		
		protected:

			/**
			 * Do input updates to interact with element of this specific element.
			 * This happens after the regular updates.
			 *
			 * \param mousePosition Mouse position to test.
			 * \param updateState Contains temporary state about UI input updates.
			 */
			virtual void DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState) override;

		};
	}
}