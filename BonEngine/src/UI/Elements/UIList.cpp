#include <UI/Elements/UIList.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>
#include <list>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIList::_Init()
		{
			// create list background
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			Background = bon::_GetEngine().UI().CreateUIWindow(nullptr, tempPtrThatDoesntDelete);

			// create container for list items
			_itemsContainer = bon::_GetEngine().UI().CreateContainer(nullptr, Background);
			_itemsContainer->SetPadding(UISides(0, 0, 0, 0));
			_itemsContainer->SetWidthToMax();
			_itemsContainer->SetHeightToMax();
		}

		// initialize element style from config file.
		void _UIList::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIElement::LoadStyleFrom(config);

			// load background window
			const char* windowSheet = config->GetStr("list", "list_background_style", nullptr);
			if (windowSheet) { Background->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(windowSheet).c_str())); }
			
			// load items background sheet
			const char* itemsBackSheet = config->GetStr("list", "item_background_style", nullptr);
			if (itemsBackSheet) { _itemsBackgroundSheet = bon::_GetEngine().Assets().LoadConfig(ToRelativePath(itemsBackSheet).c_str()); }

			// load items config file
			const char* itemsSheet = config->GetStr("list", "items_style", nullptr);
			if (itemsSheet) { _itemsSheet = bon::_GetEngine().Assets().LoadConfig(ToRelativePath(itemsSheet).c_str()); }

			// load items distance
			_lineHeight = config->GetInt("list", "line_height", 30);
			
			// create scrollbar
			const char* scrollbarSheet = config->GetStr("list", "vscrollbar_style", nullptr);
			if (scrollbarSheet) 
			{ 
				_scrollbar = bon::_GetEngine().UI().CreateVerticalScrollbar(ToRelativePath(scrollbarSheet).c_str(), Background);
			}

			// mark as dirty
			_listDirty = true;
		}

		// dd item to list.
		void _UIList::AddItem(const char* item)
		{
			// create item background
			UIImage itemBack = bon::_GetEngine().UI().CreateImage(nullptr, _itemsContainer);
			if (_itemsBackgroundSheet.get()) { itemBack->LoadStyleFrom(_itemsBackgroundSheet); }

			// create item text
			UIText itemText = bon::_GetEngine().UI().CreateText(nullptr, itemBack, item);
			if (_itemsSheet.get()) { itemText->LoadStyleFrom(_itemsSheet); }
			itemText->Interactive = itemText->CopyParentState = true;

			// add to items list
			ListItem litem;
			litem.Text = itemText;
			litem.Background = itemBack;
			_items.push_back(litem);

			// mark list as dirty
			_listDirty = true;
		}

		// get list items list.
		std::vector<std::string> _UIList::Items() const
		{
			std::vector<std::string> ret;
			for (auto curr : _items)
			{
				ret.push_back(curr.Text->GetText());
			}
			return ret;
		}

		// get if list contains a given value.
		bool _UIList::Contains(const char* value) const
		{
			for (auto curr : _items)
			{
				if (strcmp(curr.Text->GetText(), value) == 0)
				{
					return true;
				}
			}
			return false;
		}

		// remove item from list.
		void _UIList::RemoveItem(const char* item, bool removeAll)
		{
			// iterate items and remove all or first item that match value
			int prevSelection = _selected;
			int index = 0;
			for (auto curr = _items.begin(); curr != _items.end(); ++curr)
			{
				// check if need to remove
				bool remove = strcmp(curr->Text->GetText(), item) == 0;
				if (remove) {

					// remove elements
					curr->Text->Remove();
					curr->Background->Remove();

					// update selected
					if (index == _selected) { _selected = -1; }
					else if (index < _selected) { _selected--; }
					index++;

					// erase from list
					curr = _items.erase(curr);

					// if remove just one, break here
					if (!removeAll) { break; }
				}
			}

			// no selected?
			if (_selected < 0) { ClearSelection(); }
			if (prevSelection != _selected && OnValueChange)
			{
				OnValueChange(*this, nullptr);
			}

			// mark list as dirty
			_listDirty = true;
		}

		// remove item from list by index
		void _UIList::RemoveItem(int index)
		{
			// remove item
			std::list<ListItem>::iterator it = _items.begin();
			std::advance(it, index);
			it->Text->Remove();
			it->Background->Remove();
			_items.erase(it);

			// update selected
			if (index == _selected) { ClearSelection(); }
			else if (index < _selected) { Select(_selected - 1); }

			// mark list as dirty
			_listDirty = true;
		}

		// set selection
		void _UIList::Select(int index) 
		{ 
			if (_selected != index) 
			{ 
				_selected = index; 
				if (OnValueChange) { OnValueChange(*this, nullptr); }
			} 
		}

		// get currently selected item text.
		const char* _UIList::SelectedItem() const
		{
			if (_selected < 0) { return nullptr; }
			std::list<ListItem>::iterator it = ((_UIList*)(this))->_items.begin();
			std::advance(it, _selected);
			return it->Text->GetText();
		}

		// clear list.
		void _UIList::Clear()
		{
			// clear list
			for (auto curr : _items)
			{
				curr.Text->Remove();
				curr.Background->Remove();
			}
			_items.clear();
			ClearSelection();

			// mark list as dirty
			_listDirty = true;
		}

		// select by value
		void _UIList::Select(const char* item)
		{
			// clear selection
			if (item == nullptr) 
			{
				Select(-1);
				return;
			}

			// find item to select
			int index = 0;
			for (auto curr : _items)
			{
				if (strcmp(curr.Text->GetText(), item) == 0)
				{
					Select(index);
					return;
				}
				index++;
			}
		}

		// update list
		void _UIList::Update(double deltaTime, bool topLayer)
		{
			// if dirty, rearrange list
			if (_listDirty && !topLayer)
			{
				// set items offset and height
				int i = 0;
				for (auto item : _items)
				{
					// set item index and position
					item.Index = i;
					item.Background->SetOffset(bon::PointI(0, i * _lineHeight));
					item.Background->SetSize(UISize(100, UISizeType::PercentOfParent, _lineHeight, UISizeType::Pixels));
					
					// set callback
					item.Background->OnMousePressed = [this, item](_UIElement& self, void* data)
					{
						this->Select(item.Index);
					};
					
					// increase index
					i++;
				}

				// no longer dirty
				_listDirty = false;
			}

			// do base updates
			_UIElement::Update(deltaTime, topLayer);

			// set scrollbar min-max
			if (_scrollbar && !topLayer)
			{
				// calc how many items we can hold in list
				int listRegionHeight = Background->GetCalculatedDestRect().Height - (Background->GetPadding().Top + Background->GetPadding().Bottom);
				_maxVisibleEntitiesInList = listRegionHeight / _lineHeight;

				// set extra offset
				_scrollbar->_ExtraPixelsOffset = _ExtraPixelsOffset;

				// calculate how many extra items are outside
				int extras = (int)(_items.size() - _maxVisibleEntitiesInList);
				
				// got items outside? set scrollbar visible and max
				if (extras > 0) 
				{
					_scrollbar->Visible = true;
					_scrollbar->MaxValue = extras;
				}
				// no items outside range? hide scrollbar
				else 
				{
					_scrollbar->Visible = false;
					_scrollbar->MaxValue = 0;
				}
			}
		}

		// draw list
		void _UIList::Draw(bool topLayer)
		{
			if (DrawAsTopLayer() == topLayer)
			{
				// calculate bottom limit position
				int listBottomPosition = Background->GetCalculatedDestRect().Bottom() - Background->GetPadding().Bottom;

				// get scrollbar value
				int scrollVal = (_scrollbar && _scrollbar->Visible) ? _scrollbar->Value() : 0;

				// set election and visibility of items
				int index = 0;
				int positionIndex = 0;
				for (auto item : _items)
				{
					// mark active and set visibility
					item.Background->ForceActiveState = (index == _selected);
					bool isVisible = (index >= scrollVal) && (positionIndex < _maxVisibleEntitiesInList);
					item.Background->Visible = isVisible;
					if (isVisible)
					{
						item.Background->SetOffset(bon::PointI(0, positionIndex * _lineHeight));
						item.Background->Update(0.1, topLayer);
					}
					if (index >= scrollVal) positionIndex++;
					index++;
				}
			}

			// call base draw
			_UIElement::Draw(topLayer);
		}

	}
}