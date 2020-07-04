/*****************************************************************//**
 * \file   Input.h
 * \brief  The default input manager implemented by BonEngine.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "IInput.h"
#include "../Framework/Point.h"
#include <unordered_map>


namespace bon
{
	namespace input
	{
		/**
		 * Default input manager.
		 */
		class Input : public IInput
		{
		private:

			/**
			 * Store the state of an input action and when it was updated.
			 */
			struct _ActionStates
			{
				bool IsDown = false;
				unsigned long long UpdateFrameId = -1;
				unsigned long long FixedUpdateFrameId = -1;
			};

			// raw keyboard, keys, scroller and even mouse-move values
			std::unordered_map<KeyCodes, _ActionStates> _currKeyStates;

			// bind keys to commands
			std::unordered_map<KeyCodes, std::string> _keyBinds;

			// action states
			std::unordered_map<std::string, _ActionStates> _actionStates;

			// the position of mouse or other pointers
			framework::PointI _cursorPosition;
			
			// the position of mouse or other pointers from last frame
			framework::PointI _prevCursorPosition;

			// current cursor movement
			framework::PointI _cursorMovement;

			// current frame scroller delta
			framework::PointI _scrollDelta;

		public:

			/**
			 * Get if a given game action is down.
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action is currently down.
			 */
			virtual bool Down(const char* actionId) const override;

			/**
			 * Get if a given game action was released this frame
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action was released now.
			 */
			virtual bool ReleasedNow(const char* actionId) const override;

			/**
			 * Get if a given game action was pressed this frame
			 *
			 * \param actionId Action identifier, based on mapping.
			 * \return If input action was pressed now.
			 */
			virtual bool PressedNow(const char* actionId) const override;

			/**
			 * Get if a key code is down.
			 *
			 * \param key Key code to check.
			 * \return If input action is currently down.
			 */
			virtual bool Down(KeyCodes key) const override;

			/**
			 * Get if a key code was released this frame
			 *
			 * \param key Key code to check.
			 * \return If input action was released now.
			 */
			virtual bool ReleasedNow(KeyCodes key) const override;

			/**
			 * Get if a key code was pressed this frame
			 *
			 * \param key Key code to check.
			 * \return If input action was pressed now.
			 */
			virtual bool PressedNow(KeyCodes key) const override;

			/**
			 * Get scrolling delta.
			 * 
			 * \return Scroll delta.
			 */
			virtual const framework::PointI& ScrollDelta() const override { return _scrollDelta; }

			/**
			 * Get cursor position.
			 * 
			 * \return Current cursor position.
			 */
			virtual const framework::PointI& CursorPosition() const override { return _cursorPosition; }
			
			/**
			 * Get cursor movement from last frame.
			 *
			 * \return Current cursor delta.
			 */
			virtual const framework::PointI& CursorDelta() const override { return _cursorMovement; }

			/**
			 * Bind a key to an action id.
			 * 
			 * \param keyCode Key code to bind.
			 * \param actionId Action to trigger when this key pressed.
			 */
			virtual void SetKeyBind(KeyCodes keyCode, const char* actionId) override;

			/**
			 * Get all key codes assigned to a given action id.
			 *
			 * \param actionId Action id to get assigned keys to.
			 * \return Vector with all keys currently assigned to action id.
			 */
			virtual std::vector<KeyCodes> GetAssignedKeys(const char* actionId) const override;

		protected:

			/**
			 * Get key state of an action.
			 *
			 * \param actionId Action to get.
			 * \return Action state.
			 */
			KeyStates GetState(const char* actionId) const;

			/**
			 * Get key state of a key code.
			 *
			 * \param keyCode Key to get.
			 * \return Key state.
			 */
			KeyStates GetState(KeyCodes keyCode) const;

			/**
			 * Initialize manager when engine starts.
			 */
			virtual void _Initialize() override;

			/**
			 * Clear / free this manager's resources.
			 */
			virtual void _Dispose() override;

			/**
			 * Called every frame.
			 */
			virtual void _Update(double deltaTime) override;

			/**
			 * Handles an event from OS.
			 */
			virtual void _HandleEvent(SDL_Event& event) override;

			/**
			 * Called when main loop starts.
			 */
			virtual void _Start() override;

		private:

			/**
			 * Set default key binds.
			 * Used when user doesn't specify any keys.
			 */
			void SetDefaultKeyBinds();

			/**
			 * Set a key state.
			 * 
			 * \param key Key to set.
			 * \param value New value.
			 */
			void SetKeyState(KeyCodes key, bool value);
		};
	}
}
