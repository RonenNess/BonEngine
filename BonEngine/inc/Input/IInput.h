/*****************************************************************//**
 * \file   IInput.h
 * \brief  Define the API for the Input manager class.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../IManager.h"
#include "../Framework/Point.h"
#include "../Assets/Types/Config.h"
#include <vector>
#include <string>
#include "Defs.h"


namespace bon
{
	namespace input
	{
		/**
		 * Interface for the input manager.
		 * This manager responsible to get input from user.
		 */
		class BON_DLLEXPORT IInput : public IManager
		{
		public:

			/**
			 * Get if a given game action is down.
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action is currently down.
			 */
			virtual bool Down(const char* actionId) const = 0;

			/**
			 * Get if a given game action was released this frame
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action was released now.
			 */
			virtual bool ReleasedNow(const char* actionId) const = 0;

			/**
			 * Get if a given game action was pressed this frame
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action was pressed now.
			 */
			virtual bool PressedNow(const char* actionId) const = 0;

			/**
			 * Get if a key code is down.
			 *
			 * \param key Key code to check.
			 * \return If input action is currently down.
			 */
			virtual bool Down(KeyCodes key) const = 0;

			/**
			 * Get if a key code was released this frame
			 *
			 * \param key Key code to check.
			 * \return If input action was released now.
			 */
			virtual bool ReleasedNow(KeyCodes key) const = 0;

			/**
			 * Get if a key code was pressed this frame
			 *
			 * \param key Key code to check.
			 * \return If input action was pressed now.
			 */
			virtual bool PressedNow(KeyCodes key) const = 0;

			/**
			 * Get scrolling delta.
			 *
			 * \return Scroll delta.
			 */
			virtual const framework::PointI& ScrollDelta() const = 0;

			/**
			 * Get all key codes assigned to a given action id.
			 * 
			 * \param actionId Action id to get assigned keys to.
			 * \return Vector with all keys currently assigned to action id.
			 */
			virtual std::vector<KeyCodes> GetAssignedKeys(const char* actionId) const = 0;

			/**
			 * Load controls from a config file. All keys must be under 'controls' section.
			 *
			 * \param config Config asset to load controls from.
			 * \param removePreviousBinds if true, will remove previous key binds.
			 */
			virtual void LoadControlsFromConfig(const assets::ConfigAsset& config, bool removePreviousBinds) = 0;

			/**
			 * Get cursor position.
			 *
			 * \return Current cursor position.
			 */
			virtual const framework::PointI& CursorPosition() const = 0;

			/**
			 * Get cursor movement from last frame.
			 *
			 * \return Current cursor delta.
			 */
			virtual const framework::PointI& CursorDelta() const = 0;

			/**
			 * Bind a key to an action id.
			 *
			 * \param keyCode Key code to bind.
			 * \param actionId Action to trigger when this key pressed.
			 */
			virtual void SetKeyBind(KeyCodes keyCode, const char* actionId) = 0;

			/**
			 * Set clipboard value.
			 * 
			 * \param text Text to set as clipboard.
			 */
			virtual void SetClipboard(const char* text) = 0;

			/**
			 * Get clipboard value.
			 *
			 * \return Clipboard value.
			 */
			virtual std::string GetClipboard() const = 0;
			
			/**
			 * Get text input data.
			 * 
			 * \return Text input data.
			 */
			virtual const TextInputData& GetTextInput() const = 0;

		protected:

			/**
			 * Get manager identifier.
			 */
			virtual const char* _GetId() const override { return "input"; }
		};
	}
}