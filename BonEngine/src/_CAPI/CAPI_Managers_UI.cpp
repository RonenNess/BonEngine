#include <_CAPI/CAPI_Managers_UI.h>
#include <BonEngine.h>

/**
* Release a UI element.
*/
void BON_UI_ReleaseElement(bon::UIElement* element)
{
	delete element;
}

/**
* Set cursor to render.
*/
void BON_UI_SetCursorEx(const bon::assets::ImageAsset* image, int width, int height, int offsetX, int offsetY)
{
	bon::_GetEngine().UI().SetCursor(*image, bon::framework::PointI(width, height), bon::framework::PointI(offsetX, offsetY));
}

/**
* Set cursor to render from image element.
*/
void BON_UI_SetCursor(const bon::UIImage* image)
{
	bon::_GetEngine().UI().SetCursor(*image);
}

/**
* Draw cursor, based on what set with SetCursor().
*/
void BON_UI_DrawCursor()
{
	bon::_GetEngine().UI().DrawCursor();
}

/**
* Draw a UI system or element.
*/
void BON_UI_Draw(bon::UIElement* root, bool drawCursor)
{
	bon::_GetEngine().UI().Draw(*root, drawCursor);
}

/**
* Update a UI system and to all interactions.
*/
bon::UIElement* BON_UI_UpdateUI(bon::UIElement* root)
{
	bon::UIElement* outActiveElement = new bon::UIElement;
	bon::_GetEngine().UI().UpdateUI(*root, outActiveElement);
	return outActiveElement;
}

/**
* Create and return a new root element.
*/
bon::UIElement* BON_UI_CreateRoot()
{
	return new bon::UIElement(bon::_GetEngine().UI().CreateRoot());
}

#define ptrOrNull(_parent_) (parent != nullptr ? *parent : nullptr)

/**
* Create and return an empty container element.
*/
bon::UIElement* BON_UI_CreateContainer(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIElement(bon::_GetEngine().UI().CreateContainer(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return an image element.
*/
bon::UIImage* BON_UI_CreateImage(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIImage(bon::_GetEngine().UI().CreateImage(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return a text element.
*/
bon::UIText* BON_UI_CreateText(const char* stylesheet, bon::UIElement* parent, const char* text)
{
	return new bon::UIText(bon::_GetEngine().UI().CreateText(stylesheet, ptrOrNull(parent), text));
}

/**
* Create and return a window element.
*/
bon::UIWindow* BON_UI_CreateWindow(const char* stylesheet, bon::UIElement* parent, const char* title)
{
	return new bon::UIWindow(bon::_GetEngine().UI().CreateUIWindow(stylesheet, ptrOrNull(parent), title));
}

/**
* Create and return a button element.
*/
bon::UIButton* BON_UI_CreateButton(const char* stylesheet, bon::UIElement* parent, const char* caption)
{
	return new bon::UIButton(bon::_GetEngine().UI().CreateButton(stylesheet, ptrOrNull(parent), caption));
}

/**
* Create and return a text input element.
*/
bon::UITextInput* BON_UI_CreateTextInput(const char* stylesheet, bon::UIElement* parent, const char* startingVal, const char* placeholder)
{
	return new bon::UITextInput(bon::_GetEngine().UI().CreateTextInput(stylesheet, ptrOrNull(parent), startingVal, placeholder));
}

/**
* Create and return a checkbox element.
*/
bon::UICheckBox* BON_UI_CreateCheckbox(const char* stylesheet, bon::UIElement* parent, const char* caption)
{
	return new bon::UICheckBox(bon::_GetEngine().UI().CreateCheckbox(stylesheet, ptrOrNull(parent), caption));
}

/**
* Create and return a radio button element.
*/
bon::UIRadioButton* BON_UI_CreateRadioButton(const char* stylesheet, bon::UIElement* parent, const char* caption)
{
	return new bon::UIRadioButton(bon::_GetEngine().UI().CreateRadioButton(stylesheet, ptrOrNull(parent), caption));
}

/**
* Create and return a list element.
*/
bon::UIList* BON_UI_CreateList(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIList(bon::_GetEngine().UI().CreateList(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return a dropdown element.
*/
bon::UIDropDown* BON_UI_CreateDropDown(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIDropDown(bon::_GetEngine().UI().CreateDropDown(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return a slider element.
*/
bon::UISlider* BON_UI_CreateSlider(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UISlider(bon::_GetEngine().UI().CreateSlider(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return a vertical scrollbar element.
*/
bon::UIVerticalScrollbar* BON_UI_CreateVerticalScrollbar(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIVerticalScrollbar(bon::_GetEngine().UI().CreateVerticalScrollbar(stylesheet, ptrOrNull(parent)));
}

/**
* Create and return a rectangle element.
*/
bon::UIRectangle* BON_UI_CreateRectangle(const char* stylesheet, bon::UIElement* parent)
{
	return new bon::UIRectangle(bon::_GetEngine().UI().CreateRectangle(stylesheet, ptrOrNull(parent)));
}

/**
* Override cursor position just for the input manager.
*/
void BON_UI_OverrideCursorPosition(int x, int y)
{
	if (x == -1) {
		bon::_GetEngine().UI().OverrideCursorPosition(nullptr);
	}
	else {
		bon::_GetEngine().UI().OverrideCursorPosition(&bon::PointI(x, y));
	}
}
