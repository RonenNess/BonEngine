#include <UI/Elements/UIElement.h>
#include <Framework/Exceptions.h>
#include <BonEngine.h>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace bon::framework;

namespace bon
{
	namespace ui
	{
		// add child element
		void _UIElement::AddChild(UIElement child)
		{
			// make sure don't have a parent
			if (child->_parent != nullptr)
			{
				throw framework::InvalidState("Cannot add child element that already have a parent!");
			}

			// add child
			child->_parent = this;
			_children.push_back(child);

			// update dest rect / dirty
			_parentLastDestCalcId = (unsigned long)-1;
			_isDestDirty = true;
			_destCalcId = -1;
		}

		// get filename or path and convert it to a path relative to the folder we loaded stylesheet from.
		std::string _UIElement::ToRelativePath(const char* path) const
		{
			return fs::path(_stylesheetFolder).append(path).u8string();
		}

		// init style from config
		void _UIElement::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// store stylesheet folder
			_stylesheetFolder = fs::path(config->Path()).parent_path().u8string();

			// load origin and anchor
			Origin = config->GetPointF("style", "origin", bon::PointF::Zero);
			_anchor = config->GetPointF("style", "anchor", bon::PointF::Zero);

			// load padding and if should ignore padding
			RectangleF padding = config->GetRectangleF("style", "padding", RectangleF::Zero);
			_padding.FromRect(padding);
			_ignoreParentPadding = config->GetBool("style", "ignore_padding", false);
			
			// load margin
			RectangleF margin = config->GetRectangleF("style", "margin", RectangleF(0, 0, 0, 6));
			Marging.FromRect(margin);

			// load width and height
			const char* width = config->GetStr("style", "width", "100p");
			const char* height = config->GetStr("style", "height", "100p");
			_size.FromStr(width, height);

			// load behavior stuff
			Interactive = config->GetBool("behavior", "interactive", true);
			CaptureInput = config->GetBool("behavior", "capture_input", true);
			CopyParentState = config->GetBool("behavior", "copy_parent_state", false);
			Draggable = config->GetBool("behavior", "draggable", false);
			LimitDragToParentArea = config->GetBool("behavior", "limit_drag_to_parent", true);
			AutoArrangeChildren = config->GetBool("behavior", "auto_arrange_children", false);
			ExemptFromAutoArrange = config->GetBool("behavior", "exempt_auto_arrange", false);
		}

		// remove child element.
		void _UIElement::RemoveChild(UIElement child)
		{
			// make sure its our child
			if (child->_parent != this)
			{
				throw framework::InvalidState("Cannot remove a child element that doesn't belong to the parent!");
			}

			// remove child
			child->_parent = nullptr;
			_children.remove(child);
		}

		// remove self from parent.
		void _UIElement::Remove()
		{
			// make sure got a parent
			if (_parent == nullptr)
			{
				throw framework::InvalidState("Cannot remove an element without parent!");
			}

			// remove self
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			_parent->RemoveChild(tempPtrThatDoesntDelete);
			_parent = nullptr;
		}

		// set if to draw as top layer this element and all its children, recursively.
		void _UIElement::SetDrawAsTopLayerRecursive(bool drawTopLayer)
		{
			DrawAsTopLayer = drawTopLayer;
			for (auto const& child : _children) {
				child->SetDrawAsTopLayerRecursive(drawTopLayer);
			}
		}

		// draw ui element and children.
		void _UIElement::Draw(bool topLayer)
		{
			// skip draw if not visible
			if (!Visible) { return; }

			// draw self
			if (DrawAsTopLayer == topLayer) { 
				DrawSelf(); 
			}

			// draw children
			for (auto child : _children)
			{
				child->Draw(topLayer);
			}
		}

		// update the UI element and children.
		void _UIElement::Update(double deltaTime)
		{
			// skip update if not visible
			if (!Visible) { return; }

			// update self
			// special case - force-active (we need this here too, in case someone blocks our update loop)
			if (ForceActiveState)
			{
				_state = UIElementState::PressedDown;
			}
			// reset states
			else
			{
				_prevState = _state;
				_state = (CopyParentState && _parent) ? _parent->_state : UIElementState::Idle;
			}

			// do self updates
			UpdateSelf(deltaTime); 

			// for auto arrange
			int offsetY = 0;

			// update children
			for (auto child : _children)
			{
				// update child
				child->Update(deltaTime);

				// auto-arrange children
				if (AutoArrangeChildren && !child->ExemptFromAutoArrange)
				{
					offsetY += child->Marging.Top;
					if (child->_anchor.Y != 0)
					{
						child->_anchor.Y = 0;
						child->_isDestDirty = true;
					}
					if (child->_offset.Y != offsetY)
					{
						child->_offset.Y = offsetY;
						child->_isDestDirty = true;
					}
					if (child->_isDestDirty) 
					{
						child->CalcDestRect();
					}
					offsetY += child->GetActualDestRect().Height + child->Marging.Bottom;
				}
			}
		}

		// debug draw element
		void _UIElement::DebugDraw(bool recursive)
		{
			// skip if not visible
			if (!Visible) { return; }

			// draw padding
			RectangleI paddingRect = _destRect;
			paddingRect.X += _padding.Left;
			paddingRect.Width -= _padding.Left + _padding.Right;
			paddingRect.Y += _padding.Top;
			paddingRect.Height -= _padding.Top + _padding.Bottom;
			bon::_GetEngine().Gfx().DrawRectangle(paddingRect, bon::Color(0.5f, 0.5f, 0.5f, 0.5f), false, bon::BlendModes::AlphaBlend);

			// draw dest rect
			bon::_GetEngine().Gfx().DrawRectangle(_destRect, _state == UIElementState::Idle ? Color::White : Color::Red, false, bon::BlendModes::AlphaBlend);

			// draw actual dest rect
			const RectangleI& actualRect = GetActualDestRect();
			if (actualRect != _destRect)
			{
				bon::_GetEngine().Gfx().DrawRectangle(actualRect, Color::Yellow, false, bon::BlendModes::AlphaBlend);
			}

			// draw children
			for (auto child : _children)
			{
				child->DebugDraw(recursive);
			}
		}

		// update ui interactions with input
		void _UIElement::DoInputUpdates(const framework::PointI& mousePosition, UIUpdateInputState& updateState, bool topLayer)
		{
			// skip update if not visible
			if (!Visible) { return; }

			// check if needs to break
			if (updateState.BreakUpdatesLoop) { return; }

			// first update children
			// note: we iterate in reverse to give priority for elements that hide background elements. for example
			// if a button is drawn over an image, we want to first allow the button to run.
			for (auto child = _children.end(); child != _children.begin();)
			{
				--child; // <-- must come here and not in the for line
				(*child)->DoInputUpdates(mousePosition, updateState, topLayer);
				if (updateState.BreakUpdatesLoop) { break; }
			}

			// now update self
			if (!updateState.BreakUpdatesLoop && DrawAsTopLayer == topLayer) {
				DoInputUpdatesSelf(mousePosition, updateState);
			}

			// update children with 'CopyParentState' mode
			for (auto child : _children)
			{
				if (child->CopyParentState) {
					child->_state = _state;
					child->_prevState = _prevState;
				}
			}
		}

		// implement just the drawing of this element.
		void _UIElement::DrawSelf()
		{
			// invoke callback
			if (OnDraw) OnDraw(*this, nullptr);
		}

		// implement just the updating of this element
		void _UIElement::UpdateSelf(double deltaTime)
		{
			// check if need to recalculate dest rect
			if (_isDestDirty || (_parent && _parentLastDestCalcId != _parent->_destCalcId))
			{
				CalcDestRect();
			}
		}
		
		// get drawing color based on element state.
		const framework::Color& _UIElement::GetCurrentStateColor() const
		{
			switch (_state)
			{
			case UIElementState::Idle:
				return Color;
			case UIElementState::PointedOn:
				return ColorHighlight;
			case UIElementState::PressedDown:
				return ColorPressed;
			case UIElementState::AltPressedDown:
				return ColorPressed;
			default:
				return Color;
			}
		}

		// move this element to front
		void _UIElement::MoveToFront()
		{
			// no parent? skip
			if (_parent == nullptr) { return; }

			// already front? skip
			if (&(*_parent->_children.back()) == this) { return; }

			// move to front
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			auto item = std::find(_parent->_children.begin(), _parent->_children.end(), tempPtrThatDoesntDelete);
			_parent->_children.splice(_parent->_children.end(), _parent->_children, item);
		}

		// implement input updates of this element
		void _UIElement::DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
		{
			// not interactive or copying parent? skip
			if (!Interactive || CopyParentState) { return; }

			// check if pointed on
			bool pointedOn = _isBeingDragged || _destRect.Contains(mousePosition);
			if (pointedOn)
			{
				// update state
				updateState.ElementPointedOn = this;
				if (CaptureInput) { updateState.BreakUpdatesLoop = true; }

				// check if down
				_state = UIElementState::PointedOn;
				bool ldown = bon::_GetEngine().Input().Down(KeyCodes::MouseLeft);
				bool rdown = bon::_GetEngine().Input().Down(KeyCodes::MouseRight);
				bool lpressed = bon::_GetEngine().Input().PressedNow(KeyCodes::MouseLeft);
				bool lreleased = bon::_GetEngine().Input().ReleasedNow(KeyCodes::MouseLeft);
				if (ldown) { _state = UIElementState::PressedDown; }
				else if (rdown) { _state = UIElementState::AltPressedDown; }
				
				// invoke events
				if (OnMouseEnter && _prevState == UIElementState::Idle) {
					OnMouseEnter(*this, &UIInputEvent(ldown, rdown));
				}
				if (_prevState != UIElementState::PressedDown && _prevState != UIElementState::AltPressedDown) {
					if (OnMousePressed && (ldown || rdown) && lpressed) { OnMousePressed(*this, &UIInputEvent(ldown, rdown)); } 
				}
				if (_prevState == UIElementState::PressedDown || _prevState == UIElementState::AltPressedDown) {
					if (OnMouseReleased && !ldown && !rdown && lreleased) { OnMouseReleased(*this, &UIInputEvent(ldown, rdown)); }
				}

				// start dragging element
				bool pressedNow = bon::_GetEngine().Input().PressedNow(KeyCodes::MouseLeft);
				if (Draggable && pressedNow)
				{
					_isBeingDragged = true;
				}

				// drag element
				if (Draggable && ldown && _isBeingDragged)
				{
					// set as dragged
					_isBeingDragged = true;

					// set dragging start position
					if (pressedNow)
					{
						_startDragOffsetInElement = framework::PointI(mousePosition.X - _destRect.X, mousePosition.Y - _destRect.Y);
						_anchor = PointF::Zero;
						SetOffset(framework::PointI(_destRect.X, _destRect.Y));
						MoveToFront();
					}
					// drag
					else
					{
						// set position
						SetOffset(framework::PointI(
							mousePosition.X - _startDragOffsetInElement.X - _parentInternalDestRect.X,
							mousePosition.Y - _startDragOffsetInElement.Y - _parentInternalDestRect.Y));

						// check boundaries
						if (LimitDragToParentArea)
						{
							ValidateOffsetInsideParent();
						}
					}
				}
				// no longer dragged
				else
				{
					_isBeingDragged = false;
				}
			}
			// mouse leave event
			if (OnMouseLeave && _state == UIElementState::Idle && _prevState != UIElementState::Idle)
			{
				OnMouseLeave(*this, nullptr);
			}

			// special case - force-active
			if (ForceActiveState)
			{
				_state = UIElementState::PressedDown;
			}
		}

		// make sure element offset is inside parent boundaries
		void _UIElement::ValidateOffsetInsideParent()
		{
			UISides padding;
			if (_parent && !_ignoreParentPadding) { padding = _parent->_padding; }
			if (_offset.X < padding.Left) {
				_offset.X = padding.Left;
			}
			if (_offset.Y < padding.Top) {
				_offset.Y = padding.Top;
			}
			if (_offset.X + _destRect.Width > _parentInternalDestRect.Width) {
				_offset.X = _parentInternalDestRect.Width - _destRect.Width;
			}
			if (_offset.Y + _destRect.Height > _parentInternalDestRect.Height) {
				_offset.Y = _parentInternalDestRect.Height - _destRect.Height;
			}
		}

		// calculate and return coords based on parent, return absolute value in pixels.
		PointI _UIElement::CalcUISize(const UISize& coords, const framework::RectangleI& region, bool addRegionPosition)
		{
			// add position
			PointI ret;
			if (addRegionPosition) 
			{ 
				ret.X += region.X; 
				ret.Y += region.Y; 
			}

			// calc coords X
			switch (coords.WidthType)
			{
			case UISizeType::Pixels:
				ret.X += coords.Width;
				break;

			case UISizeType::PercentOfParent:
				ret.X += (int)((float)(coords.Width / 100.0f) * region.Width);
				break;
			}

			// calc coords Y
			switch (coords.HeightType)
			{
			case UISizeType::Pixels:
				ret.Y += coords.Height;
				break;

			case UISizeType::PercentOfParent:
				ret.Y += (int)((float)(coords.Height / 100.0f) * region.Height);
				break;
			}

			// return coords in absolute value
			return ret;
		}

		// recalc dest rect
		void _UIElement::CalcDestRect()
		{
			// get parent dest rect / region we can draw on
			RectangleI parentRect;
			if (_parent)
			{
				parentRect = _parent->GetCalculatedDestRect();
				if (!_ignoreParentPadding)
				{
					parentRect.X += _parent->_padding.Left;
					parentRect.Width -= _parent->_padding.Left + _parent->_padding.Right;
					parentRect.Y += _parent->_padding.Top;
					parentRect.Height -= _parent->_padding.Top + _parent->_padding.Bottom;
				}
			}
			else
			{
				auto renderSize = bon::_GetEngine().Gfx().RenderableSize();
				parentRect.Set(0, 0, renderSize.X, renderSize.Y);
			}
			_parentInternalDestRect = parentRect;

			// calc position
			_destRect.X = parentRect.X + (int)((float)parentRect.Width * _anchor.X) + _offset.X;
			_destRect.Y = parentRect.Y + (int)((float)parentRect.Height * _anchor.Y) + _offset.Y;

			// calc size
			auto size = CalcUISize(_size, parentRect, false);
			_destRect.Width = size.X;
			_destRect.Height = size.Y;

			// apply origin
			_destRect.X -= (int)((float)_destRect.Width * Origin.X);
			_destRect.Y -= (int)((float)_destRect.Height * Origin.Y);

			// no longer dirty + update calc id
			_isDestDirty = false;
			_destCalcId++;
			if (_parent) { _parentLastDestCalcId = _parent->_destCalcId; }
		}
	}
}