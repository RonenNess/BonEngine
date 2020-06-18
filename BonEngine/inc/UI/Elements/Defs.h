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
#include "../../Framework/RectangleF.h"
#include "../../Framework/Exceptions.h"
#include <functional>
#include <memory>

namespace bon
{
	namespace ui
	{
		// forward declare element base class
		class _UIElement;

		// pointer to an UI element
		typedef BON_DLLEXPORT std::shared_ptr<_UIElement> UIElement;

		/**
		 * Define callback for UI element actions.
		 * First param is element reference, second param is optional additional data.
		 */
		BON_DLLEXPORT typedef std::function<void(_UIElement&, void*)> UICallback;

		/**
		 * Additional data sent with input-related events.
		 */
		struct BON_DLLEXPORT UIInputEvent
		{
			bool LeftMouseDown;
			bool RightMouseDown;
			UIInputEvent(bool leftDown, bool rightDown) : LeftMouseDown(leftDown), RightMouseDown(rightDown) {}
		};

		/**
		 * UI Elements we can create.
		 */
		enum class BON_DLLEXPORT UIElementTypes
		{
			/**
			 * Root element - basically a container that takes whole screen without padding.
			 */
			Root,

			/**
			 * An empty container without graphics.
			 */
			 Container,
			
			 /**
			 * An image element.
			 */
			 Image
		};

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

			/**
			 * Empty constructor
			 */
			UISides()
			{
			}

			/**
			 * Create sides from values.
			 */
			UISides(int left, int right, int top, int bottom) : Left(left), Right(right), Top(top), Bottom(bottom)
			{
			}

			/**
			 * Set from rectangle.
			 */
			void FromRect(const framework::RectangleF& rect)
			{
				Left = (int)rect.X;
				Top = (int)rect.Y;
				Right = (int)rect.Width;
				Bottom = (int)rect.Height;
			}
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

			/**
			 * Load from strings.
			 * Every string value should be number + unit, where unit can be p for pixels or % for percent of parent. 
			 * Examples: "100p", "50%"..
			 */
			void FromStr(const char* x, const char* y)
			{
				// internal buffer for copying
				char buff[16];

				// get x type
				int lenx = strlen(x);
				char tx = x[lenx - 1];
				switch (tx)
				{
				case '%':
					TypeX = UICoordsType::PercentOfParent;
					break;
				case 'p':
					TypeX = UICoordsType::Pixels;
					break;
				default:
					throw framework::AssetLoadError("Invalid format for UI coord X value!");
				}

				// get x value
				memcpy_s(buff, lenx - 1, x, lenx - 1);
				buff[lenx-1] = '\0';
				Value.X = std::atoi(buff);

				// get y type
				int leny = strlen(y);
				char ty = y[leny - 1];
				switch (ty)
				{
				case '%':
					TypeY = UICoordsType::PercentOfParent;
					break;
				case 'p':
					TypeY = UICoordsType::Pixels;
					break;
				default:
					throw framework::AssetLoadError("Invalid format for UI coord Y value!");
				}

				// get y value
				memcpy_s(buff, leny - 1, y, leny - 1);
				buff[leny - 1] = '\0';
				Value.Y = std::atoi(buff);
			}
		};

		/**
		 * Store temporary state while updating UI elements input.
		 */
		struct BON_DLLEXPORT UIUpdateInputState
		{
			// Element we're currently pointing on.
			_UIElement* ElementPointedOn = nullptr;

			// Set to true to capture the input and prevent other elements from recieving the input update.
			bool BreakUpdatesLoop = false;
		};

		/**
		 * UI Element state.
		 */
		enum class BON_DLLEXPORT UIElementState
		{
			// There's no interaction with this element.
			Idle,

			// User points on this element.
			PointedOn,

			// User clicks or somehow interacts with element.
			PressedDown,
			
			// User right-clicks element.
			AltPressedDown,
		};
	}
}