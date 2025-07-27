#pragma once

#include <windows.h>

namespace RenderOnePixel {

	void HandleInput(HWND hwnd, WPARAM wParam);

	void InitBuffer(HWND hwnd);

	void RandomizeOnePixel();

	void RenderOnePixel(HWND hwnd);

	void RunRenderOnePixel();

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}