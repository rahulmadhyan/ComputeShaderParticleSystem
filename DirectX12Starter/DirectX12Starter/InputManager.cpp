#include "InputManager.h"
   
InputManager::InputManager()
{
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
}

InputManager::~InputManager()
{
	
}

bool InputManager::isKeyPressed(const unsigned char keyCode)
{
	return keyStates[keyCode];
}

bool InputManager::KeyBufferEmpty()
{
	return keyBuffer.empty();
}

KeyboardEvent InputManager::ReadKey()
{
	if (keyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
}

void InputManager::OnKeyPressed(const unsigned char key)
{
	keyStates[key] = true;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void InputManager::OnKeyReleased(const unsigned char key)
{
	keyStates[key] = false;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void InputManager::EnableAutoRepeatKeys()
{
	autoRepeatKeys = true;
}

void InputManager::DisableAutoRepeatKeys()
{
	autoRepeatKeys = false;
}

bool InputManager::isKeysAutoRepeat()
{
	return autoRepeatKeys;
}

void InputManager::UpdateController()
{
	DWORD dwResult;
	for (DWORD i = 0; i < 1; i++) // loop 1 since we are using only one controller for now  // in future 'XUSER_MAX_COUNT' if using multiple controllers
	{							
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			if (previousControllerState != state.dwPacketNumber)
			{
				gameController = state.Gamepad;
			}
		}
		else
		{
			// Controller is not connected 
		}
	}
}

bool InputManager::isControllerButtonPressed(WORD keyCode)
{
	if (gameController.wButtons & keyCode)
	{
		return true;
	}

	return false;
}

SHORT InputManager::getLeftStickX()
{
	return gameController.sThumbLX;
}

SHORT InputManager::getLeftStickY()
{
	return gameController.sThumbLY;
}
SHORT InputManager::getRightStickX()
{
	return gameController.sThumbRX;
}

SHORT InputManager::getRightStickY()
{
	return gameController.sThumbRY;
}