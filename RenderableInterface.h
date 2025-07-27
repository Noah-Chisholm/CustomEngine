#pragma once

#include <stdint.h>
#include "Pair.h"
#include <Windows.h>
#include <string>
#include <stdexcept>
#include <fstream>

class RenderableInterface {
public:
	RenderableInterface() = default; // Default constructor
	RenderableInterface(const Pair16& origin, const Pair16& location, uint16_t layer = 0, COLORREF tint = RGB(255, 255, 255), std::string Path)
		: Origin(origin), Location(location), layer(layer), Tint(tint), Path(Path) {
		// Initialize the renderable object with the provided parameters
		loadData(); // Load the bitmap data from the specified path
	} // Parameterized constructor
protected:
	// Pure virtual function to render the object
	uint16_t layer = 0; // Layer for rendering order, default is 0
	float Scale = 1.0f; // Scale factor for rendering, default is 1.0f
	float Rotation = 0.0f; // Rotation angle in degrees, default is 0.0f
	Pair16 Origin; // Origin of the renderable object
	Pair16 Size = { 0, 0 }; // Size of the renderable object, default is {0, 0}
	Pair16 Location; // Location of the renderable object
	COLORREF Tint = RGB(255, 255, 255); // Tint color for rendering, default is white
	std::string Path = nullptr; // Path to the resource, default is nullptr
	BITMAPINFO* data = nullptr; // Pointer to bitmap data, default is nullptr
	void loadData();
	virtual BITMAPINFO* Render();
public:
	enum OrginPresets {
		OriginTopLeft = 0, // Origin at the top-left corner
		OriginCenter = 1, // Origin at the center of the object
		OriginBottomRight = 2 // Origin at the bottom-right corner
	};

	void rotate(float angle);
	void setScale(float scale);
	void setLocation(const Pair16& location);
	void setOrigin(const Pair16& origin);
	void setLayer(uint16_t newLayer);
	void setOriginPreset(OrginPresets preset);
	void setTint(COLORREF tint);
	void setPath(const std::string& path);
};