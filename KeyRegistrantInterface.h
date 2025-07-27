#pragma once
#include "KeyEvent.h"
#include "MouseEvent.h"

class KeyRegistrantInterface {
	public:
		virtual void KeyStroke(KeyEvent) = 0; // Pure virtual function to handle key events
};

class MouseRegistrantInterface {
	public:
		virtual void MouseEvent(Mouse::MouseEvent) = 0; // Pure virtual function to handle mouse events
};