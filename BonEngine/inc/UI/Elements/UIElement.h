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
			// stylesheet folder, if loaded from stylesheet file
			std::string _stylesheetFolder;

			// element offset from its anchor position.
			framework::PointI _offset;

			// element position relative to its parent dest rect: 0,0 will position element at parent top-left corner, 1,1 at bottom right.
			framework::PointF _anchor;

			// element size.
			UISize _size;

			// internal padding
			UISides _padding;

			// is this element being dragged right now?
			bool _isBeingDragged = false;

			// do we need to recalculate dest rect?
			bool _isDestDirty = true;

			// every time we recalculate dest rect this increases by 1.
			unsigned long _destCalcId = 0;

			// last known parent dest id. if changes, we need to update ourselves as well
			unsigned long _parentLastDestCalcId = (unsigned long)-1; 

			// start dragging offset, if element is being dragged
			framework::PointI _startDragOffsetInElement;

			// if true, will ignore parent padding
			bool _ignoreParentPadding = false;

			// child elements.
			std::list<UIElement> _children;

			// store column data
			struct ColumnData
			{
				UIAlignment Alignment;
				UIElement Column;
			};

			// columns under this element
			std::list<ColumnData> _columns;
		
		protected:

			// parent ui element.
			_UIElement* _parent = nullptr;

			// element state
			UIElementState _state = UIElementState::Idle;
			
			// element previous state
			UIElementState _prevState = UIElementState::Idle;

		private:

			// element calculated dest rect (based on position and size)
			framework::RectangleI _destRect;

			// last calculated parent internal dest rect
			framework::RectangleI _parentInternalDestRect;

		public:

			/**
			 * Get all children's list.
			 */
			inline const std::list<UIElement>& GetChildren() { return _children; }

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const { return UIElementType::Element; }

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() {}

			/**
			 * If true, will automatically arrange children every frame based on their actual dest rect.
			 */
			bool AutoArrangeChildren = false;

			/**
			 * If parent `AutoArrangeChildren` is true but this flag is also true, will skip this element when auto arranging.
			 */
			bool ExemptFromAutoArrange = false;

			/**
			 * If true, this element will interact with user input, respond to clicks, ect.
			 * If false, its merely a graphical entity and non of the event callbacks will be triggered.
			 * Note: even if an element is not interactive, its children may still be and can respond to events (and vice versa).
			 */
			bool Interactive = true;

			/**
			 * If true, this element will capture input events and won't allow them to propagate to parent and siblings.
			 * For example, if user clicks on the element, any elements behind it will not recieve the click.
			 * If false, this element allow input to go through it, triggering both it and anything behind it.
			 */
			bool CaptureInput = true;

			/**
			 * If true, this element will just copy its parent state - if mouse points on parent, it will behave like mouse points on it,
			 * If user clicks parent - it will behave like its being clicked. This will affect the graphical aspects of the element, but will
			 * not trigger any events. If you set this to true, don't bother registering to events register to parent instead.
			 * Note: this is useful for stuff like text that's attached to buttons - you want text to appear as active the same time as background button.
			 */
			bool CopyParentState = false;

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
			 * Allow user to attach custom data to this element.
			 */
			void* UserData = nullptr;

			/**
			 * Can the user drag this element around?
			 */
			bool Draggable = false;

			/**
			 * Adds margin around element sides when auto-arranging elements.
			 * This property is not used when element is not being auto-arranged.
			 */
			UISides Marging;

			/**
			 * Get if this element is being dragged right now.
			 * 
			 * \return True if element is currently being dragged.
			 */
			inline bool IsBeingDragged() const { return _isBeingDragged; }

			/**
			 * If true and element is draggable, user will not be able to drag it outside its parent region.
			 */
			bool LimitDragToParentArea = true;

			/**
			 * Set if to draw as top layer this element and all its children, recursively.
			 */
			virtual void SetDrawAsTopLayerRecursive(bool drawTopLayer);

			/**
			 * Set if we want to ignore parent's padding.
			 * 
			 * \param ignore If true, will ignore parent padding.
			 */
			inline void IgnoreParentPadding(bool ignore) { _ignoreParentPadding = ignore; MarkAsDirty(); }

			/**
			 * Initialize element style from config file.
			 * 
			 * \param config Config file to init element from.
			 *				* config may contain the following sections:
			 *				*	[style]
			 *				*		- width = Element width + unit (p for pixels, % for percent of parent. for example: "100%" or "40p").
			 *				*		- height = Element height + unit (p for pixels, % for percent of parent. for example: "100%" or "40p").
			 *				*		- padding = Element padding (left, top, right, bottom).
			 *				*		- margin = Element margin (left, top, right, bottom).
			 *				*		- origin = Element origin (x,y).
			 *				*		- anchor = Element anchor - its position relative to parent bounding box (x,y).
			 *				*		- ignore_padding = If true, will ignore parent's padding (true / false).
			 *				*
			 *				*	[behavior]
			 *				*		- interactive = Is this element interactive? (true / false).
			 *				*		- capture_input = Will this element capture input events? (true / false). 
			 *				*		- copy_parent_state = Will this element copy its parent state? (true / false). 
			 *				*		- draggable = If true, users can drag this element (true / false). 
			 *				*		- limit_drag_to_parent = If true, will limit dragging to parent's region (true / false). 
			 *				*		- auto_arrange_children = If true, will auto-arrange children based on actual dest rects (true / false). 
			 *				*		- exempt_auto_arrange = If true, will ignore parent's auto arrange (true / false). 
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

			/**
			 * If true, this element will remain "stuck" in active state, as if user is constantly pressing it.
			 */
			bool ForceActiveState = false;

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
			 * If true, will draw this element on top layer, above other elements.
			 */
			bool DrawAsTopLayer = false;

			/**
			 * Mark dest rect as dirty.
			 */
			inline void MarkAsDirty() { _isDestDirty = true; }

			/**
			 * Set element offset from its anchor position.
			 */
			inline void SetOffset(const framework::PointI& offset) { if (_offset != offset) { _offset = offset; MarkAsDirty(); } }
			
			/**
			 * Get element position.
			 */
			inline const framework::PointI& GetOffset() const { return _offset; }

			/**
			 * Set element anchor.
			 * Anchor position the element relative to its parent bounding box.
			 */
			inline void SetAnchor(const framework::PointF& anchor) { _anchor = anchor; MarkAsDirty(); }

			/**
			 * Get element anchor.
			 * Anchor position the element relative to its parent bounding box.
			 */
			inline const framework::PointF& GetAnchor() const { return _anchor; }

			/**
			 * Set element size.
			 */
			inline void SetSize(const UISize& size) { _size = size; MarkAsDirty(); }

			/**
			 * Set element width to be 100% of its parent.
			 */
			inline void SetWidthToMax() { _size.Width = 100; _size.WidthType = UISizeType::PercentOfParent; MarkAsDirty(); }

			/**
			 * Set element height to be 100% of its parent.
			 */
			inline void SetHeightToMax() { _size.Height = 100; _size.HeightType = UISizeType::PercentOfParent; MarkAsDirty(); }

			/**
			 * Set element size as pixels.
			 */
			inline void SetSizeInPixels(framework::PointI size) { SetSize(UISize(size.X, UISizeType::Pixels, size.Y, UISizeType::Pixels)); }

			/**
			 * Set element size as percents of parent.
			 */
			inline void SetSizeInPercents(framework::PointI size) { SetSize(UISize(size.X, UISizeType::PercentOfParent, size.Y, UISizeType::PercentOfParent)); }

			/**
			 * Get element size.
			 */
			inline const UISize& GetSize() const { return _size; }

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
			 * 
			 * \param topLayer Set to true to only draw top layer elements.
			 */
			virtual void Draw(bool topLayer);

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
			 * \param topLayer True when we update top layer elements.
			 */
			virtual void DoInputUpdates(const framework::PointI& mousePosition, UIUpdateInputState& updateState, bool topLayer);

			/**
			 * Move this element to front inside its parent.
			 * If have no parent or already the most front element - nothing will happen.
			 */
			void MoveToFront();

			/**
			 * Debug draw UI related stuff like dest rects and paddings.
			 * Used to debug purposes. Call this only after you call all necessary updates.
			 * 
			 * \param recursive If true, will debug draw children as well recursively.
			 */
			void DebugDraw(bool recursive = true);

			/**
			 * Get the last dest rect we calculated.
			 * Note: may be outdated if actions were done without calling CalcDestRect() or Update().
			 * Sometimes you need to Update() parent too.
			 */
			inline framework::RectangleI GetCalculatedDestRect() const { return _destRect.CloneWithOffset(_ExtraPixelsOffset); }

			/**
			 * Get the actual destination rect as calculated by the Update() method.
			 * This would usually be the same as GetCalculatedDestRect(), but might be different for some UI elements.
			 */
			virtual framework::RectangleI GetActualDestRect() const { return _destRect.CloneWithOffset(_ExtraPixelsOffset); }

			/**
			 * Make sure element offset is inside is parent boundaries (takes element width and height into consideration).
			 */
			void ValidateOffsetInsideParent();

			/**
			 * Extra offset to add to dest rect in pixels, used internally.
			 */
			framework::PointI _ExtraPixelsOffset;

			/**
			 * Create an internal column container inside this element, which scales and position itself automatically.
			 * For example, if you create 3 columns aligned left with widths of 100, 200, and 300, these columns offset would be
			 * 100px, 200px and 300px accordingly.
			 *
			 * Don't try to play with columns offset and size, as these are set automatically every update.
			 *
			 * \param stylesheet Stylesheet for column.
			 * \param width Column width.
			 * \param widthType Column width type.
			 * \param alignment Which side of the element to stick the column to.
			 * \return New element used as column. Use RemoveChild() to remove it.
			 */
			UIElement CreateColumn(const char* stylesheet, int width, UISizeType widthType = UISizeType::Pixels, UIAlignment alignment = UIAlignment::Left);

		protected:

			/**
			 * Get filename or path and convert it to a path relative to the folder we loaded stylesheet from.
			 */
			std::string ToRelativePath(const char* path) const;

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
			framework::PointI CalcUISize(const UISize& coords, const framework::RectangleI& region, bool addRegionPosition);

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

			/**
			 * Update columns under this element.
			 */
			void UpdateColumns();
		};
	}
}

#pragma warning (pop)