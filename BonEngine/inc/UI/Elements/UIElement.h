/*****************************************************************//**
 * \file   UIElement.h
 * \brief  Define a basic UI element class.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "Defs.h"
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include "../../Assets/Types/Config.h"
#include "../../Framework/Rectangle.h"
#include "../../Framework/Color.h"
#include "../../Assets/Types/Config.h"
#include "../../Assets/Defs.h"
#include <list>


#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

namespace bon
{
	namespace ui
	{
		/**
		 * Base UI element class.
		 */
		class BON_DLLEXPORT _UIElement
		{
		private:
			// element position.
			UICoords _position;

			// element size.
			UICoords _size;

			// child elements.
			std::list<UIElement> _children;

			// internal padding
			UISides _padding;

			// parent ui element.
			_UIElement* _parent = nullptr;

			// do we need to recalculate dest rect?
			bool _isDestDirty = true;

			// every time we recalculate dest rect this increases by 1.
			unsigned long _destCalcId = 0;

			// last known parent dest id. if changes, we need to update ourselves as well
			unsigned long _parentLastDestCalcId = (unsigned long)-1; 

		protected:
			// element state
			UIElementState _state = UIElementState::Idle;
			
			// element previous state
			UIElementState _prevState = UIElementState::Idle;

			// element calculated dest rect (based on position and size)
			framework::RectangleI _destRect;

		public:

			/**
			 * Callback for mouse press.
			 * Additional param will be UIInputEvent instance. Don't delete it.
			 */
			UICallback OnMousePressed;

			/**
			 * Callback for mouse release.
			 * Additional param will be UIInputEvent instance. Don't delete it.
			 */
			UICallback OnMouseReleased;

			/**
			 * Callback for mouse enter.
			 * Additional param will be UIInputEvent instance. Don't delete it.
			 */
			UICallback OnMouseEnter;

			/**
			 * Callback for mouse leave.
			 * Additional param will be null.
			 */
			UICallback OnMouseLeave;

			/**
			 * Callback for before drawing.
			 * Additional param will be null.
			 */
			UICallback OnDraw;

			/**
			 * Callback for value change.
			 * Additional param will be null.
			 */
			UICallback OnValueChange;

			/**
			 * Is this UI element currently visible?
			 * Note: also affect children.
			 */
			bool Visible = true;

			/**
			 * Initialize element style from config file.
			 * 
			 * \param config Config file to init element from.
			 *				* config must contain the following section:
			 *				*	[style]
			 *				*		- width = Element width + unit (p for pixels, % for percent of parent. for example: "100%" or "40p").
			 *				*		- height = Element height + unit (p for pixels, % for percent of parent. for example: "100%" or "40p").
			 *				*		- padding = Element padding (left, top, right, bottom).
			 *				*		- origin = Element origin (x,y).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

			/**
			 * Element origin, relative to dest rect size.
			 */
			framework::PointF Origin;

			/**
			 * Element drawing color.
			 */
			framework::Color Color;

			/**
			 * Element drawing color while being hightlighted / point on.
			 */
			framework::Color ColorHighlight;

			/**
			 * Element drawing color while being pressed on / interacted with.
			 */
			framework::Color ColorPressed;

			/**
			 * Mark dest rect as dirty.
			 */
			inline void MarkAsDirty() { _isDestDirty = true; }

			/**
			 * Set element position.
			 */
			inline void SetPosition(UICoords position) { _position = position; MarkAsDirty(); }
			
			/**
			 * Set element position as pixels.
			 */
			inline void SetPosition(framework::PointI position) { SetPosition(UICoords(position.X, UICoordsType::Pixels, position.Y, UICoordsType::Pixels)); }

			/**
			 * Get element position.
			 */
			inline const UICoords& GetPosition() const { return _position; }

			/**
			 * Set element size.
			 */
			inline void SetSize(UICoords size) { _size = size; MarkAsDirty(); }
			
			/**
			 * Set element size as pixels.
			 */
			inline void SetSize(framework::PointI size) { SetSize(UICoords(size.X, UICoordsType::Pixels, size.Y, UICoordsType::Pixels)); }

			/**
			 * Get element size.
			 */
			inline const UICoords& GetSize() const { return _size; }

			/**
			 * Set internal padding.
			 */
			inline void SetPadding(UISides padding) { _padding = padding; MarkAsDirty(); }

			/**
			 * Get internal padding.
			 */
			inline const UISides& GetPadding() const { return _padding; }

			/**
			 * Get parent element.
			 * 
			 * \return Parent element, or null.
			 */
			inline const _UIElement* Parent() const { return _parent; }

			/**
			 * Add child element.
			 * 
			 * \param child Element to add.
			 */
			void AddChild(UIElement child);

			/**
			 * Remove child element.
			 * 
			 * \param child Element to remove.
			 */
			void RemoveChild(UIElement child);

			/**
			 * Remove self from parent.
			 */
			void Remove();

			/**
			 * Draw ui element and children.
			 */
			virtual void Draw();

			/**
			 * Update the UI element and children.
			 * 
			 * \param deltaTime Update frame delta time.
			 */
			virtual void Update(double deltaTime);

			/**
			 * Do input updates to interact with element.
			 * This happens after the regular updates.
			 *
			 * \param mousePosition Mouse position to test.
			 * \param updateState Contains temporary state about UI input updates.
			 */
			virtual void DoInputUpdates(const framework::PointI& mousePosition, UIUpdateInputState& updateState);

		protected:

			/**
			 * Get drawing color based on element state.
			 */
			const framework::Color& GetCurrentStateColor() const;

			/**
			 * Recalculate destination rect.
			 */
			void CalcDestRect();

			/**
			 * Calculate and return coords based on parent, return absolute value in pixels.
			 */
			framework::PointI CalcCoords(const UICoords& coords, const framework::RectangleI& region, bool addRegionPosition);

			/**
			 * Get the last dest rect we calculated.
			 * Note: may be outdated if actions were done without calling CalcDestRect() or Update(). 
			 * Sometimes you need to Update() parent too.
			 */
			inline const framework::RectangleI& GetCalculatedDestRect() const { return _destRect; }

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf();

			/**
			 * Do input updates to interact with element of this specific element.
			 * This happens after the regular updates.
			 *
			 * \param mousePosition Mouse position to test.
			 * \param updateState Contains temporary state about UI input updates.
			 */
			virtual void DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState);

			/**
			 * Implement just the updating of this element
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void UpdateSelf(double deltaTime);
		};
	}
}

#pragma warning (pop)