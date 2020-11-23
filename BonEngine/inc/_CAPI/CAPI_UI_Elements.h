/*****************************************************************//**
 * \file   CAPI_UI_Elements.h
 * \brief  A C-API of BonEngine, so we can bind it to other languages.
 *			This file is for ui elements.
 *
 * \author Ronen Ness Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "CAPI_Defs.h"
#include "../Assets/Defs.h"
#include "../UI/IUI.h"
#include "../Framework/Point.h"
#include "../Framework/Rectangle.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Define callback for UI stuff.
	 */
	BON_DLLEXPORT typedef void(__stdcall* BON_UICallback)(bon::UIElement*);

	/**
	* Iterate children.
	*/
	BON_DLLEXPORT void BON_UIElement_IterateChildren(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Get element enum type.
	 */
	BON_DLLEXPORT BON_UIElementType BON_UIElement_GetType(bon::UIElement* element);

	/**
	 * Call element's init function.
	 */
	BON_DLLEXPORT void BON_UIElement_Init(bon::UIElement* element);

	/**
	 * Set element interactive mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetInteractive(bon::UIElement* element, bool val);

	/**
	 * Get element interactive mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetInteractive(bon::UIElement* element);

	/**
	 * Set element Capture Input mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetCaptureInput(bon::UIElement* element, bool val);

	/**
	 * Get element Capture Input mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetCaptureInput(bon::UIElement* element);

	/**
	 * Set element Copy Parent State mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetCopyParentState(bon::UIElement* element, bool val);

	/**
	 * Get element Copy Parent State mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetCopyParentState(bon::UIElement* element);

	/**
	 * Set element visibility.
	 */
	BON_DLLEXPORT void BON_UIElement_SetVisible(bon::UIElement* element, bool val);

	/**
	 * Get element visibility.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetVisible(bon::UIElement* element);

	/**
	 * Set element draggable mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetDraggable(bon::UIElement* element, bool val);

	/**
	 * Get element draggable mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetDraggable(bon::UIElement* element);

	/**
	 * Get if element is being dragged.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetIsBeingDragged(bon::UIElement* element);

	/**
	 * Set mouse pressed callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnMousePressed(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set mouse released callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnMouseReleased(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set mouse enter callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnMouseEnter(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set mouse leave callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnMouseLeave(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set draw callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnDraw(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set value change callback.
	 */
	BON_DLLEXPORT void BON_UIElement_OnValueChange(bon::UIElement* element, BON_UICallback callback);

	/**
	 * Set element limit drag to parent mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetLimitDragToParentArea(bon::UIElement* element, bool val);

	/**
	 * Get element limit drag to parent mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetLimitDragToParentArea(bon::UIElement* element);

	/**
	 * Set element Ignore Parent Padding mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetIgnoreParentPadding(bon::UIElement* element, bool val);

	/**
	 * Load element stylesheet from config asset.
	 */
	BON_DLLEXPORT void BON_UIElement_LoadStyleFrom(bon::UIElement* element, bon::ConfigAsset* config);

	/**
	 * Set element Force Active State mode.
	 */
	BON_DLLEXPORT void BON_UIElement_SetForceActiveState(bon::UIElement* element, bool val);

	/**
	 * Get element Force Active State mode.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetForceActiveState(bon::UIElement* element);

	/**
	 * Set element origin.
	 */
	BON_DLLEXPORT void BON_UIElement_SetOrigin(bon::UIElement* element, float x, float y);

	/**
	 * Get element origin.
	 */
	BON_DLLEXPORT void BON_UIElement_GetOrigin(bon::UIElement* element, float* x, float* y);

	/**
	 * Set element color.
	 */
	BON_DLLEXPORT void BON_UIElement_SetColor(bon::UIElement* element, float r, float g, float b, float a);

	/**
	 * Get element color.
	 */
	BON_DLLEXPORT void BON_UIElement_GetColor(bon::UIElement* element, float* r, float* g, float* b, float* a);

	/**
	 * Set element color highlight.
	 */
	BON_DLLEXPORT void BON_UIElement_SetColorHighlight(bon::UIElement* element, float r, float g, float b, float a);

	/**
	 * Get element color highlight.
	 */
	BON_DLLEXPORT void BON_UIElement_GetColorHighlight(bon::UIElement* element, float* r, float* g, float* b, float* a);

	/**
	 * Set element color pressed.
	 */
	BON_DLLEXPORT void BON_UIElement_SetColorPressed(bon::UIElement* element, float r, float g, float b, float a);

	/**
	 * Get element color pressed.
	 */
	BON_DLLEXPORT void BON_UIElement_GetColorPressed(bon::UIElement* element, float* r, float* g, float* b, float* a);

	/**
	 * Mark element as dirty.
	 */
	BON_DLLEXPORT void BON_UIElement_MarkAsDirty(bon::UIElement* element);

	/**
	 * Set element offset.
	 */
	BON_DLLEXPORT void BON_UIElement_SetOffset(bon::UIElement* element, int x, int y);

	/**
	 * Get element offset.
	 */
	BON_DLLEXPORT void BON_UIElement_GetOffset(bon::UIElement* element, int* x, int* y);

	/**
	 * Set element anchor.
	 */
	BON_DLLEXPORT void BON_UIElement_SetAnchor(bon::UIElement* element, float x, float y);

	/**
	 * Get element anchor.
	 */
	BON_DLLEXPORT void BON_UIElement_GetAnchor(bon::UIElement* element, float* x, float* y);

	/**
	 * Set element size.
	 */
	BON_DLLEXPORT void BON_UIElement_SetSize(bon::UIElement* element, int x, BON_UISizeType xtype, int y, BON_UISizeType ytype);

	/**
	 * Set element to max width.
	 */
	BON_DLLEXPORT void BON_UIElement_SetWidthToMax(bon::UIElement* element);

	/**
	 * Set element to max height.
	 */
	BON_DLLEXPORT void BON_UIElement_SetHeightToMax(bon::UIElement* element);

	/**
	 * Get element size.
	 */
	BON_DLLEXPORT void BON_UIElement_GetSize(bon::UIElement* element, int* x, BON_UISizeType* xtype, int* y, BON_UISizeType* ytype);

	/**
	 * Set element padding.
	 */
	BON_DLLEXPORT void BON_UIElement_SetPadding(bon::UIElement* element, int left, int top, int right, int bottom);

	/**
	 * Get element padding.
	 */
	BON_DLLEXPORT void BON_UIElement_GetPadding(bon::UIElement* element, int* left, int* top, int* right, int* bottom);

	/**
	 * Set element margin.
	 */
	BON_DLLEXPORT void BON_UIElement_SetMargin(bon::UIElement* element, int left, int top, int right, int bottom);

	/**
	 * Get element margin.
	 */
	BON_DLLEXPORT void BON_UIElement_GetMargin(bon::UIElement* element, int* left, int* top, int* right, int* bottom);

	/**
	 * Get element parent.
	 */
	BON_DLLEXPORT bon::_UIElement* BON_UIElement_GetParent(bon::UIElement* element);

	/**
	 * Add child element.
	 */
	BON_DLLEXPORT void BON_UIElement_AddChild(bon::UIElement* element, bon::UIElement* child);

	/**
	 * Remove child element.
	 */
	BON_DLLEXPORT void BON_UIElement_RemoveChild(bon::UIElement* element, bon::UIElement* child);

	/**
	 * Remove element from parent.
	 */
	BON_DLLEXPORT void BON_UIElement_RemoveSelf(bon::UIElement* element);

	/**
	 * Draw element.
	 */
	BON_DLLEXPORT void BON_UIElement_Draw(bon::UIElement* element);

	/**
	 * Update element.
	 */
	BON_DLLEXPORT void BON_UIElement_Update(bon::UIElement* element, double dt);

	/**
	 * Update element inputs.
	 */
	BON_DLLEXPORT void BON_UIElement_DoInputUpdates(bon::UIElement* element, int mx, int my);

	/**
	 * Move element to front.
	 */
	BON_DLLEXPORT void BON_UIElement_MoveToFront(bon::UIElement* element);

	/**
	 * Debug draw element.
	 */
	BON_DLLEXPORT void BON_UIElement_DebugDraw(bon::UIElement* element, bool recursive);

	/**
	 * Get calculated dest rect.
	 */
	BON_DLLEXPORT void BON_UIElement_GetCalculatedDestRect(bon::UIElement* element, int* x, int* y, int* width, int* height);
	
	/**
	 * Get actual dest rect.
	 */
	BON_DLLEXPORT void BON_UIElement_GetActualDestRect(bon::UIElement* element, int* x, int* y, int* width, int* height);

	/**
	 * Get element AutoArrangeChildren.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetAutoArrangeChildren(bon::UIElement* element);

	/**
	 * Set element AutoArrangeChildren.
	 */
	BON_DLLEXPORT void BON_UIElement_SetAutoArrangeChildren(bon::UIElement* element, bool val);

	/**
	 * Get element ExemptFromAutoArrange.
	 */
	BON_DLLEXPORT bool BON_UIElement_GetExemptFromAutoArrange(bon::UIElement* element);

	/**
	 * Set element ExemptFromAutoArrange.
	 */
	BON_DLLEXPORT void BON_UIElement_SetExemptFromAutoArrange(bon::UIElement* element, bool val);

	/**
	 * Validate element is inside parent.
	 */
	BON_DLLEXPORT void BON_UIElement_ValidateOffsetInsideParent(bon::UIElement* element);

	/**
	 * Get caption from button.
	 */
	BON_DLLEXPORT bon::UIText* BON_UIButton_Caption(bon::UIButton* element);

	/**
	 * Get caption from checkbox.
	 */
	BON_DLLEXPORT bon::UIText* BON_UICheckbox_Caption(bon::UICheckBox* element);

	/**
	 * Get if checkbox is checked.
	 */
	BON_DLLEXPORT bool BON_UICheckbox_Checked(bon::UICheckBox* element);

	/**
	 * Set checkbox value.
	 */
	BON_DLLEXPORT void BON_UICheckbox_SetValue(bon::UICheckBox* element, bool value);

	/**
	 * Toggle checkbox.
	 */
	BON_DLLEXPORT void BON_UICheckbox_Toggle(bon::UICheckBox* element);

	/**
	 * Get caption from radio button.
	 */
	BON_DLLEXPORT bon::UIText* BON_UIRadio_Caption(bon::UIRadioButton* element);

	/**
	 * Get if radio button is checked.
	 */
	BON_DLLEXPORT bool BON_UIRadio_Checked(bon::UIRadioButton* element);

	/**
	 * Set radio button value.
	 */
	BON_DLLEXPORT void BON_UIRadio_SetValue(bon::UIRadioButton* element, bool value);

	/**
	 * Toggle radio button.
	 */
	BON_DLLEXPORT void BON_UIRadio_Toggle(bon::UIRadioButton* element);

	/**
	 * Get ui image image.
	 */
	BON_DLLEXPORT bon::ImageAsset* BON_UIImage_GetImage(bon::UIImage* element);

	/**
	 * Set ui image image.
	 */
	BON_DLLEXPORT void BON_UIImage_SetImage(bon::UIImage* element, bon::ImageAsset* image);

	/**
	 * Set ui image source rect.
	 */
	BON_DLLEXPORT void BON_UIImage_SetSourceRect(bon::UIImage* element, int x, int y, int width, int height);

	/**
	 * Get ui image source rect.
	 */
	BON_DLLEXPORT void BON_UIImage_GetSourceRect(bon::UIImage* element, int* x, int* y, int* width, int* height);

	/**
	 * Set ui image source rect highlight.
	 */
	BON_DLLEXPORT void BON_UIImage_SetSourceRectHighlight(bon::UIImage* element, int x, int y, int width, int height);

	/**
	 * Get ui image source rect highlight.
	 */
	BON_DLLEXPORT void BON_UIImage_GetSourceRectHighlight(bon::UIImage* element, int* x, int* y, int* width, int* height);

	/**
	 * Set ui image source rect pressed.
	 */
	BON_DLLEXPORT void BON_UIImage_SetSourceRectPressed(bon::UIImage* element, int x, int y, int width, int height);

	/**
	 * Get ui image source rect pressed.
	 */
	BON_DLLEXPORT void BON_UIImage_GetSourceRectPressed(bon::UIImage* element, int* x, int* y, int* width, int* height);

	/**
	 * Set ui image blend mode.
	 */
	BON_DLLEXPORT void BON_UIImage_SetBlendMode(bon::UIImage* element, BON_BlendModes blend);

	/**
	 * Get ui image blend mode.
	 */
	BON_DLLEXPORT BON_BlendModes BON_UIImage_GetBlendMode(bon::UIImage* element);

	/**
	 * Set ui image blend mode.
	 */
	BON_DLLEXPORT void BON_UIImage_SetImageTypes(bon::UIImage* element, BON_UIImageTypes type);

	/**
	 * Get ui image blend mode.
	 */
	BON_DLLEXPORT BON_UIImageTypes BON_UIImage_GetImageTypes(bon::UIImage* element);

	/**
	 * Set ui image scale.
	 */
	BON_DLLEXPORT void BON_UIImage_SetImageScale(bon::UIImage* element, float scale);

	/**
	 * Get ui image scale.
	 */
	BON_DLLEXPORT float BON_UIImage_GetImageScale(bon::UIImage* element);

	/**
	 * Set element slided image sides.
	 */
	BON_DLLEXPORT void BON_UIImage_SetSlicedImageSides(bon::UIImage* element, int left, int top, int right, int bottom);

	/**
	 * Get element slided image sides.
	 */
	BON_DLLEXPORT void BON_UIImage_GetSlicedImageSides(bon::UIImage* element, int* left, int* top, int* right, int* bottom);

	/**
	 * Get list background element.
	 */
	BON_DLLEXPORT bon::UIWindow* BON_UIList_Background(bon::UIList* element);

	/**
	 * Get if list contains an item.
	 */
	BON_DLLEXPORT bool BON_UIList_Contains(bon::UIList* element, const char* item);

	/**
	 * Set list line height.
	 */
	BON_DLLEXPORT void BON_UIList_SetLineHeight(bon::UIList* element, int height);

	/**
	 * Get list line height.
	 */
	BON_DLLEXPORT int BON_UIList_GetLineHeight(bon::UIList* element);

	/**
	 * Set if to show list scrollbar.
	 */
	BON_DLLEXPORT void BON_UIList_ShowScrollbar(bon::UIList* element, bool show);

	/**
	 * Add item to list.
	 */
	BON_DLLEXPORT void BON_UIList_AddItem(bon::UIList* element, const char* item);

	/**
	 * Remove item from list.
	 */
	BON_DLLEXPORT void BON_UIList_RemoveItem(bon::UIList* element, const char* item, bool removeAll);

	/**
	 * Remove item from list.
	 */
	BON_DLLEXPORT void BON_UIList_RemoveItemByIndex(bon::UIList* element, int index);

	/**
	 * Remove item from list.
	 */
	BON_DLLEXPORT void BON_UIList_Clear(bon::UIList* element);

	/**
	 * Get list selected index.
	 */
	BON_DLLEXPORT int BON_UIList_SelectedIndex(bon::UIList* element);

	/**
	 * Get list selected item.
	 */
	BON_DLLEXPORT const char* BON_UIList_SelectedItem(bon::UIList* element);

	/**
	 * Set selected value.
	 */
	BON_DLLEXPORT void BON_UIList_Select(bon::UIList* element, const char* item);

	/**
	 * Set selected value.
	 */
	BON_DLLEXPORT void BON_UIList_SelectIndex(bon::UIList* element, int index);

	/**
	 * Clear list selection.
	 */
	BON_DLLEXPORT void BON_UIList_ClearSelection(bon::UIList* element);

	/**
	 * Set list locked
	 */
	BON_DLLEXPORT void BON_UIList_SetLocked(bon::UIList* element, bool locked);

	/**
	 * Get if list ist locked
	 */
	BON_DLLEXPORT bool BON_UIList_GetLocked(bon::UIList* element);

	/**
	 * Set slider max value.
	 */
	BON_DLLEXPORT void BON_UISlider_SetMaxValue(bon::UISlider* element, int maxVal);
	
	/**
	 * Get slider max value.
	 */
	BON_DLLEXPORT int BON_UISlider_GetMaxValue(bon::UISlider* element);
	
	/**
	 * Set slider value.
	 */
	BON_DLLEXPORT void BON_UISlider_SetValue(bon::UISlider* element, int val);

	/**
	 * Get slider value.
	 */
	BON_DLLEXPORT int BON_UISlider_GetValue(bon::UISlider* element);

	/**
	 * Get text font.
	 */
	BON_DLLEXPORT bon::FontAsset* BON_UIText_GetFont(bon::UIText* element);

	/**
	 * Set text font.
	 */
	BON_DLLEXPORT void BON_UIText_SetFont(bon::UIText* element, bon::FontAsset* font);

	/**
	 * Get text outline.
	 */
	BON_DLLEXPORT int BON_UIText_GetOutlineWidth(bon::UIText* element);

	/**
	 * Set text outline.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlineWidth(bon::UIText* element, int width);

	/**
	 * Get text outline highlight.
	 */
	BON_DLLEXPORT int BON_UIText_GetOutlineHighlightWidth(bon::UIText* element);

	/**
	 * Set text outline highlight.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlineHighlightWidth(bon::UIText* element, int width);

	/**
	 * Get text outline pressed.
	 */
	BON_DLLEXPORT int BON_UIText_GetOutlinePressedWidth(bon::UIText* element);

	/**
	 * Set text outline pressed.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlinePressedWidth(bon::UIText* element, int width);

	/**
	 * Get text font size.
	 */
	BON_DLLEXPORT int BON_UIText_GetFontSize(bon::UIText* element);

	/**
	 * Set text font size.
	 */
	BON_DLLEXPORT void BON_UIText_SetFontSize(bon::UIText* element, int size);

	/**
	 * Get text alignment.
	 */
	BON_DLLEXPORT BON_UITextAlignment BON_UIText_GetAlignment(bon::UIText* element);

	/**
	 * Get text word wrap state.
	 */
	BON_DLLEXPORT bool BON_UIText_GetWordWrap(bon::UIText* element);

	/**
	 * Set text word wrap state.
	 */
	BON_DLLEXPORT void BON_UIText_SetWordWrap(bon::UIText* element, bool value);

	/**
	 * Set text alignment.
	 */
	BON_DLLEXPORT void BON_UIText_SetAlignment(bon::UIText* element, BON_UITextAlignment alignment);

	/**
	 * Get text text.
	 */
	BON_DLLEXPORT const char* BON_UIText_GetText(bon::UIText* element);

	/**
	 * Set text text.
	 */
	BON_DLLEXPORT void BON_UIText_SetText(bon::UIText* element, const char* text);

	/**
	 * Set element outline color.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlineColor(bon::UIText* element, float r, float g, float b, float a);

	/**
	 * Get element outline color.
	 */
	BON_DLLEXPORT void BON_UIText_GetOutlineColor(bon::UIText* element, float* r, float* g, float* b, float* a);

	/**
	 * Set element highlight outline color.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlineHighlightColor(bon::UIText* element, float r, float g, float b, float a);

	/**
	 * Get element highlight outline color.
	 */
	BON_DLLEXPORT void BON_UIText_GetOutlineHighlightColor(bon::UIText* element, float* r, float* g, float* b, float* a);

	/**
	 * Set element pressed outline color.
	 */
	BON_DLLEXPORT void BON_UIText_SetOutlinePressedColor(bon::UIText* element, float r, float g, float b, float a);

	/**
	 * Get element pressed outline color.
	 */
	BON_DLLEXPORT void BON_UIText_GetOutlinePressedColor(bon::UIText* element, float* r, float* g, float* b, float* a);

	/**
	 * Get title from window.
	 */
	BON_DLLEXPORT bon::UIText* BON_UIWindow_Title(bon::UIWindow* element);

	/**
	 * Get scrollbar max value.
	 */
	BON_DLLEXPORT void BON_UIScrollbar_SetMaxValue(bon::UIVerticalScrollbar* element, int maxVal);

	/**
	 * Get scrollbar max value.
	 */
	BON_DLLEXPORT int BON_UIScrollbar_GetMaxValue(bon::UIVerticalScrollbar* element);
	
	/**
	 * Get scrollbar value.
	 */
	BON_DLLEXPORT int BON_UIScrollbar_GetValue(bon::UIVerticalScrollbar* element);

	/**
	 * Get checkbox allow uncheck.
	 */
	BON_DLLEXPORT bool BON_UICheckbox_GetAllowUncheck(bon::UICheckBox* element);

	/**
	 * Set checkbox allow uncheck.
	 */
	BON_DLLEXPORT void BON_UICheckbox_SetAllowUncheck(bon::UICheckBox* element, bool value);

	/**
	 * Get checkbox allow uncheck.
	 */
	BON_DLLEXPORT bool BON_UIRadio_GetAllowUncheck(bon::UIRadioButton* element);

	/**
	 * Set checkbox allow uncheck.
	 */
	BON_DLLEXPORT void BON_UIRadio_SetAllowUncheck(bon::UIRadioButton* element, bool value);

	/**
	 * Set text input caret character.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetCaretCharacter(bon::UITextInput* element, char value);

	/**
	 * Get text input caret character.
	 */
	BON_DLLEXPORT char BON_UITextInput_GetCaretCharacter(bon::UITextInput* element);

	/**
	 * Set text input input mode.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetInputMode(bon::UITextInput* element, BON_UITextInputMode value);

	/**
	 * Get text input input mode.
	 */
	BON_DLLEXPORT BON_UITextInputMode BON_UITextInput_GetInputMode(bon::UITextInput* element);

	/**
	 * Get text input text element.
	 */
	BON_DLLEXPORT bon::UIText* BON_UITextInput_Text(bon::UITextInput* element);

	/**
	 * Get text input placeholder element.
	 */
	BON_DLLEXPORT bon::UIText* BON_UITextInput_Placeholder(bon::UITextInput* element);

	/**
	 * Set text input caret blinking interval.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetCaretBlinkingInterval(bon::UITextInput* element, float value);

	/**
	 * Get text input caret blinking interval.
	 */
	BON_DLLEXPORT float BON_UITextInput_GetCaretBlinkingInterval(bon::UITextInput* element);

	/**
	 * Set if text input is currently receiving input.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetReceivingInput(bon::UITextInput* element, bool value);

	/**
	 * Get text input caret blinking interval.
	 */
	BON_DLLEXPORT bool BON_UITextInput_GetReceivingInput(bon::UITextInput* element);

	/**
	 * Set if text input allows tab input.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetAllowTabs(bon::UITextInput* element, bool value);

	/**
	 * Get text input allows tab input.
	 */
	BON_DLLEXPORT bool BON_UITextInput_GetAllowTabs(bon::UITextInput* element);

	/**
	 * Set text input max length.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetMaxLength(bon::UITextInput* element, int value);

	/**
	 * Get text input max length.
	 */
	BON_DLLEXPORT int BON_UITextInput_GetMaxLength(bon::UITextInput* element);

	/**
	 * Set text input value.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetValue(bon::UITextInput* element, const char* value);

	/**
	 * Get text input value.
	 */
	BON_DLLEXPORT const char* BON_UITextInput_GetValue(bon::UITextInput* element);

	/**
	 * Set text input placeholder.
	 */
	BON_DLLEXPORT void BON_UITextInput_SetPlaceholder(bon::UITextInput* element, const char* value);

	/**
	 * Get text input placeholder.
	 */
	BON_DLLEXPORT const char* BON_UITextInput_GetPlaceholder(bon::UITextInput* element);

#ifdef __cplusplus
}
#endif

