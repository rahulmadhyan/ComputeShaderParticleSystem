#pragma once
#include <queue>
#include "Windows.h"
#include "KeyboardEvent.h"
#include "Xinput.h"

#pragma comment(lib, "XInput.lib")

class InputManager
{
public:
	InputManager();
	~InputManager();

	static InputManager* getInstance()
	{
		static InputManager* instance = NULL;
		if (instance == NULL)
		{
			instance = new InputManager;
		}
		_ASSERT(instance);
		
		return instance;
	}

	// keyboard
	bool isKeyPressed(const unsigned char keyCode);
	bool KeyBufferEmpty();
	KeyboardEvent ReadKey();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	bool isKeysAutoRepeat();

	// controller
	void UpdateController();
	bool isControllerButtonPressed(WORD keyCode);
	SHORT getLeftStickX();
	SHORT getLeftStickY();
	SHORT getRightStickX();
	SHORT getRightStickY();

private:
	bool autoRepeatKeys = false;
	bool keyStates[256];
	DWORD previousControllerState;
	_XINPUT_GAMEPAD gameController;
	std::queue<KeyboardEvent> keyBuffer;
};

