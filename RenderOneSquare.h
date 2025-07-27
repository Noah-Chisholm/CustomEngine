#pragma once
#include <Windows.h>

namespace RenderOneSquare {

	void RunRenderOneSquare();

	void HandleInput(HWND hwnd, WPARAM wParam);

	void InitBuffer(HWND hwnd);

	void RenderOneSquare(HWND hwnd);

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void RandomizeOneSquare();
}