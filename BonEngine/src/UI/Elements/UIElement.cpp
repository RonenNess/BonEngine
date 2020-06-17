#include <UI/Elements/UIElement.h>
#include <Framework/Exceptions.h>
#include <BonEngine.h>

using namespace bon::framework;

namespace bon
{
	namespace ui
	{
		// add child element
		void UIElement::AddChild(UIElementPtr child)
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
		void UIElement::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load color
			Color = config->GetColor("style", "color", Color.White);

			// load padding
			RectangleF padding = config->GetRectangleF("style", "padding", RectangleF::Zero());
			_padding.FromRect(padding);

			// load width and height
			const char* width = config->GetStr("style", "width", "100p");
			const char* height = config->GetStr("style", "height", "100p");
			_size.FromStr(width, height);
		}

		// remove child element.
		void UIElement::RemoveChild(UIElementPtr child)
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
		void UIElement::Remove()
		{
			// make sure got a parent
			if (_parent == nullptr)
			{
				throw framework::InvalidState("Cannot remove an element without parent!");
			}

			// remove self
			UIElementPtr tempPtrThatDoesntDelete = std::shared_ptr<UIElement>(this, [](UIElement*) {});
			_parent->RemoveChild(tempPtrThatDoesntDelete);
			_parent = nullptr;
		}

		// draw ui element and children.
		void UIElement::Draw()
		{
			// draw self
			DrawSelf();

			// draw children
			for (auto child : _children)
			{
				child->Draw();
			}
		}

		// update the UI element and children.
		void UIElement::Update(double deltaTime)
		{
			// update self
			UpdateSelf(deltaTime);

			// update children
			for (auto child : _children)
			{
				child->Update(deltaTime);
			}
		}

		// implement just the drawing of this element.
		void UIElement::DrawSelf()
		{
			// no drawing for base element
		}

		// implement just the updating of this element
		void UIElement::UpdateSelf(double deltaTime)
		{
			// check if need to recalculate dest rect
			if (_isDestDirty || (_parent && _parentLastDestCalcId != _parent->_destCalcId))
			{
				CalcDestRect();
			}
		}

		// calculate and return coords based on parent, return absolute value in pixels.
		PointI UIElement::CalcCoords(const UICoords& coords, const framework::RectangleI& region, bool addRegionPosition)
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
		void UIElement::CalcDestRect()
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

			// no longer dirty + update calc id
			_isDestDirty = false;
			_destCalcId++;
			if (_parent) { _parentLastDestCalcId = _parent->_destCalcId; }
		}
	}
}