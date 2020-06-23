#include <_CAPI/CAPI_UI_Elements.h>
#include <BonEngine.h>

/**
* Iterate children.
*/
void BON_UIElement_IterateChildren(bon::UIElement* element, BON_UICallback callback)
{  
	auto children = (*element)->GetChildren();
	for (auto child : children)
	{
		callback(&child);
	}
}

/**
 * Get element enum type.
 */
BON_UIElementType BON_UIElement_GetType(bon::UIElement* element)
{  
	return (BON_UIElementType)(*element)->GetType();
}

/**
 * Call element's init function.
 */
void BON_UIElement_Init(bon::UIElement* element) 
{  
	(*element)->_Init();
}

/**
 * Set element interactive mode.
 */
void BON_UIElement_SetInteractive(bon::UIElement* element, bool val) 
{  
	(*element)->Interactive = val;
}

/**
 * Get element interactive mode.
 */
bool BON_UIElement_GetInteractive(bon::UIElement* element) 
{  
	return (*element)->Interactive;
}

/**
 * Set element Capture Input mode.
 */
void BON_UIElement_SetCaptureInput(bon::UIElement* element, bool val) 
{  
	(*element)->CaptureInput = val;
}

/**
 * Get element Capture Input mode.
 */
bool BON_UIElement_GetCaptureInput(bon::UIElement* element) 
{  
	return (*element)->CaptureInput;
}

/**
 * Set element Copy Parent State mode.
 */
void BON_UIElement_SetCopyParentState(bon::UIElement* element, bool val) 
{ 
	(*element)->CopyParentState = val;
}

/**
 * Get element Copy Parent State mode.
 */
bool BON_UIElement_GetCopyParentState(bon::UIElement* element) 
{  
	return (*element)->CopyParentState;
}

/**
 * Set element visibility.
 */
void BON_UIElement_SetVisible(bon::UIElement* element, bool val) 
{ 
	(*element)->Visible = val;
}

/**
 * Get element visibility.
 */
bool BON_UIElement_GetVisible(bon::UIElement* element) 
{
	return (*element)->Visible;
}

/**
 * Set element draggable mode.
 */
void BON_UIElement_SetDraggable(bon::UIElement* element, bool val) 
{  
	(*element)->Draggable = val;
}

/**
 * Get element draggable mode.
 */
bool BON_UIElement_GetDraggable(bon::UIElement* element) 
{  
	return (*element)->Draggable;
}

/**
 * Get if element is being dragged.
 */
bool BON_UIElement_GetIsBeingDragged(bon::UIElement* element) 
{  
	return (*element)->IsBeingDragged();
}

/**
 * Set mouse pressed callback.
 */
void BON_UIElement_OnMousePressed(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnMousePressed = [callback](bon::_UIElement& element, void*)
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set mouse released callback.
 */
void BON_UIElement_OnMouseReleased(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnMouseReleased = [callback](bon::_UIElement& element, void*) 
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set mouse enter callback.
 */
void BON_UIElement_OnMouseEnter(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnMouseEnter = [callback](bon::_UIElement& element, void*)
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set mouse leave callback.
 */
void BON_UIElement_OnMouseLeave(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnMouseLeave = [callback](bon::_UIElement& element, void*)
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set draw callback.
 */
void BON_UIElement_OnDraw(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnDraw = [callback](bon::_UIElement& element, void*)
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set value change callback.
 */
void BON_UIElement_OnValueChange(bon::UIElement* element, BON_UICallback callback)
{  
	(*element)->OnValueChange = [callback](bon::_UIElement& element, void*)
	{
		bon::UIElement tempPtrThatDoesntDelete = std::shared_ptr<bon::_UIElement>(&element, [](bon::_UIElement*) {});
		callback(&tempPtrThatDoesntDelete);
	};
}

/**
 * Set element limit drag to parent mode.
 */
void BON_UIElement_SetLimitDragToParentArea(bon::UIElement* element, bool val) 
{  
	(*element)->LimitDragToParentArea = val;
}

/**
 * Get element limit drag to parent mode.
 */
bool BON_UIElement_GetLimitDragToParentArea(bon::UIElement* element) 
{  
	return (*element)->LimitDragToParentArea;
}

/**
 * Set element Ignore Parent Padding mode.
 */
void BON_UIElement_SetIgnoreParentPadding(bon::UIElement* element, bool val) 
{  
	(*element)->IgnoreParentPadding(val);
}

/**
 * Load element stylesheet from config asset.
 */
void BON_UIElement_LoadStyleFrom(bon::UIElement* element, bon::ConfigAsset* config)
{  
	(*element)->LoadStyleFrom(*config);
}

/**
 * Set element Force Active State mode.
 */
void BON_UIElement_SetForceActiveState(bon::UIElement* element, bool val) 
{  
	(*element)->ForceActiveState = val;
}

/**
 * Get element Force Active State mode.
 */
bool BON_UIElement_GetForceActiveState(bon::UIElement* element) 
{  
	return (*element)->ForceActiveState;
}

/**
 * Set element origin.
 */
void BON_UIElement_SetOrigin(bon::UIElement* element, float x, float y) 
{  
	(*element)->Origin.Set(x, y);
}

/**
 * Get element origin.
 */
void BON_UIElement_GetOrigin(bon::UIElement* element, float* x, float* y) 
{  
	*x = (*element)->Origin.X;
	*y = (*element)->Origin.Y;
}

/**
 * Set element color.
 */
void BON_UIElement_SetColor(bon::UIElement* element, float r, float g, float b, float a) 
{
	(*element)->Color = bon::Color(r, g, b, a);
}

/**
 * Get element color.
 */
void BON_UIElement_GetColor(bon::UIElement* element, float* r, float* g, float* b, float* a) 
{  
	*r = (*element)->Color.R;
	*g = (*element)->Color.G;
	*b = (*element)->Color.B;
	*a = (*element)->Color.A;
}

/**
 * Set element color highlight.
 */
void BON_UIElement_SetColorHighlight(bon::UIElement* element, float r, float g, float b, float a) 
{  
	(*element)->ColorHighlight = bon::Color(r, g, b, a);
}

/**
 * Get element color highlight.
 */
void BON_UIElement_GetColorHighlight(bon::UIElement* element, float* r, float* g, float* b, float* a) 
{ 
	*r = (*element)->ColorHighlight.R;
	*g = (*element)->ColorHighlight.G;
	*b = (*element)->ColorHighlight.B;
	*a = (*element)->ColorHighlight.A;
}

/**
 * Set element color pressed.
 */
void BON_UIElement_SetColorPressed(bon::UIElement* element, float r, float g, float b, float a) 
{  
	(*element)->ColorPressed = bon::Color(r, g, b, a);
}

/**
 * Get element color pressed.
 */
void BON_UIElement_GetColorPressed(bon::UIElement* element, float* r, float* g, float* b, float* a) 
{  
	*r = (*element)->ColorPressed.R;
	*g = (*element)->ColorPressed.G;
	*b = (*element)->ColorPressed.B;
	*a = (*element)->ColorPressed.A;
}

/**
 * Mark element as dirty.
 */
void BON_UIElement_MarkAsDirty(bon::UIElement* element)
{
	(*element)->MarkAsDirty();
}

/**
 * Set element offset.
 */
void BON_UIElement_SetOffset(bon::UIElement* element, int x, int y)
{
	(*element)->SetOffset(bon::PointI(x, y));
}

/**
 * Get element offset.
 */
void BON_UIElement_GetOffset(bon::UIElement* element, int* x, int* y)
{
	bon::PointI offset = (*element)->GetOffset();
	*x = offset.X;
	*y = offset.Y;
}

/**
 * Set element anchor.
 */
void BON_UIElement_SetAnchor(bon::UIElement* element, float x, float y)
{
	(*element)->SetAnchor(bon::PointF(x, y));
}

/**
 * Get element anchor.
 */
void BON_UIElement_GetAnchor(bon::UIElement* element, float* x, float* y)
{
	bon::PointF offset = (*element)->GetAnchor();
	*x = offset.X;
	*y = offset.Y;
}

/**
 * Set element size.
 */
void BON_UIElement_SetSize(bon::UIElement* element, int x, BON_UISizeType xtype, int y, BON_UISizeType ytype)
{
	(*element)->SetSize(bon::UISize(x, (bon::UISizeType)xtype, y, (bon::UISizeType)ytype));
}

/**
 * Set element to max width.
 */
void BON_UIElement_SetWidthToMax(bon::UIElement* element)
{
	(*element)->SetWidthToMax();
}

/**
 * Set element to max height.
 */
void BON_UIElement_SetHeightToMax(bon::UIElement* element)
{
	(*element)->SetHeightToMax();
}

/**
 * Get element size.
 */
void BON_UIElement_GetSize(bon::UIElement* element, int* x, BON_UISizeType* xtype, int* y, BON_UISizeType* ytype)
{
	auto size = (*element)->GetSize();
	*x = size.Width;
	*xtype = (BON_UISizeType)size.WidthType;
	*y = size.Height;
	*ytype = (BON_UISizeType)size.HeightType;
}

/**
 * Set element padding.
 */
void BON_UIElement_SetPadding(bon::UIElement* element, int left, int top, int right, int bottom)
{
	(*element)->SetPadding(bon::UISides(left, right, top, bottom));
}

/**
 * Get element padding.
 */
void BON_UIElement_GetPadding(bon::UIElement* element, int* left, int* top, int* right, int* bottom)
{
	const bon::UISides& padding = (*element)->GetPadding();
	*left = padding.Left;
	*right = padding.Right;
	*top = padding.Top;
	*bottom = padding.Bottom;
}

/**
 * Set element margin.
 */
void BON_UIElement_SetMargin(bon::UIElement* element, int left, int top, int right, int bottom)
{
	(*element)->SetPadding(bon::UISides(left, right, top, bottom));
}

/**
 * Get element margin.
 */
void BON_UIElement_GetMargin(bon::UIElement* element, int* left, int* top, int* right, int* bottom)
{
	const bon::UISides& margin = (*element)->Marging;
	*left = margin.Left;
	*right = margin.Right;
	*top = margin.Top;
	*bottom = margin.Bottom;
}

/**
 * Get element parent.
 */
bon::_UIElement* BON_UIElement_GetParent(bon::UIElement* element)
{
	return (bon::_UIElement*)((*element)->Parent());
}

/**
 * Add child element.
 */
void BON_UIElement_AddChild(bon::UIElement* element, bon::UIElement* child)
{
	(*element)->AddChild(*child);
}

/**
 * Remove child element.
 */
void BON_UIElement_RemoveChild(bon::UIElement* element, bon::UIElement* child)
{
	(*element)->RemoveChild(*child);
}

/**
 * Remove element from parent.
 */
void BON_UIElement_RemoveSelf(bon::UIElement* element)
{
	(*element)->Remove();
}

/**
 * Draw element.
 */
void BON_UIElement_Draw(bon::UIElement* element)
{
	(*element)->Draw();
}

/**
 * Update element.
 */
void BON_UIElement_Update(bon::UIElement* element, double dt)
{
	(*element)->Update(dt);
}

/**
 * Update element inputs.
 */
void BON_UIElement_DoInputUpdates(bon::UIElement* element, int mx, int my)
{
	bon::UIUpdateInputState state;
	(*element)->DoInputUpdates(bon::PointI(mx, my), state);
}

/**
 * Move element to front.
 */
void BON_UIElement_MoveToFront(bon::UIElement* element)
{
	(*element)->MoveToFront();
}

/**
 * Debug draw element.
 */
void BON_UIElement_DebugDraw(bon::UIElement* element, bool recursive)
{
	(*element)->DebugDraw(recursive);
}

/**
 * Get calculated dest rect.
 */
void BON_UIElement_GetCalculatedDestRect(bon::UIElement* element, int* x, int* y, int* width, int* height)
{
	const bon::RectangleI& rect = (*element)->GetCalculatedDestRect();
	*x = rect.X;
	*y = rect.Y;
	*width = rect.Width;
	*height = rect.Height;
}

/**
 * Get actual dest rect.
 */
void BON_UIElement_GetActualDestRect(bon::UIElement* element, int* x, int* y, int* width, int* height)
{
	const bon::RectangleI& rect = (*element)->GetActualDestRect();
	*x = rect.X;
	*y = rect.Y;
	*width = rect.Width;
	*height = rect.Height;
}

/**
 * Get element AutoArrangeChildren.
 */
bool BON_UIElement_GetAutoArrangeChildren(bon::UIElement* element)
{
	return (*element)->AutoArrangeChildren;
}

/**
 * Set element AutoArrangeChildren.
 */
void BON_UIElement_SetAutoArrangeChildren(bon::UIElement* element, bool val)
{
	(*element)->AutoArrangeChildren = val;
}

/**
 * Get element ExemptFromAutoArrange.
 */
bool BON_UIElement_GetExemptFromAutoArrange(bon::UIElement* element)
{
	return (*element)->ExemptFromAutoArrange;
}

/**
 * Set element ExemptFromAutoArrange.
 */
void BON_UIElement_SetExemptFromAutoArrange(bon::UIElement* element, bool val)
{
	(*element)->ExemptFromAutoArrange = val;
}

/**
 * Validate element is inside parent.
 */
void BON_UIElement_ValidateOffsetInsideParent(bon::UIElement* element)
{
	(*element)->ValidateOffsetInsideParent();
}

/**
 * Get caption from button.
 */
bon::UIText* BON_UIButton_Caption(bon::UIButton* element)
{
	return &((*element)->Caption);
}

/**
 * Get caption from checkbox.
 */
bon::UIText* BON_UICheckbox_Caption(bon::UICheckBox* element)
{
	return &((*element)->Caption);
}

/**
 * Get if checkbox is checked.
 */
bool BON_UICheckbox_Checked(bon::UICheckBox* element)
{
	return (*element)->Checked();
}

/**
 * Set checkbox value.
 */
void BON_UICheckbox_SetValue(bon::UICheckBox* element, bool value)
{
	(*element)->SetValue(value);
}

/**
 * Get checkbox allow uncheck.
 */
bool BON_UICheckbox_GetAllowUncheck(bon::UICheckBox* element)
{
	return (*element)->AllowUncheck;
}

/**
 * Set checkbox allow uncheck.
 */
void BON_UICheckbox_SetAllowUncheck(bon::UICheckBox* element, bool value)
{
	(*element)->AllowUncheck = value;
}

/**
 * Get checkbox allow uncheck.
 */
bool BON_UIRadio_GetAllowUncheck(bon::UIRadioButton* element)
{
	return (*element)->AllowUncheck;
}

/**
 * Set checkbox allow uncheck.
 */
void BON_UIRadio_SetAllowUncheck(bon::UIRadioButton* element, bool value)
{
	(*element)->AllowUncheck = value;
}

/**
 * Toggle checkbox.
 */
void BON_UICheckbox_Toggle(bon::UICheckBox* element)
{
	return (*element)->Toggle();
}

/**
 * Get caption from radio button.
 */
bon::UIText* BON_UIRadio_Caption(bon::UIRadioButton* element)
{
	return &((*element)->Caption);
}

/**
 * Get if radio button is checked.
 */
bool BON_UIRadio_Checked(bon::UIRadioButton* element)
{
	return (*element)->Checked();
}

/**
 * Set radio button value.
 */
void BON_UIRadio_SetValue(bon::UIRadioButton* element, bool value)
{
	return (*element)->SetValue(value);
}

/**
 * Toggle radio button.
 */
void BON_UIRadio_Toggle(bon::UIRadioButton* element)
{
	return (*element)->Toggle();
}

/**
 * Get ui image image.
 */
bon::ImageAsset* BON_UIImage_GetImage(bon::UIImage* element)
{
	return &((*element)->Image);
}

/**
 * Set ui image image.
 */
void BON_UIImage_SetImage(bon::UIImage* element, bon::ImageAsset* image)
{
	(*element)->Image = *image;
}

/**
 * Set ui image source rect.
 */
void BON_UIImage_SetSourceRect(bon::UIImage* element, int x, int y, int width, int height)
{
	(*element)->SourceRect.Set(x,y, width, height);
}

/**
 * Get ui image source rect.
 */
void BON_UIImage_GetSourceRect(bon::UIImage* element, int* x, int* y, int* width, int* height)
{
	*x = (*element)->SourceRect.X;
	*y = (*element)->SourceRect.Y;
	*width = (*element)->SourceRect.Width;
	*height = (*element)->SourceRect.Height;
}

/**
 * Set ui image source rect highlight.
 */
void BON_UIImage_SetSourceRectHighlight(bon::UIImage* element, int x, int y, int width, int height)
{
	(*element)->SourceRectHighlight.Set(x, y, width, height);
}

/**
 * Get ui image source rect highlight.
 */
void BON_UIImage_GetSourceRectHighlight(bon::UIImage* element, int* x, int* y, int* width, int* height)
{
	*x = (*element)->SourceRectHighlight.X;
	*y = (*element)->SourceRectHighlight.Y;
	*width = (*element)->SourceRectHighlight.Width;
	*height = (*element)->SourceRectHighlight.Height;
}

/**
 * Set ui image source rect pressed.
 */
void BON_UIImage_SetSourceRectPressed(bon::UIImage* element, int x, int y, int width, int height)
{
	(*element)->SourceRectPressed.Set(x, y, width, height);
}

/**
 * Get ui image source rect pressed.
 */
void BON_UIImage_GetSourceRectPressed(bon::UIImage* element, int* x, int* y, int* width, int* height)
{
	*x = (*element)->SourceRectPressed.X;
	*y = (*element)->SourceRectPressed.Y;
	*width = (*element)->SourceRectPressed.Width;
	*height = (*element)->SourceRectPressed.Height;
}

/**
 * Set ui image blend mode.
 */
void BON_UIImage_SetBlendMode(bon::UIImage* element, BON_BlendModes blend)
{
	(*element)->BlendMode = (bon::BlendModes)blend;
}

/**
 * Get ui image blend mode.
 */
BON_BlendModes BON_UIImage_GetBlendMode(bon::UIImage* element)
{
	return (BON_BlendModes)(*element)->BlendMode;
}

/**
 * Set ui image blend mode.
 */
void BON_UIImage_SetImageTypes(bon::UIImage* element, BON_UIImageTypes type)
{
	(*element)->ImageType = (bon::UIImageTypes)type;
}

/**
 * Get ui image blend mode.
 */
BON_UIImageTypes BON_UIImage_GetImageTypes(bon::UIImage* element)
{
	return (BON_UIImageTypes)((*element)->ImageType);
}

/**
 * Set ui image scale.
 */
void BON_UIImage_SetImageScale(bon::UIImage* element, float scale)
{
	(*element)->TextureScale = scale;
}

/**
 * Get ui image scale.
 */
float BON_UIImage_GetImageScale(bon::UIImage* element)
{
	return (*element)->TextureScale;
}

/**
 * Set element slided image sides.
 */
void BON_UIImage_SetSlicedImageSides(bon::UIImage* element, int left, int top, int right, int bottom)
{
	(*element)->SlicedImageSides.Left = left;
	(*element)->SlicedImageSides.Right = right;
	(*element)->SlicedImageSides.Top = top;
	(*element)->SlicedImageSides.Bottom = bottom;
}

/**
 * Get element slided image sides.
 */
void BON_UIImage_GetSlicedImageSides(bon::UIImage* element, int* left, int* top, int* right, int* bottom)
{
	*left = (*element)->SlicedImageSides.Left;
	*right = (*element)->SlicedImageSides.Right;
	*top = (*element)->SlicedImageSides.Top;
	*bottom = (*element)->SlicedImageSides.Bottom;
}

/**
 * Get list background
 */
bon::UIWindow* BON_UIList_Background(bon::UIList* element)
{
	return &(*element)->Background;
}

/**
 * Set list line height.
 */
void BON_UIList_SetLineHeight(bon::UIList* element, int height)
{
	(*element)->SetLineHeight(height);
}

/**
 * Get list line height.
 */
int BON_UIList_GetLineHeight(bon::UIList* element)
{
	return (*element)->GetLineHeight();
}

/**
 * Set if to show list scrollbar.
 */
void BON_UIList_ShowScrollbar(bon::UIList* element, bool show)
{
	(*element)->ShowScrollbar(show);
}

/**
 * Add item to list.
 */
void BON_UIList_AddItem(bon::UIList* element, const char* item)
{
	(*element)->AddItem(item);
}

/**
 * Remove item from list.
 */
void BON_UIList_RemoveItem(bon::UIList* element, const char* item, bool removeAll)
{
	(*element)->RemoveItem(item, removeAll);
}

/**
 * Remove item from list.
 */
void BON_UIList_RemoveItemByIndex(bon::UIList* element, int index)
{
	(*element)->RemoveItem(index);
}

/**
 * Remove item from list.
 */
void BON_UIList_Clear(bon::UIList* element)
{
	(*element)->Clear();
}

/**
 * Get list selected index.
 */
int BON_UIList_SelectedIndex(bon::UIList* element)
{
	return (*element)->SelectedIndex();
}

/**
 * Get list selected item.
 */
const char* BON_UIList_SelectedItem(bon::UIList* element)
{
	return (*element)->SelectedItem();
}

/**
 * Set selected value.
 */
void BON_UIList_Select(bon::UIList* element, const char* item)
{
	(*element)->Select(item);
}

/**
 * Set selected value.
 */
void BON_UIList_SelectIndex(bon::UIList* element, int index)
{
	(*element)->Select(index);
}

/**
 * Clear list selection.
 */
void BON_UIList_ClearSelection(bon::UIList* element)
{
	(*element)->ClearSelection();
}

/**
 * Set slider max value.
 */
void BON_UISlider_SetMaxValue(bon::UISlider* element, int maxVal)
{
	(*element)->MaxValue = maxVal;
}

/**
 * Get slider max value.
 */
int BON_UISlider_GetMaxValue(bon::UISlider* element)
{
	return (*element)->MaxValue;
}

/**
 * Set slider value.
 */
void BON_UISlider_SetValue(bon::UISlider* element, int val)
{
	(*element)->SetValue(val);
}

/**
 * Get slider value.
 */
int BON_UISlider_GetValue(bon::UISlider* element)
{
	return (*element)->GetValue();
}

/**
 * Get text font.
 */
bon::FontAsset* BON_UIText_GetFont(bon::UIText* element)
{
	return &((*element)->Font);
}

/**
 * Set text font.
 */
void BON_UIText_SetFont(bon::UIText* element, bon::FontAsset* font)
{
	(*element)->Font = *font;
}

/**
 * Get text outline.
 */
int BON_UIText_GetOutlineWidth(bon::UIText* element)
{
	return (*element)->OutlineWidth;
}

/**
 * Set text outline.
 */
void BON_UIText_SetOutlineWidth(bon::UIText* element, int width)
{
	(*element)->OutlineWidth = width;
}

/**
 * Get text outline highlight.
 */
int BON_UIText_GetOutlineHighlightWidth(bon::UIText* element)
{
	return (*element)->OutlineWidthHighlight;
}

/**
 * Set text outline highlight.
 */
void BON_UIText_SetOutlineHighlightWidth(bon::UIText* element, int width)
{
	(*element)->OutlineWidthHighlight = width;
}

/**
 * Get text outline pressed.
 */
int BON_UIText_GetOutlinePressedWidth(bon::UIText* element)
{
	return (*element)->OutlineWidthPressed;
}

/**
 * Set text outline pressed.
 */
void BON_UIText_SetOutlinePressedWidth(bon::UIText* element, int width)
{
	(*element)->OutlineWidthPressed = width;
}

/**
 * Get text font size.
 */
int BON_UIText_GetFontSize(bon::UIText* element)
{
	return (*element)->FontSize;
}

/**
 * Set text font size.
 */
void BON_UIText_SetFontSize(bon::UIText* element, int size)
{
	(*element)->FontSize = size;
}

/**
 * Get text alignment.
 */
BON_UITextAlignment BON_UIText_GetAlignment(bon::UIText* element)
{
	return (BON_UITextAlignment)(*element)->Alignment;
}

/**
 * Set text alignment.
 */
void BON_UIText_SetAlignment(bon::UIText* element, BON_UITextAlignment alignment)
{
	(*element)->Alignment = (bon::UITextAlignment)alignment;
}

/**
 * Get text text.
 */
const char* BON_UIText_GetText(bon::UIText* element)
{
	return (*element)->GetText();
}

/**
 * Set text text.
 */
void BON_UIText_SetText(bon::UIText* element, const char* text)
{
	(*element)->SetText(text);
}

/**
 * Set element outline color.
 */
void BON_UIText_SetOutlineColor(bon::UIText* element, float r, float g, float b, float a)
{
	(*element)->OutlineColor.Set(r, g, b, a);
}

/**
 * Get element outline color.
 */
void BON_UIText_GetOutlineColor(bon::UIText* element, float* r, float* g, float* b, float* a)
{
	*r = (*element)->OutlineColor.R;
	*g = (*element)->OutlineColor.G;
	*b = (*element)->OutlineColor.B;
	*a = (*element)->OutlineColor.A;
}

/**
 * Set element highlight outline color.
 */
void BON_UIText_SetOutlineHighlightColor(bon::UIText* element, float r, float g, float b, float a)
{
	(*element)->OutlineColorHighlight.Set(r, g, b, a);
}

/**
 * Get element highlight outline color.
 */
void BON_UIText_GetOutlineHighlightColor(bon::UIText* element, float* r, float* g, float* b, float* a)
{
	*r = (*element)->OutlineColorHighlight.R;
	*g = (*element)->OutlineColorHighlight.G;
	*b = (*element)->OutlineColorHighlight.B;
	*a = (*element)->OutlineColorHighlight.A;
}

/**
 * Set element pressed outline color.
 */
void BON_UIText_SetOutlinePressedColor(bon::UIText* element, float r, float g, float b, float a)
{
	(*element)->OutlineColorPressed.Set(r, g, b, a);
}

/**
 * Get element pressed outline color.
 */
void BON_UIText_GetOutlinePressedColor(bon::UIText* element, float* r, float* g, float* b, float* a)
{
	*r = (*element)->OutlineColorPressed.R;
	*g = (*element)->OutlineColorPressed.G;
	*b = (*element)->OutlineColorPressed.B;
	*a = (*element)->OutlineColorPressed.A;
}

/**
 * Get title from window.
 */
bon::UIText* BON_UIWindow_Title(bon::UIWindow* element)
{
	return &((*element)->Title);
}

/**
 * Get scrollbar max value.
 */
void BON_UIScrollbar_SetMaxValue(bon::UIVerticalScrollbar* element, int maxVal)
{
	(*element)->MaxValue = maxVal;
}

/**
 * Get scrollbar max value.
 */
int BON_UIScrollbar_GetMaxValue(bon::UIVerticalScrollbar* element)
{
	return (*element)->MaxValue;
}

/**
 * Get scrollbar value.
 */
int BON_UIScrollbar_GetValue(bon::UIVerticalScrollbar* element)
{
	return (*element)->Value();
}
