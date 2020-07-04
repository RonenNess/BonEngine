#include <_CAPI/CAPI_Managers_Input.h>
#include <BonEngine.h>

/**
* Get if a given game action is down.
*/
bool BON_Input_Down(const char* actionId)
{
	return bon::_GetEngine().Input().Down(actionId);
}

/**
* Get if a given game action was released this frame
*/
bool BON_Input_ReleasedNow(const char* actionId)
{
	return bon::_GetEngine().Input().ReleasedNow(actionId);
}

/**
* Get if a given game action was pressed this frame
*/
bool BON_Input_PressedNow(const char* actionId)
{
	return bon::_GetEngine().Input().PressedNow(actionId);
}

/**
* Get if a key code is down.
*/
bool BON_Input_KeyDown(BON_KeyCodes key)
{
	return bon::_GetEngine().Input().Down((bon::KeyCodes)key);
}

/**
* Get if a key code was released this frame
*/
bool BON_Input_KeyReleasedNow(BON_KeyCodes key)
{
	return bon::_GetEngine().Input().ReleasedNow((bon::KeyCodes)key);
}

/**
* Get if a key code was pressed this frame
*/
bool BON_Input_KeyPressedNow(BON_KeyCodes key)
{
	return bon::_GetEngine().Input().PressedNow((bon::KeyCodes)key);
}

/**
* Get scrolling delta X.
*/
int BON_Input_ScrollDeltaX()
{
	return bon::_GetEngine().Input().ScrollDelta().X;
}

/**
* Get scrolling delta Y.
*/
int BON_Input_ScrollDeltaY()
{
	return bon::_GetEngine().Input().ScrollDelta().Y;
}

/**
* Get cursor position X.
*/
int BON_Input_CursorPositionX()
{
	return bon::_GetEngine().Input().CursorPosition().X;
}

/**
* Get cursor position Y.
*/
int BON_Input_CursorPositionY()
{
	return bon::_GetEngine().Input().CursorPosition().Y;
}

/**
* Get cursor movement from last frame X.
*/
int BON_Input_CursorDeltaX()
{
	return bon::_GetEngine().Input().CursorDelta().X;
}

/**
* Get cursor movement from last frame Y.
*/
int BON_Input_CursorDeltaY()
{
	return bon::_GetEngine().Input().CursorDelta().Y;
}

/**
* Bind a key to an action id.
*/
void BON_Input_SetKeyBind(BON_KeyCodes keyCode, const char* actionId)
{
	bon::_GetEngine().Input().SetKeyBind((bon::KeyCodes)keyCode, actionId);
}

/**
* Get list of key codes assigned to given action id.
*/
int* BON_Input_GetAssignedKeys(const char* actionId, int* retLength)
{
	static std::vector<bon::KeyCodes> retVal;
	retVal = bon::_GetEngine().Input().GetAssignedKeys(actionId);
	(*retLength) = (int)retVal.size();
	return (int*)retVal.data();
}