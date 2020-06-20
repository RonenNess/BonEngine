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
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			Background = bon::_GetEngine().UI().CreateWindow(nullptr, tempPtrThatDoesntDelete);
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

			// mark as dirty
			_listDirty = true;
		}

		// dd item to list.
		void _UIList::AddItem(const char* item)
		{
			// create item background
			UIImage itemBack = bon::_GetEngine().UI().CreateImage(nullptr, Background);
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

		// remove item from list.
		void _UIList::RemoveItem(const char* item)
		{
			// remove item
			_items.remove_if([item](const ListItem& curr) {
				bool remove = strcmp(curr.Text->GetText(), item) == 0;
				if (remove) {
					curr.Text->Remove();
					curr.Background->Remove();
				}
				return remove;
			});

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

			// mark list as dirty
			_listDirty = true;
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

			// mark list as dirty
			_listDirty = true;
		}

		// update list
		void _UIList::Update(double deltaTime)
		{
			// set items offset and height
			int i = 0;
			for (auto item : _items)
			{
				item.Background->SetOffset(bon::PointI(0, i * _lineHeight));
				item.Background->SetSize(UISize(100, UISizeType::PercentOfParent, _lineHeight, UISizeType::Pixels));
				i++;
			}

			// do base updates
			_UIElement::Update(deltaTime);
		}
	}
}