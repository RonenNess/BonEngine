/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc UI related defs.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include <memory>

namespace bon
{
	namespace ui
	{
		// forward declare element base class
		class UIElement;

		// pointer to an UI element
		typedef BON_DLLEXPORT std::shared_ptr<UIElement> UIElementPtr;

		/**
		 * Different coordinate modes for UI elements.
		 */
		enum class BON_DLLEXPORT UICoordsType
		{
			// Coordinates are in absolute pixels.
			Pixels,

			// Coordinates are relative to parent size.
			PercentOfParent,
		};

		/**
		 * UI sides - contains values for left, right, top, bottom.
		 */
		struct BON_DLLEXPORT UISides
		{
			int Left = 0;
			int Right = 0;
			int Top = 0;
			int Bottom = 0;
		};

		/**
		 * UI coords - contains point and coords type.
		 */
		struct BON_DLLEXPORT UICoords
		{
			/**
			 * Coordinates value.
			 */
			framework::PointI Value;

			/**
			 * Coordinates type for X value.
			 */
			UICoordsType TypeX = UICoordsType::Pixels;

			/**
			 * Coordinates type for Y value.
			 */
			UICoordsType TypeY = UICoordsType::Pixels;

			/**
			 * Create the UI coords.
			 */
			UICoords() {}

			/**
			 * Create the UI coords.
			 */
			UICoords(int x, UICoordsType xtype, int y, UICoordsType ytype) : Value(x, y), TypeX(xtype), TypeY(ytype)
			{
			}
		};
	}
}