#include "RenderableInterface.h"

void RenderableInterface::loadData()
{
	// Load the bitmap data from the specified path
	// This function should be implemented to load the bitmap data into 'data'
	if (Path.empty()) {
		data = nullptr; // If no path is specified, set data to nullptr
		throw std::runtime_error("Resource Path Must be Provided"); // Throw an error if the path is empty
		return; // Exit if no path is provided
	}
	std::fstream file(Path, std::ios::binary); // Open the file in binary mode
	if (!file) {
		data = nullptr; // If the file cannot be opened, set data to nullptr
		throw std::runtime_error("Failed to open resource file: " + Path); // Throw an error if the file cannot be opened
		return; // Exit if the file cannot be opened
	}
}

BITMAPINFO* RenderableInterface::Render() {
	if (data) {
		return data;
	}
	else {
		loadData(); // Load the data if it is not already loaded
	}
}

void RenderableInterface::rotate(float angle)
{
	Rotation += angle; // Update the rotation angle
	if (Rotation >= 360.0f) Rotation -= 360.0f; // Normalize the rotation angle
	
}

void RenderableInterface::setScale(float scale)
{
	Scale = scale; // Set the scale factor
	if (Scale <= 0.0f) {
		throw std::invalid_argument("Scale must be greater than zero"); // Ensure scale is positive
	}
	Size.X = static_cast<uint16_t>(Size.X * Scale); // Update the width based on the scale
	Size.Y = static_cast<uint16_t>(Size.Y * Scale); // Update the height based on the scale
	data->bmiHeader.biWidth = Size.X; // Update the bitmap width
	data->bmiHeader.biHeight = -static_cast<int>(Size.Y); // Update the bitmap height (top-down)
	data->bmiHeader.biSizeImage = Size.X * Size.Y * 4; // Update the size of the bitmap image
	StretchBlt(
		GetDC(NULL), // Get the device context for the entire screen
		Location.X, Location.Y, Size.X, Size.Y, // Destination rectangle
		GetDC(NULL), // Source device context
		0, 0, data->bmiHeader.biWidth, -data->bmiHeader.biHeight, // Source rectangle
		SRCCOPY // Copy the source to the destination
	); // Stretch the bitmap to the new size
}

void RenderableInterface::setLocation(const Pair16& location)
{
	Location = location; // Set the location of the renderable object
}

void RenderableInterface::setOrigin(const Pair16& origin)
{
	Origin = origin; // Set the origin of the renderable object
}

void RenderableInterface::setLayer(uint16_t newLayer)
{
	layer = newLayer; // Set the layer for rendering order
}

void RenderableInterface::setOriginPreset(OrginPresets preset)
{
	switch (preset) {
	case OriginTopLeft:
		Origin = { 0, 0 }; // Set origin to top-left corner
		break;
	case OriginCenter:
		Origin = { Size.X / 2, Size.Y / 2 }; // Set origin to center
		break;
	case OriginBottomRight:
		Origin = { Size.X, Size.Y }; // Set origin to bottom-right corner
		break;
	}
}

void RenderableInterface::setTint(COLORREF tint)
{
	Tint = tint; // Set the tint color for rendering
	for(auto& pixel : data->bmiColors) {
		pixel.rgbRed = GetRValue(tint); // Set the red component of the tint
		pixel.rgbGreen = GetGValue(tint); // Set the green component of the tint
		pixel.rgbBlue = GetBValue(tint); // Set the blue component of the tint
	}
}

void RenderableInterface::setPath(const std::string& path)
{
	Path = path; // Set the path to the resource
	loadData(); // Load the bitmap data from the new path
}