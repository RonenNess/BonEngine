/*****************************************************************//**
 * \file   IUI.h
 * \brief  Define the API for the UI manager class.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "../Assets/Types/Image.h"
#include "../Framework/Point.h"
#include "../Framework/Color.h"
#include "../Framework/Rectangle.h"

namespace bon
{
	namespace ui
	{
		using namespace bon::assets;
		using namespace bon::framework;

		/**
		 * Interface for the UI manager.
		 * This manager responsible to draw and manage UI elements.
		 */
		class BON_DLLEXPORT IUI : public IManager
		{
		public:


		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "ui"; }
		};
	}
}