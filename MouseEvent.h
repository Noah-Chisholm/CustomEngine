#pragma once

#include <windows.h>

namespace Mouse {

	enum MouseInteraction {
		MouseMove,
		MouseLeftButtonDown,
		MouseLeftButtonUp,
		MouseRightButtonDown,
		MouseRightButtonUp,
		MouseMiddleButtonDown,
		MouseMiddleButtonUp,
		MouseWheel,
		MouseHorizontalWheel
	};

	struct MouseEvent {
		MouseInteraction Interaction; // Type of mouse interaction
		int X; // X coordinate of the mouse event
		int Y; // Y coordinate of the mouse event
		int Delta; // Scroll delta for wheel events, 0 for other events
	};
};