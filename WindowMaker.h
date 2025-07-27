#pragma once
#include <windows.h>
#include "Map.h"
#include "Pair.h"
#include "Flag.h"
#include "TickableInterface.h"
#include <vector>
#include "KeyEvent.h"

class KeyRegistrantInterface;
class MouseRegistrantInterface;
class RenderableInterface;

class Window : public TickableInterface {
public:
	void CreateWindowAndRun(const LPCTSTR CLASS_NAME, const LPCTSTR WindowName, bool ShouldTick = true, uint32_t Width = 800, uint32_t Height = 600, const DWORD Style = WS_OVERLAPPEDWINDOW, uint32_t XPosition = CW_DEFAULT, uint32_t YPosition = CW_DEFAULT, const DWORD ExtendedStyle = 0, HWND ParentWindow = NULL, HMENU ChildWindow = NULL);
	
	enum WindowFlags : uint16_t {
		WindowCreated = Flags::Flag16::Flag1,  // Window has been created
		KeyStrokeWaiting = Flags::Flag16::Flag2,  // A keystroke needs processing
		MouseEvent = Flags::Flag16::Flag3,  // Mouse event (move, click, wheel)
		NeedsRedraw = Flags::Flag16::Flag4,  // Something changed that requires redraw
		WindowResized = Flags::Flag16::Flag5,  // Window resize event occurred
		WindowFocused = Flags::Flag16::Flag6,  // Window gained or lost focus
		ExitRequested = Flags::Flag16::Flag7,  // WM_QUIT received
		OtherMessage = Flags::Flag16::Flag8,   // Catch-all for unhandled messages
		CreationHandled = Flags::Flag16::Flag9,  // Creation message handled
		ShouldTick = Flags::Flag16::Flag10,  // Window should tick
		LimitFPS = Flags::Flag16::Flag11, // Limit FPS to the specified value
		MouseEventWaiting = Flags::Flag16::Flag12, // Mouse event waiting to be processed
	};

private:
	std::vector<KeyRegistrantInterface*> KeyRegistrants; // List of key registrants
	std::vector<MouseRegistrantInterface*> MouseRegistrants; // List of mouse registrants
	std::vector<RenderableInterface*> Renderables; // List of renderable objects
	uint16_t PixelCount;
	uint16_t FPS = 60; // Frames per second for the window
	float FrameTime = 1.0f / FPS; // Time per frame in seconds
	float TimeSinceLastFrame = 0.0f; // Time since the last frame
	Map<uint16_t, uint16_t*> PixelBuffers; // Map of pixel buffers for each layer
	uint16_t width, height; // Width and height of the window
	std::vector<KeyEvent> KeyEvents; // Buffer for key events
	std::vector<Mouse::MouseEvent> MouseEventsBuffer; // Buffer for mouse events
	static LRESULT CALLBACK WindowProcCommon(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK WindowProcOverride(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	Flags::Flag16State Flags; // Flags for the window state
	MSG msg = {}; // Message structure for window messages
	void Render();
	virtual void Tick(float deltaTime) override; // Override Tick method from TickableInterface
	float CalculateFrameTime() const {
		return 1.0f / FPS; // Calculate frame time based on FPS
	}
public:
	void RegisterKeyRegistrant(KeyRegistrantInterface* keyRegistrant);
	void ToggleLimitFPS(bool enable) {
		if (enable) {
			Flags.SetFlag(WindowFlags::LimitFPS);
			FrameTime = 0.0f;
		} else {
			Flags.ClearFlag(WindowFlags::LimitFPS);
		}
	}
	void SetFPS(uint16_t fps) {
		FPS = fps;
		FrameTime = CalculateFrameTime();
		if (fps <= 0) {
			Flags.SetFlag(WindowFlags::LimitFPS);
		} else {
			Flags.ClearFlag(WindowFlags::LimitFPS);
		}
	}
};
