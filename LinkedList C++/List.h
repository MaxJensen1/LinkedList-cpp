#pragma once
#include "Node.h"
#include <string>
#include <sstream>
#include <fstream>

template <typename T>
class List
{
private:
	Node<T>* head; // Using a pointer so save space and time. I can refer to the memory adress when I need to access the head node
	int listLength = 0;

	void SwapNodes(Node<T>* node1, Node<T>* node2);
	std::string TryParse(T input);
	Node<T>* SplitListInHalf(Node<T>* head);
	Node<T>* Merge(Node<T>* left, Node<T>* right);
	Node<T>* StartMergeSort(Node<T>* head);

public:
	List() // Constructor. It sets the head to null by default
	{
		head = nullptr;
	}

	void BubbleSort();
	void MergeSort();
	void Add(T input);
	void PrintAll();
	int GetLength();
	void Clear();
	bool Contains(T input);
	void AddTextFromFile(const std::string& fileName);
	int CountLength();
};

template<typename T>
inline void List<T>::BubbleSort() // Sorting algorithm of the type bubble sort
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
			if (TryParse(current->GetValue()) > TryParse(current->next->GetValue()))
			{
				SwapNodes(current, current->next);
			}

			// Move along the list to the next node pair
			current = current->next;
		}
	}
}

template<typename T>
inline void List<T>::MergeSort()
{
	head = StartMergeSort(head);
}

template<typename T>
inline void List<T>::SwapNodes(Node<T>* node1, Node<T>* node2)
{
	if (node1 == nullptr || node2 == nullptr) { return; } // Safety check to avoid crashes

	// Swap the value of the two nodes
	T temporary = node1->GetValue();
	node1->SetValue(node2->GetValue());
	node2->SetValue(temporary);
}

template<typename T>
inline void List<T>::Add(T input)
{
	if (head == nullptr) // If there is no head node, make one with the input data
	{
		head = new Node<T>(input);
		listLength++;
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
		listLength++;
	}
}

template<typename T>
inline void List<T>::PrintAll()
{
	Node<T>* current = head;
	while (current != nullptr) // While the current node exists, print it in the console
	{
		std::cout << TryParse(current->GetValue()) << std::endl;
		current = current->next;
	}
}

template<typename T>
inline int List<T>::GetLength()
{
	return listLength;
}

template<typename T>
inline int List<T>::CountLength()
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
	listLength = 0;
}

template<typename T>
inline bool List<T>::Contains(T input)
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current->GetValue() == input)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}

template<typename T>
void List<T>::AddTextFromFile(const std::string& fileName) 
{
	std::ifstream inputFile(fileName);
	std::string line;

	while (std::getline(inputFile, line)) 
	{
		std::stringstream stream(line);
		std::string word;

		while (stream >> word) 
		{
			// Remove any commas or periods
			if (!word.empty() && (word.back() == ',' || word.back() == '.' || word.back() == ')'))
			{
				word.pop_back();
			}
			// Add the word to the list
			Add(word);
		}
	}

	inputFile.close();
}


//template<typename T>
//inline std::string List<T>::TryParse(T input)
//{
//	std::stringstream stringStream;
//	stringStream << input; // Insert the input to the string stream
//
//	std::string result;
//	stringStream >> result; // Pull out the converted value from the stream
//
//	// Check if conversion was successful and that no characters were left
//	if (!stringStream.fail() && stringStream.eof())
//	{
//		return result;
//	}
//	else { return ""; } // Returning empty string if failed to avoid errors
//}

template<typename T>
std::string List<T>::TryParse(T input)
{
	if constexpr (std::is_arithmetic<T>::value)
	{
		// If the variable is a number, convert it to a string
		return std::to_string(input);
	}
	else if constexpr (std::is_same<T, std::string>::value)
	{
		// If the variable already is a string, there's no need to convert it
		return input;
	}
	else
	{
		// Default case for unsupported types
		std::stringstream stringStream;
		stringStream << input;
		return stringStream.str();
	}
}

template<typename T>
inline Node<T>* List<T>::SplitListInHalf(Node<T>* head)
{
	if (head == nullptr || head->next == nullptr) return nullptr; // Return if the list is empty or has only one node

	Node<T>* slowPointer = head;
	Node<T>* fastPointer = head->next;

	/* Move the fast pointer two steps and the slow pointer one
	step until the fast one is at the end of the list. This is how the middle of the list is found.*/
	while (fastPointer != nullptr && fastPointer->next != nullptr)
	{
		slowPointer = slowPointer->next;
		fastPointer = fastPointer->next->next;
	}

	Node<T>* secondHalf = slowPointer->next; // Second half starts at slowPointer->next
	slowPointer->next = nullptr; // End first half

	return secondHalf; // Return the start of the second half
}

// Used to merge two lists after they have been split and sorted
template<typename T>
Node<T>* List<T>::Merge(Node<T>* firstHalf, Node<T>* secondHalf)
{
	// If either half is null, return the other half (base case for recursion)
	if (firstHalf == nullptr) return secondHalf;
	if (secondHalf == nullptr) return firstHalf;

	// Dummy node to act as the start of the merged list
	Node<T>* mergedList = nullptr;

	// Compare the two halves and merge them accordingly
	if (TryParse(firstHalf->GetValue()) <= TryParse(secondHalf->GetValue())) 
	{
		//std::cout << "Merging 1: '" << TryParse(firstHalf->GetValue()) << "' and '" << TryParse(secondHalf->GetValue()) << "'" << std::endl;
		// First node of the first half is smaller, so link it to the merged list
		mergedList = firstHalf;
		// Recursively merge the rest of firstHalf with the secondHalf
		mergedList->next = Merge(firstHalf->next, secondHalf);
	}
	else
	{
		// First node of the second half is smaller, so link it to the merged list
		mergedList = secondHalf;
		// Recursively merge the firstHalf with the rest of secondHalf
		mergedList->next = Merge(firstHalf, secondHalf->next);
		//std::cout << "Merging 2: '" << TryParse(secondHalf->GetValue()) << "' and '" << TryParse(firstHalf->GetValue()) << "'" << std::endl;
	}

	return mergedList;
}

template<typename T>
inline Node<T>* List<T>::StartMergeSort(Node<T>* head)
{
	if (head == nullptr || head->next == nullptr) { return head; } // If there is no head (empty list) or there is only one value, it can't be sorted

	Node<T>* secondHalf = SplitListInHalf(head); // Split into two halves

	head = StartMergeSort(head); // Sort the first half
	secondHalf = StartMergeSort(secondHalf);  // Sort the second half

	return Merge(head, secondHalf); // Merge the two sorted halves and return it as one list
}