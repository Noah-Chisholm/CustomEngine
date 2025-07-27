#pragma once

#include "RenderOnePixel.h"
#include <windows.h>
#include <stdint.h>
#include <vector>

namespace RenderOnePixel {

	struct PixelLocation {
		int x;
		int y;
	};

	struct Pixel
	{
		PixelLocation loc;
		COLORREF color;
	};

	struct WindowData {
		uint32_t* Buffer; // Pointer to the pixel buffer
		uint32_t Width;  // Width of the window
		uint32_t Height; // Height of the window
	};

	struct KeyEvent {
		WPARAM KeyCode; // Key code of the pressed key
		bool IsPressed; // True if the key is pressed, false if released
	};

	Pixel ONE_PIXEL = { { 100, 100 }, RGB(255, 0, 0) }; // Example pixel at (100, 100) with red color

	//background color
	const COLORREF BACKGROUND_COLOR = RGB(0, 0, 0); // Black background

	bool CreateFlag = false;
	bool ShouldRenderFlag = false;
	std::vector<KeyEvent> KeyEvents; // Vector to store key events
}

using namespace RenderOnePixel;

LRESULT CALLBACK RenderOnePixel::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);  // Close window
        return 0;
    }
    if (uMsg == WM_CREATE) {
		WindowData* data = new WindowData();
		data->Width = 50;  // Set your desired width
		data->Height = 50; // Set your desired height
		data->Buffer = new uint32_t[data->Width * data->Height]; // Allocate pixel buffer
		CreateFlag = true; // Set the flag to indicate creation
		RenderOnePixel::InitBuffer(hwnd); // Initialize the pixel buffer with the background color
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

void RenderOnePixel::InitBuffer(HWND hwnd) {
	if (!CreateFlag) return; // Ensure the window is created
	WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (data && data->Buffer) {
		// Initialize the pixel buffer with the background color
		for (uint32_t i = 0; i < data->Width * data->Height; ++i) {
			data->Buffer[i] = BACKGROUND_COLOR;
		}
		// Set the initial pixel in the buffer
		data->Buffer[ONE_PIXEL.loc.y * data->Width + ONE_PIXEL.loc.x] = ONE_PIXEL.color; // Set the initial pixel color
	}
}

void RenderOnePixel::RenderOnePixel(HWND hwnd) {
	WindowData* data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	//update the pixel buffer with the ONE_PIXEL data

	if (data && data->Buffer) {
		HDC hdc = GetDC(hwnd);
		// Create a bitmap from the pixel buffer
		HBITMAP hBitmap = CreateBitmap(data->Width, data->Height, 1, 32, data->Buffer);
		if (hBitmap) {
			HDC hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hBitmap);
			BitBlt(hdc, 0, 0, data->Width, data->Height, hdcMem, 0, 0, SRCCOPY);
			DeleteDC(hdcMem);
			DeleteObject(hBitmap);
		}
		ReleaseDC(hwnd, hdc);
	}
}

void RenderOnePixel::RandomizeOnePixel() {
	if (!CreateFlag) return; // Ensure the window is created
	WindowData* data = (WindowData*)GetWindowLongPtr(GetActiveWindow(), GWLP_USERDATA);
	if (data && data->Buffer) {
		Pixel newPixel;
		newPixel.loc.x = rand() % data->Width; // Random x coordinate
		newPixel.loc.y = rand() % data->Height; // Random y coordinate
		newPixel.color = RGB(rand() % 256, rand() % 256, rand() % 256); // Random color
		// remove the old pixel from the buffer
		data->Buffer[newPixel.loc.y * data->Width + newPixel.loc.x] = BACKGROUND_COLOR; // Set the old pixel to black (or transparent)
		ONE_PIXEL = newPixel; // Update the global pixel
		//update the pixel buffer
		data->Buffer[newPixel.loc.y * data->Width + newPixel.loc.x] = newPixel.color; // Set the new pixel color
	}
}

void RenderOnePixel::HandleInput(HWND hwnd, WPARAM wParam) {
	if (KeyEvents.empty()) return; // No key events to handle
	KeyEvent OldestEvent = KeyEvents.front(); // Get the oldest key event
	KeyEvents.erase(KeyEvents.begin()); // Remove the oldest event from the buffer
	if (OldestEvent.KeyCode == VK_ESCAPE) { // If Escape key is pressed
		PostMessage(hwnd, WM_CLOSE, 0, 0); // Close the window
	}
	// process the R key event
	if (OldestEvent.KeyCode == 'R' && !OldestEvent.IsPressed) {
		RenderOnePixel::RandomizeOnePixel(); // Call the function to randomize the pixel
		ShouldRenderFlag = true; //Render the Changed Pixel
	}
}

// Regular function to launch your window
void RenderOnePixel::RunRenderOnePixel() {
    const WCHAR* CLASS_NAME = L"MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);  // Get HINSTANCE manually
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Render One Pixel",
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

		HandleInput(hwnd, 0);  // Ignore wParam, you're pulling from KeyEvents

		if (ShouldRenderFlag) {
			RenderOnePixel::RenderOnePixel(hwnd);
			ShouldRenderFlag = false;
		}
	}
}