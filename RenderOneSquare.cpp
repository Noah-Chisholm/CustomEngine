#include "RenderOneSquare.h"
#include <stdint.h>
#include <vector>
#include "KeyEvent.h"

namespace RenderOneSquare {
	struct WindowData {
		uint32_t* Buffer; // Pointer to the pixel buffer
		uint32_t Width;  // Width of the window
		uint32_t Height; // Height of the window
	};

	struct SquareData {
		uint32_t X = 100; // X coordinate of the square
		uint32_t Y = 100; // Y coordinate of the square
		uint32_t SquareLength = 25;
		COLORREF SquareColor = RGB(255, 0, 0);
	};

	bool CreateFlag = false;
	bool ShouldRenderFlag = false;
	std::vector<KeyEvent> KeyEvents;
	const COLORREF BACKGROUND_COLOR = RGB(0, 0, 0); // Black background
	SquareData Square;
	const uint32_t MaxSquareSize = 100;
	const uint32_t MinSquareSize = 5;
}

using namespace RenderOneSquare;

LRESULT CALLBACK RenderOneSquare::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);  // Close window
		return 0;
	}
	if (uMsg == WM_CREATE) {
		WindowData* data = new WindowData();
		data->Width = 800;  // Set your desired width
		data->Height = 500; // Set your desired height
		data->Buffer = new uint32_t[data->Width * data->Height]; // Allocate pixel buffer
		CreateFlag = true; // Set the flag to indicate creation
		ShouldRenderFlag = true;
		RenderOneSquare::InitBuffer(hwnd); // Initialize the pixel buffer with the background color
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data); // Store WindowData pointer
	}
	if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) {
		KeyEvent keyEvent;
		keyEvent.KeyCode = wParam; // Get the key code
		keyEvent.IsPressed = (uMsg == WM_KEYDOWN); // Check if the key is pressed or released
		KeyEvents.push_back(keyEvent); // Store the key event
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void RenderOneSquare::RenderOneSquare(HWND hwnd) {
	WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (!data || !data->Buffer) return;

	// Blit the buffer to the screen
	HDC hdc = GetDC(hwnd);

	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = data->Width;
	bmi.bmiHeader.biHeight = -static_cast<int>(data->Height); // Top-down bitmap
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	StretchDIBits(
		hdc,
		0, 0, data->Width, data->Height, // dest rect
		0, 0, data->Width, data->Height, // src rect
		data->Buffer,
		&bmi,
		DIB_RGB_COLORS,
		SRCCOPY
	);

	ReleaseDC(hwnd, hdc);
}

void RenderOneSquare::RunRenderOneSquare() {
	const WCHAR* CLASS_NAME = L"MyWindowClass";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);  // Get HINSTANCE manually
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0, CLASS_NAME, L"Render One Square",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL
	);

	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};
	bool running = true;

	while (running) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				running = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		HWND hwnd = GetActiveWindow();

		RenderOneSquare::HandleInput(hwnd, 0);  // Ignore wParam, you're pulling from KeyEvents

		if (ShouldRenderFlag) {
			RenderOneSquare(hwnd);
			ShouldRenderFlag = false;
		}
	}
}

void RenderOneSquare::RandomizeOneSquare() {
	WindowData* data = (WindowData*)GetWindowLongPtr(GetActiveWindow(), GWLP_USERDATA);
	if (!data || !data->Buffer) return;
	// Randomize the square's position and color
	Square.SquareLength = rand() % (MaxSquareSize - MinSquareSize + 1) + MinSquareSize; // Random length between Min and Max
	Square.X = rand() % (data->Width - Square.SquareLength);
	Square.Y = rand() % (data->Height - Square.SquareLength);
	Square.SquareColor = RGB(rand() % 256, rand() % 256, rand() % 256);
	// Clear the buffer
	for (uint32_t i = 0; i < data->Width * data->Height; ++i) {
		data->Buffer[i] = BACKGROUND_COLOR;
	}
	// Draw the new square
	for (uint32_t y = Square.Y; y < Square.Y + Square.SquareLength; ++y) {
		for (uint32_t x = Square.X; x < Square.X + Square.SquareLength; ++x) {
			if (x < data->Width && y < data->Height) {
				data->Buffer[y * data->Width + x] = Square.SquareColor;
			}
		}
	}
}

void RenderOneSquare::HandleInput(HWND hwnd, WPARAM wParam) {
	if (KeyEvents.empty()) return; // No key events to handle
	KeyEvent OldestEvent = KeyEvents.front(); // Get the oldest key event
	KeyEvents.erase(KeyEvents.begin()); // Remove the oldest event from the buffer
	if (OldestEvent.KeyCode == VK_ESCAPE) { // If Escape key is pressed
		PostMessage(hwnd, WM_CLOSE, 0, 0); // Close the window
	}
	// process the R key event
	if (OldestEvent.KeyCode == 'R' && !OldestEvent.IsPressed) {
		RandomizeOneSquare(); // Call the function to randomize the pixel
		ShouldRenderFlag = true; //Render the Changed Pixel
	}
}


void RenderOneSquare::InitBuffer(HWND hwnd) {
	WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (!data) return; // Ensure data is valid
	// Initialize the pixel buffer with the background color
	for (uint32_t i = 0; i < data->Width * data->Height; ++i) {
		data->Buffer[i] = BACKGROUND_COLOR;
	}
	// Draw the initial square
	for (uint32_t y = Square.Y; y < Square.Y + Square.SquareLength; ++y) {
		for (uint32_t x = Square.X; x < Square.X + Square.SquareLength; ++x) {
			if (x < data->Width && y < data->Height) {
				data->Buffer[y * data->Width + x] = Square.SquareColor;
			}
		}
	}
	ShouldRenderFlag = true; // Set the flag to render the initial square
}