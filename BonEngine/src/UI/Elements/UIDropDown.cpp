#include <UI/Elements/UIDropDown.h>
#include <UI/Elements/UIList.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIDropDown::_Init()
		{
			_UIList::_Init();
		}

		// initialize element style from config file.
		void _UIDropDown::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIList::LoadStyleFrom(config);

			
		}
	}
}