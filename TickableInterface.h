#pragma once

class TickableInterface {
public:
	virtual ~TickableInterface() = default;
	// Called every frame to update the state of the object
	virtual void Tick(float deltaTime) = 0;
	// Optional: Called when the object is initialized
	virtual void Initialize() {}
	// Optional: Called when the object is destroyed
	virtual void Shutdown() {}

	bool Active = true; // Flag to indicate if the object is active
	virtual bool IsActive() const = 0; // Check if the object is active
};