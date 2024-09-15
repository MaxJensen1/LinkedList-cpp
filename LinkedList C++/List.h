#pragma once
#include "Node.h"
#include <string>
#include <sstream>

template <typename T>
class List
{
private:
	Node<T>* head; // Using a pointer so save space and time. I can refer to the memory adress when I need to access the head node
	void SwapNodes(Node<T>* node1, Node<T>* node2);
	std::string TryParse(T input);

public:
	List() // Constructor. It sets the head to null by default
	{
		head = nullptr;
	}

	void Sort();
	void Add(T input);
	void PrintAll();
	int GetLength();
	void Clear();
	bool Contains(T input);
};

template<typename T>
inline void List<T>::Sort() // Sorting algorithm of the type bubble sort
{
	if (GetLength() < 2) // Can't sort a list with only one or no elements in it
	{
		return;
	}

	// Move along the list the same amount of times as values in the list
	for (int i = 0; i < GetLength() - 1; i++)
	{
		Node<T>* current = head;

		// Go through the list to compare each value with the next one
		while (current != nullptr && current->next != nullptr)
		{
			if (TryParse(current->getValue()) > TryParse(current->next->getValue()))
			{
				SwapNodes(current, current->next);
			}

			// Move along the list to the next node pair
			current = current->next;
		}
	}
}

template<typename T>
inline void List<T>::SwapNodes(Node<T>* node1, Node<T>* node2)
{
	if (node1 == nullptr || node2 == nullptr) return;  // Safety check to avoid crashes

	// Swap the value of the two nodes
	T temporary = node1->getValue();
	node1->setValue(node2->getValue());
	node2->setValue(temporary);
}

template<typename T>
inline void List<T>::Add(T input)
{
	if (head == nullptr) // If there is no head node, make one with the input data
	{
		head = new Node<T>(input);
	}
	else // Moves along the list until the next node is null (meaning that the end has been reached)
	{
		Node<T>* current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}

		// Add the input at the end of the list
		current->next = new Node<T>(input);
	}
}

template<typename T>
inline void List<T>::PrintAll()
{
	Node<T>* current = head;
	while (current != nullptr) // While the current node exists, print it in the console
	{
		std::cout << TryParse(current->getValue()) << std::endl;
		current = current->next;
	}
}

template<typename T>
inline int List<T>::GetLength()
{
	int count = 0;
	Node<T>* current = head;

	while (current != nullptr) // Move along the lsit until the end is reached and count while doing it
	{
		count++;
		current = current->next;
	}

	return count;
}

template<typename T>
inline void List<T>::Clear()
{
	Node<T>* current = head;

	while (current != nullptr) // Move along the list and temporarily save the next node so it can still be accessed after current has been deleted. 
	{
		Node<T>* nextNode = current->next;
		delete current;
		current = nextNode;
	}

	// Can't delete head because then the list would be gone, but I can set it to null so it's empty. 
	head = nullptr;
}

template<typename T>
inline bool List<T>::Contains(T input)
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current->getValue() == input)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

template<typename T>
inline std::string List<T>::TryParse(T input)
{
	std::stringstream stringStream;
	stringStream << input;  // Insert the input to the string stream

	std::string result;
	stringStream >> result;  // Pull out the converted value from the stream

	// Check if conversion was successful and that no characters were left
	if (!stringStream.fail() && stringStream.eof())
	{
		return result;
	}
	else { return ""; } // Returning empty string if failed to avoid errors
}