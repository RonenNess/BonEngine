#include <UI/Elements/UIElement.h>
#include <Framework/Exceptions.h>
#include <BonEngine.h>

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

		// init style from config
		void _UIElement::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load origin
			Origin = config->GetPointF("style", "origin", bon::PointF::Zero);

			// load padding
			RectangleF padding = config->GetRectangleF("style", "padding", RectangleF::Zero);
			_padding.FromRect(padding);

			// load width and height
			const char* width = config->GetStr("style", "width", "100p");
			const char* height = config->GetStr("style", "height", "100p");
			_size.FromStr(width, height);
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

		// draw ui element and children.
		void _UIElement::Draw()
		{
			// skip draw if not visible
			if (!Visible) { return; }

			// draw self
			DrawSelf();

			// draw children
			for (auto child : _children)
			{
				child->Draw();
			}
		}

		// update the UI element and children.
		void _UIElement::Update(double deltaTime)
		{
			// skip update if not visible
			if (!Visible) { return; }

			// reset states
			_prevState = _state;
			_state = UIElementState::Idle;

			// update self
			UpdateSelf(deltaTime);

			// update children
			for (auto child : _children)
			{
				child->Update(deltaTime);
			}
		}

		// update ui interactions with input
		void _UIElement::DoInputUpdates(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
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
				(*child)->DoInputUpdates(mousePosition, updateState);
				if (updateState.BreakUpdatesLoop) { return; }
			}

			// now update self
			DoInputUpdatesSelf(mousePosition, updateState);
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

		// implement input updates of this element
		void _UIElement::DoInputUpdatesSelf(const framework::PointI& mousePosition, UIUpdateInputState& updateState)
		{
			// check if pointed on
			bool pointedOn = _destRect.Contains(mousePosition);
			if (pointedOn)
			{
				// update state
				updateState.ElementPointedOn = this;
				updateState.BreakUpdatesLoop = true;

				// check if down
				_state = UIElementState::PointedOn;
				bool ldown = bon::_GetEngine().Input().Down(KeyCodes::MouseLeft);
				bool rdown = bon::_GetEngine().Input().Down(KeyCodes::MouseRight);
				if (ldown) { _state = UIElementState::PressedDown; }
				else if (rdown) { _state = UIElementState::AltPressedDown; }
				
				// invoke events
				if (OnMouseEnter && _prevState == UIElementState::Idle) {
					OnMouseEnter(*this, &UIInputEvent(ldown, rdown));
				}
				if (_prevState != UIElementState::PressedDown && _prevState != UIElementState::AltPressedDown) {
					if (OnMousePressed && (ldown || rdown)) { OnMousePressed(*this, &UIInputEvent(ldown, rdown)); }
				}
				if (_prevState == UIElementState::PressedDown || _prevState == UIElementState::AltPressedDown) {
					if (OnMouseReleased && !ldown && !rdown) { OnMouseReleased(*this, &UIInputEvent(ldown, rdown)); }
				}
			}
			// mouse leave event
			if (OnMouseLeave && _prevState != UIElementState::Idle)
			{
				OnMouseLeave(*this, nullptr);
			}
		}

		// calculate and return coords based on parent, return absolute value in pixels.
		PointI _UIElement::CalcCoords(const UICoords& coords, const framework::RectangleI& region, bool addRegionPosition)
		{
			// add position
			PointI ret;
			if (addRegionPosition) 
			{ 
				ret.X += region.X; 
				ret.Y += region.Y; 
			}

			// calc coords X
			switch (coords.TypeX)
			{
			case UICoordsType::Pixels:
				ret.X += coords.Value.X;
				break;

			case UICoordsType::PercentOfParent:
				ret.X += (int)((float)(coords.Value.X / 100.0f) * region.Width);
				break;
			}

			// calc coords Y
			switch (coords.TypeY)
			{
			case UICoordsType::Pixels:
				ret.Y += coords.Value.Y;
				break;

			case UICoordsType::PercentOfParent:
				ret.Y += (int)((float)(coords.Value.Y / 100.0f) * region.Height);
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
				parentRect.X += _parent->_padding.Left;
				parentRect.Width -= _parent->_padding.Left + _parent->_padding.Right;
				parentRect.Y += _parent->_padding.Top;
				parentRect.Height -= _parent->_padding.Top + _parent->_padding.Bottom;
			}
			else
			{
				auto renderSize = bon::_GetEngine().Gfx().RenderableSize();
				parentRect.Set(0, 0, renderSize.X, renderSize.Y);
			}

			// calc position
			auto position = CalcCoords(_position, parentRect, true);
			_destRect.X = position.X;
			_destRect.Y = position.Y;

			// calc size
			auto size = CalcCoords(_size, parentRect, false);
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