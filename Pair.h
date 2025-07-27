#pragma once

#include <stdint.h>

struct Pair32
{
	uint32_t X; // X coordinate
	uint32_t Y; // Y coordinate

	Pair32 operator + (const Pair32& other) const {
		return Pair32{ X + other.X, Y + other.Y }; // Addition operator to add pairs
	}

	Pair32 operator - (const Pair32& other) const {
		return Pair32{ X - other.X, Y - other.Y }; // Subtraction operator to subtract pairs
	}

	Pair32 operator * (const Pair32& other) const {
		return Pair32{ X * other.X, Y * other.Y }; // Multiplication operator to multiply pairs
	}

	Pair32 operator / (const Pair32& other) const {
		return Pair32{ X / other.X, Y / other.Y }; // Division operator to divide pairs
	}

	Pair32 operator += (const Pair32& other) {
		X += other.X; // Add the X coordinates
		Y += other.Y; // Add the Y coordinates
		return *this; // Return the modified pair
	}

	Pair32 operator -= (const Pair32& other) {
		X -= other.X; // Subtract the X coordinates
		Y -= other.Y; // Subtract the Y coordinates
		return *this; // Return the modified pair
	}

	Pair32 operator *= (const Pair32& other) {
		X *= other.X; // Multiply the X coordinates
		Y *= other.Y; // Multiply the Y coordinates
		return *this; // Return the modified pair
	}

	Pair32 operator /= (const Pair32& other) {
		X /= other.X; // Divide the X coordinates
		Y /= other.Y; // Divide the Y coordinates
		return *this; // Return the modified pair
	}

	bool operator == (const Pair32& other) const {
		return X == other.X && Y == other.Y; // Equality operator to compare pairs
	}

	bool operator != (const Pair32& other) const {
		return !(*this == other); // Inequality operator to compare pairs
	}

	bool operator < (const Pair32& other) const {
		return (X < other.X) && Y < other.Y; // Less than operator to compare pairs
	}

	bool operator > (const Pair32& other) const {
		return (X > other.X) && (Y > other.Y); // Greater than operator to compare pairs
	}

	bool operator <= (const Pair32& other) const {
		return (X <= other.X) && (Y <= other.Y); // Less than or equal to operator to compare pairs
	}

	bool operator >= (const Pair32& other) const {
		return (X >= other.X) && (Y >= other.Y); // Greater than or equal to operator to compare pairs
	}
};

struct Pair16
{
	uint16_t X;// X coordinate
	uint16_t Y; // Y coordinate

	Pair16 operator + (const Pair16& other) const {
		return Pair16{ X + other.X, Y + other.Y }; // Addition operator to add pairs
	}

	Pair16 operator - (const Pair16& other) const {
		return Pair16{ X - other.X, Y - other.Y }; // Subtraction operator to subtract pairs
	}

	Pair16 operator * (const Pair16& other) const {
		return Pair16{ X * other.X, Y * other.Y }; // Multiplication operator to multiply pairs
	}

	Pair16 operator / (const Pair16& other) const {
		return Pair16{ X / other.X, Y / other.Y }; // Division operator to divide pairs
	}

	Pair16 operator += (const Pair16& other) {
		X += other.X; // Add the X coordinates
		Y += other.Y; // Add the Y coordinates
		return *this; // Return the modified pair
	}	

	Pair16 operator -= (const Pair16& other) {
		X -= other.X; // Subtract the X coordinates
		Y -= other.Y; // Subtract the Y coordinates
		return *this; // Return the modified pair
	}

	Pair16 operator *= (const Pair16& other) {
		X *= other.X; // Multiply the X coordinates
		Y *= other.Y; // Multiply the Y coordinates
		return *this; // Return the modified pair
	}

	Pair16 operator /= (const Pair16& other) {
		X /= other.X; // Divide the X coordinates
		Y /= other.Y; // Divide the Y coordinates
		return *this; // Return the modified pair
	}

	bool operator == (const Pair16& other) const {
		return X == other.X && Y == other.Y; // Equality operator to compare pairs
	}

	bool operator != (const Pair16& other) const {
		return !(*this == other); // Inequality operator to compare pairs
	}

	bool operator < (const Pair16& other) const {
		return (X < other.X) && Y < other.Y; // Less than operator to compare pairs
	}

	bool operator > (const Pair16& other) const {
		return (X > other.X) && (Y > other.Y); // Greater than operator to compare pairs
	}

	bool operator <= (const Pair16& other) const {
		return (X <= other.X) && (Y <= other.Y); // Less than or equal to operator to compare pairs
	}

	bool operator >= (const Pair16& other) const {
		return (X >= other.X) && (Y >= other.Y); // Greater than or equal to operator to compare pairs
	}
};

template <typename I1, typename I2>
struct Pair
{
	I1 First; // First element of the pair
	I2 Second; // Second element of the pair

	Pair(I1 first, I2 second) : First(first), Second(second) {} // Constructor to initialize the pair

	operator == (const Pair<I1, I2>& other) const {
		return First == other.First && Second == other.Second; // Equality operator to compare pairs
	}

	operator != (const Pair<I1, I2>& other) const {
		return !(*this == other); // Inequality operator to compare pairs
	}

	operator + (const Pair<I1, I2>& other) const {
		return Pair<I1, I2>(First + other.First, Second + other.Second); // Addition operator to add pairs
	}

	operator - (const Pair<I1, I2>& other) const {
		return Pair<I1, I2>(First - other.First, Second - other.Second); // Subtraction operator to subtract pairs
	}

	operator * (const Pair<I1, I2>& other) const {
		return Pair<I1, I2>(First * other.First, Second * other.Second); // Multiplication operator to multiply pairs
	}

	operator / (const Pair<I1, I2>& other) const {
		return Pair<I1, I2>(First / other.First, Second / other.Second); // Division operator to divide pairs
	}

	operator += (const Pair<I1, I2>& other) {
		First += other.First; // Add the first elements
		Second += other.Second; // Add the second elements
		return *this; // Return the modified pair
	}

	operator -= (const Pair<I1, I2>& other) {
		First -= other.First; // Subtract the first elements
		Second -= other.Second; // Subtract the second elements
		return *this; // Return the modified pair
	}

	operator *= (const Pair<I1, I2>& other) {
		First *= other.First; // Multiply the first elements
		Second *= other.Second; // Multiply the second elements
		return *this; // Return the modified pair
	}

	operator /= (const Pair<I1, I2>& other) {
		First /= other.First; // Divide the first elements
		Second /= other.Second; // Divide the second elements
		return *this; // Return the modified pair
	}
};