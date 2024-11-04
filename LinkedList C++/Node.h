#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
	// Constructor. It's faster to define the variables like this when creating the function instead of inside the funciton.
	Node(T inputValue) : value(inputValue), next(nullptr) {}

	Node* next; // Pointer to next node
	T value;

	void SetValue(T inputValue)  // Setter, to be able to change the value
	{
		value = inputValue;
	}
};