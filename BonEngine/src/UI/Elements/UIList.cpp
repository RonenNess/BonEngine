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
			const char* windowSheet = config->GetStr("list", "background_style", nullptr);
			if (windowSheet) { Background->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(windowSheet).c_str())); }

			// load items config file
			const char* itemsSheet = config->GetStr("list", "items_style", nullptr);
			_itemsSheet = bon::_GetEngine().Assets().LoadConfig(ToRelativePath(itemsSheet).c_str());

			// load items distance
			LineHeight = config->GetInt("list", "line_height", 30);
		}

		// dd item to list.
		void _UIList::AddItem(const char* item)
		{
			// create item
			UIText itemText = bon::_GetEngine().UI().CreateText(nullptr, Background, item);
			itemText->LoadStyleFrom(_itemsSheet);

			// set item offset
			itemText->SetOffset(bon::PointI(0, _items.size() * LineHeight));

			// add to items list
			_items.push_back(itemText);
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