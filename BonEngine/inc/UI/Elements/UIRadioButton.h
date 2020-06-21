/*****************************************************************//**
 * \file   UIRadioButton.h
 * \brief  A UI radio button.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "UICheckBox.h"

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * A UI radio button - like checkbox, but uncheck all siblings when selected.
		 */
		class BON_DLLEXPORT _UIRadioButton : public _UICheckBox
		{
		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::Radio; }

			/**
			 * Set current radio button value.
			 *
			 * \param checked True to check radio button.
			 */
			virtual void SetValue(bool checked) override;
		};
	}
}