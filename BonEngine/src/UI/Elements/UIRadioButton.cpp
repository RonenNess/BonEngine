#include <UI/Elements/UIRadioButton.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// set value
		void _UIRadioButton::SetValue(bool checked)
		{
			// call base set value
			_UICheckBox::SetValue(checked);

			// disable siblings
			if (checked)
			{
				if (_parent != nullptr)
				{
					for (auto sibling : _parent->GetChildren())
					{
						if (sibling.get() != this && (sibling->GetType() == UIElementType::Radio))
						{
							((_UIRadioButton*)sibling.get())->SetValue(false);
							sibling->Update(0.1);
						}
					}
				}
			}
		}
	}
}