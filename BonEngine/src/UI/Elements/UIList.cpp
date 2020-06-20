#include <UI/Elements/UIList.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

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
			LineHeight = config->GetInt("list", "line_height", 30);
		}

		// dd item to list.
		void _UIList::AddItem(const char* item)
		{
			// create item background
			UIImage itemBack = bon::_GetEngine().UI().CreateImage(nullptr, Background);
			if (_itemsBackgroundSheet.get()) { itemBack->LoadStyleFrom(_itemsBackgroundSheet); }
			itemBack->SetSize(UISize(100, UISizeType::PercentOfParent, LineHeight, UISizeType::Pixels));

			// create item text
			UIText itemText = bon::_GetEngine().UI().CreateText(nullptr, itemBack, item);
			if (_itemsSheet.get()) { itemText->LoadStyleFrom(_itemsSheet); }
			itemText->Interactive = itemText->CopyParentState = true;

			// set item offset
			itemBack->SetOffset(bon::PointI(0, _items.size() * LineHeight));

			// add to items list
			ListItem litem;
			litem.Text = itemText;
			litem.Background = itemBack;
			_items.push_back(litem);
		}

		// remove item from list.
		void _UIList::RemoveItem(const char* item)
		{

		}

		// clear list.
		void _UIList::Clear()
		{

		}
	}
}