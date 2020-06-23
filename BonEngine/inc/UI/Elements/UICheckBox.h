/*****************************************************************//**
 * \file   UICheckBox.h
 * \brief  A UI checkbox.
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
		 * A UI checkbox with check square image and caption.
		 */
		class BON_DLLEXPORT _UICheckBox : public _UIImage
		{
		private:
			// current state
			bool _checked = false;

		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::Checkbox; }

			/**
			 * Caption text element.
			 */
			UIText Caption;

			/**
			 * If true, users can click this radio button again to uncheck it.
			 * If false, users can only select radio but can uncheck them.
			 */
			bool AllowUncheck = true;

			/**
			 * Is this checkbox checked?
			 */
			inline bool Checked() const { return _checked; }

			/**
			 * Set current checkbox value.
			 * 
			 * \param checked True to check checkbox.
			 */
			virtual void SetValue(bool checked);

			/**
			 * Toggle checkbox value.
			 */
			inline void Toggle() { SetValue(!_checked); }

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[checkbox]
			 *				*		- caption_style = Stylesheet to use for checkbox text.
			 *				*		- caption_offset = checkbox text offset (x,y).
			 *				*		- caption_anchor = if provided, will override checkbox's text anchor (x,y).
			 *				*		- allow_uncheck = set if user can uncheck the checkbox.
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