#include "WindowMaker.h"
#include <windowsx.h>
#include "MouseEvent.h"
#include "KeyRegistrantInterface.h"
#include "RenderableInterface.h"

LRESULT Window::WindowProcCommon(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Retrieve the Window instance from the user data
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	return window->WindowProcOverride(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::WindowProcOverride(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = reinterpret_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		KeyEvent keyEvent;
		keyEvent.KeyCode = wParam; // Get the key code
		keyEvent.IsPressed = (uMsg == WM_KEYDOWN); // Check if the key is pressed or released
		KeyEvents.push_back(keyEvent); // Store the key event
		Flags.SetFlag(WindowFlags::KeyStrokeWaiting);
		break;
	}
	case WM_CREATE:
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)); // Store the Window instance in user data
		window->Flags.SetFlag(WindowFlags::WindowCreated);
		window->Flags.SetFlag(WindowFlags::CreationHandled);
		break;
	}
	case WM_DESTROY:
	{
		// Handle window destruction
		window->Flags.SetFlag(WindowFlags::ExitRequested);
		break;
	}
	case WM_SIZE:
	{
		// Handle window resizing
		window->width = LOWORD(lParam);
		window->height = HIWORD(lParam);
		window->PixelCount = window->width * window->height;
		window->Flags.SetFlag(WindowFlags::WindowResized);
		break;
	}
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_MOUSEHWHEEL:
	{
		// Handle mouse events
		window->Flags.SetFlag(WindowFlags::MouseEvent);
		Mouse::MouseEvent Event;
		Event.X = GET_X_LPARAM(lParam); // Get the X coordinate
		Event.Y = GET_Y_LPARAM(lParam); // Get the Y coordinate
		Event.Delta = 0; // Initialize delta to 0, will be set for wheel events
		switch (uMsg)
		{
			case WM_MOUSEMOVE:
			{
				Event.Interaction = Mouse::MouseMove;
				break;
			}
			case WM_LBUTTONDOWN:
			{
				Event.Interaction = Mouse::MouseLeftButtonDown;
				break;
			}
			case WM_LBUTTONUP:
			{
				Event.Interaction = Mouse::MouseLeftButtonUp;
				break;
			}
			case WM_RBUTTONDOWN:
			{
				Event.Interaction = Mouse::MouseRightButtonDown;
				break;
			}
			case WM_RBUTTONUP:
			{
				Event.Interaction = Mouse::MouseRightButtonUp;
				break;
			}
			case WM_MBUTTONDOWN:
			{
				Event.Interaction = Mouse::MouseMiddleButtonDown;
				break;
			}
			case WM_MBUTTONUP:
			{
				Event.Interaction = Mouse::MouseMiddleButtonUp;
				break;
			}
			case WM_MOUSEWHEEL:
			{
				Event.Interaction = Mouse::MouseWheel;
				Event.Delta = GET_WHEEL_DELTA_WPARAM(wParam); // Get the wheel delta
				break;
			}
			case WM_MOUSEHWHEEL:
			{
				Event.Interaction = Mouse::MouseHorizontalWheel;
				Event.Delta = GET_WHEEL_DELTA_WPARAM(wParam); // Get the horizontal wheel delta
				break;
			}
		}
		MouseEventsBuffer.push_back(Event); // Store the mouse event
	}
	case WM_SETFOCUS:
	{
		// Handle window focus gain
		window->Flags.SetFlag(WindowFlags::WindowFocused);
		break;
	}
	default:
		window->Flags.SetFlag(WindowFlags::OtherMessage);

		break;
	}
	return LRESULT();
}

void Window::CreateWindowAndRun(const LPCTSTR CLASS_NAME, const LPCTSTR WindowName, bool ShouldTick = true, uint32_t Width = 800, uint32_t Height = 600, const DWORD Style = WS_OVERLAPPEDWINDOW, uint32_t XPosition = CW_DEFAULT, uint32_t YPosition = CW_DEFAULT, const DWORD ExtendedStyle = 0, HWND ParentWindow = NULL, HMENU ChildWindow = NULL) {
	PixelCount = width * height;
	if(ShouldTick) {
		Flags.SetFlag(WindowFlags::ShouldTick);
	} else {
		Flags.ClearFlag(WindowFlags::ShouldTick);
	}
	//create layer 0
	uint32_t* layer0 = new uint32_t[PixelCount];
	// Initialize the pixel buffer with a default color (e.g., black)
	for (uint32_t i = 0; i < PixelCount; ++i) {
		layer0[i] = RGB(0,0,0);
	}
	PixelBuffers.Set(0, new uint16_t[PixelCount]);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProcCommon;
	wc.hInstance = GetModuleHandle(NULL);  // Get HINSTANCE manually
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		ExtendedStyle,
		CLASS_NAME,
		WindowName,
		Style,
		XPosition,
		YPosition,
		width,
		height,
		ParentWindow,
		ChildWindow,
		wc.hInstance,
		this
	);

}

void Window::Render() {
	// In future implement directX, currently render using cpu
	for(auto& renderable : Renderables) {
		renderable->Render(); // Call the render method of each renderable object
	}
}

void Window::Tick(float deltaTime)
{
	//exit
	if (Flags.IsFlagSet(WindowFlags::ExitRequested)) {
		// Handle exit request, e.g., clean up resources, close window
		PostQuitMessage(0);
		return;
	}
	// Process Window Messages
	if (Flags.IsFlagSet(WindowFlags::CreationHandled)) {
		// Handle window creation messages, e.g., WM_CREATE
		// This could include initializing resources, setting up the window, etc.
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Process key events
	if (Flags.IsFlagSet(WindowFlags::KeyStrokeWaiting)) {
		// Process key strokes
		for (auto& registrant : KeyRegistrants) {
			for(const auto& keyEvent : KeyEvents) {
				registrant->KeyStroke(keyEvent); // Call the key registrant's method to handle the key event
			}
		}
		Flags.ClearFlag(WindowFlags::KeyStrokeWaiting);
	}

	// Process mouse events
	if (Flags.IsFlagSet(WindowFlags::MouseEvent)) {
		// Process mouse events
		for(auto& registrant : MouseRegistrants) {
			for (const auto& mouseEvent : MouseEventsBuffer) {
				registrant->MouseEvent(mouseEvent); // Call the mouse registrant's method to handle the mouse event
			}
		}
		MouseEventsBuffer.clear(); // Clear the buffer after processing
		Flags.ClearFlag(WindowFlags::MouseEvent);
	}

	if (Flags.IsFlagSet(WindowFlags::ShouldTick)) {
		if (TimeSinceLastFrame < FrameTime) {
			TimeSinceLastFrame += deltaTime;
		}
		else {
			TimeSinceLastFrame = 0.0f;
			Flags.SetFlag(WindowFlags::NeedsRedraw);
		}
	}

	// Process Dirty Flag
	if (Flags.IsFlagSet(WindowFlags::NeedsRedraw)) {
		Render();
		Flags.ClearFlag(WindowFlags::NeedsRedraw);
	}
}

void Window::RegisterKeyRegistrant(KeyRegistrantInterface* keyRegistrant)
{
}
