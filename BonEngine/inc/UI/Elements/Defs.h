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
		// forward declare element base classes
		class _UIElement;
		class _UIText;
		class _UIImage;
		class _UIWindow;
		class _UIButton;
		class _UIList;

		// pointer to all UI element types
		typedef BON_DLLEXPORT std::shared_ptr<_UIElement> UIElement;
		typedef BON_DLLEXPORT std::shared_ptr<_UIText> UIText;
		typedef BON_DLLEXPORT std::shared_ptr<_UIImage> UIImage;
		typedef BON_DLLEXPORT std::shared_ptr<_UIWindow> UIWindow;
		typedef BON_DLLEXPORT std::shared_ptr<_UIButton> UIButton;
		typedef BON_DLLEXPORT std::shared_ptr<_UIList> UIList;

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
		 * UI text alignment
		 */
		enum class BON_DLLEXPORT UITextAlignment
		{
			Left = 0,
			Right = 1,
			Center = 2
		};		

		/**
		 * UI Size unit types.
		 */
		enum class BON_DLLEXPORT UISizeType
		{
			// Coordinates are in absolute pixels.
			Pixels,

			// Coordinates are relative to parent size.
			PercentOfParent,
		};

		/**
		 * UI Image drawing types.
		 */
		enum class BON_DLLEXPORT UIImageTypes
		{
			// Draw image stretched over the calculated destination rect.
			Stretch,

			// Draw image as tiles that cover the calculated destination rect.
			Tiled,

			// Draw image as a 9-sliced texture with 4 sides, 4 corners, and tiled center.
			Sliced,
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
		 * UI size - represent a UI element size.
		 */
		struct BON_DLLEXPORT UISize
		{
			/**
			 * Width value
			 */
			int Width = 0;

			/**
			 * Height value.
			 */
			int Height = 0;

			/**
			 * Width units type.
			 */
			UISizeType WidthType = UISizeType::Pixels;

			/**
			 * Height units type.
			 */
			UISizeType HeightType = UISizeType::Pixels;

			/**
			 * Create the UI coords.
			 */
			UISize() {}

			/**
			 * Create the UI coords.
			 */
			UISize(int w, UISizeType wtype, int h, UISizeType htype) : Width(w), Height(h), WidthType(wtype), HeightType(htype)
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
					WidthType = UISizeType::PercentOfParent;
					break;
				case 'p':
					WidthType = UISizeType::Pixels;
					break;
				default:
					throw framework::AssetLoadError("Invalid format for UI size width type!");
				}

				// get x value
				memcpy_s(buff, lenx - 1, x, lenx - 1);
				buff[lenx-1] = '\0';
				Width = std::atoi(buff);

				// get y type
				int leny = strlen(y);
				char ty = y[leny - 1];
				switch (ty)
				{
				case '%':
					HeightType = UISizeType::PercentOfParent;
					break;
				case 'p':
					HeightType = UISizeType::Pixels;
					break;
				default:
					throw framework::AssetLoadError("Invalid format for UI size height type!");
				}

				// get y value
				memcpy_s(buff, leny - 1, y, leny - 1);
				buff[leny - 1] = '\0';
				Height = std::atoi(buff);
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