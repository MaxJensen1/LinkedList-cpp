#pragma once
#include <iostream>

template <typename T>
class Node
{
private:
	T value;
	Node *next; // Pointer to next node

public:
	// Constructor. It's faster to define the variables like this when creating the function instead of inside the funciton.
	Node(T inputValue) : value(inputValue), next(nullptr) {} 

	void getValue() // Getter, so you can see the value.
	{
		return value;
	}

	void setValue(T inputValue)  // Setter, to be able to change values if needed
	{
		value = inputValue;
	}
};
	