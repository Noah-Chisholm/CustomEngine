#pragma once

#include <windows.h>

struct KeyEvent {
	WPARAM KeyCode; // Key code of the pressed key
	bool IsPressed; // True if the key is pressed, false if released
};