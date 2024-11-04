#pragma once
#include "Node.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <type_traits>
#include <thread>

template <typename T>
class List
{
private:
	Node<T>* head; // Using a pointer so save space and time. I can refer to the memory adress when I need to access the head node
	Node<T>* tail; // A pointer that keeps track of the end of the list. Saves time because the program no longer has to loop through the lsit to find the end
	int listLength = 0;
	char bannedCharacters[7] = { ',', '.', '(', ')', '"', ';', ':' };

	void SwapNodes(Node<T>* node1, Node<T>* node2);
	Node<T>* SplitListInHalf(Node<T>* head);
	Node<T>* Merge(Node<T>* left, Node<T>* right);
	Node<T>* StartMergeSort(Node<T>* head, int threadDepth);
	T Parse(T value);

public:
	List() // Constructor. It sets the head to null by default
	{
		head = nullptr;
		tail = nullptr;
	}

	void BubbleSort();
	void MergeSort();
	void AddAtTail(T input);
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
		while (current && current->next)
		{
			if (Parse(current->value) > Parse(current->next->value))
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
	head = StartMergeSort(head, 2); // Input head node and how deep multithreading should go
}

template<typename T>
inline void List<T>::SwapNodes(Node<T>* node1, Node<T>* node2)
{
	if (!node1 || !node2) { return; } // Safety check to avoid crashes

	// Swap the value of the two nodes
	T temporary = node1->value;
	node1->SetValue(node2->value);
	node2->SetValue(temporary);
}

template<typename T>
inline void List<T>::AddAtTail(T input)
{
	if constexpr (std::is_same<T, std::string>::value)
	{
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	}
	else if (std::is_same<T, char>::value)
	{
		input = std::tolower(input);
	}

	if (!head) // If there is no head node, make the new node the head and tail
	{
		head = new Node<T>(input);
		tail = head;  // Since it's the only node, it's also the tail
	}
	else // Add the new node to the tail
	{
		tail->next = new Node<T>(input); // Link the new node to the last node
		tail = tail->next;       // Update the tail to be the new node
	}

	listLength++;
}

template<typename T>
inline void List<T>::PrintAll()
{
	Node<T>* current = head;
	while (current) // While the current node isn't null, print it in the console
	{
		std::stringstream stringStream;
		stringStream << current->value;
		std::cout << stringStream.str() << "\n";
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

	while (current) // Move along the lsit until the end is reached and count while doing it
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

	while (current) // Move along the list and temporarily save the next node so it can still be accessed after current has been deleted. 
	{
		Node<T>* nextNode = current->next;
		delete current;
		current = nextNode;
	}

	// Can't delete head because then the list would be gone, but I can set it to null so it's empty. 
	head = nullptr;
	tail = nullptr;
	listLength = 0;
}

template<typename T>
inline bool List<T>::Contains(T input)
{
	Node<T>* current = head;
	while (current)
	{
		if (current->value == input)
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

	while (std::getline(inputFile, line)) // Get one line at a time from the file
	{
		std::stringstream stream(line); // Create a stringstream from the line
		std::string word;

		while (stream >> word) // Get one word at a time from the stream
		{
			// Remove any unwanted symbols from words
			for (uint16_t i = 0; i < sizeof(bannedCharacters); i++) 
			{
				while (!word.empty() && word.back() == bannedCharacters[i]) // The end of words
				{
					word.pop_back();
				}
				while (!word.empty() && word.front() == bannedCharacters[i]) // The front of words
				{
					word.pop_back();
				}
			}
			
			// Convert the word to lowercase
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);

			// Add the word to the list if it is not empty
			if (!word.empty())
			{
				AddAtTail(word);
			}
		}
	}

	inputFile.close();
}

template<typename T>
inline Node<T>* List<T>::SplitListInHalf(Node<T>* head)
{
	if (!head || !head->next) { return nullptr; } // Can't split if the list is empty or has only one node

	Node<T>* slowPointer = head;
	Node<T>* fastPointer = head->next;

	/* Move the fast pointer two steps and the slow pointer one
	step until the fast one is at the end of the list. This is how the middle of the list is found.*/
	while (fastPointer && fastPointer->next)
	{
		fastPointer = fastPointer->next->next;
		slowPointer = slowPointer->next;
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
	if (!firstHalf) { return secondHalf; }
	if (!secondHalf) { return firstHalf; }

	// Dummy node to act as the start of the merged list
	Node<T>* mergedList = nullptr;

	// Compare the two halves and merge them accordingly
	if ((firstHalf->value) <= (secondHalf->value)) 
	{
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
	}

	return mergedList;
}

template<typename T>
inline Node<T>* List<T>::StartMergeSort(Node<T>* head, int threadDepth)
{
	if (!head || !head->next) { return head; } // If there is no head (empty list) or there is only one value, it can't be sorted

	Node<T>* secondHalf = SplitListInHalf(head); // Split into two halves

	// It will use threads when starting the split sorting if the variable is greater than 0. Its value determines how deep in the sorting multithreading will be utilized
	if (threadDepth > 0)
	{
		threadDepth--;

		// Important to include all variables the lambda function is allowed to access and change. Doesn't work otherwise
		std::thread firstHalfThread([this, &head, threadDepth]()
		{
			head = StartMergeSort(head, threadDepth); // Sort the first half (sequentially)
		});

		std::thread secondHalfThread([this, &secondHalf, threadDepth]()
		{
			secondHalf = StartMergeSort(secondHalf, threadDepth);  // Sort the second half (sequentially)
		});

		// Wait for both threads to finish
		firstHalfThread.join();
		secondHalfThread.join();
	}
	else
	{
		head = StartMergeSort(head, threadDepth); // Sort the first half
		secondHalf = StartMergeSort(secondHalf, threadDepth);  // Sort the second half
	}

	return Merge(head, secondHalf); // Merge the two sorted halves and return it as one list
}

// Slows down the algorithm quite a lot, only use if absolutely nessacry
template<typename T>
inline T List<T>::Parse(T value)
{
	T tempValue = value; // A copy of the value to return

	if constexpr (std::is_same<T, std::string>::value)
	{
		std::transform(tempValue.begin(), tempValue.end(), tempValue.begin(), ::tolower); // If the variabe is a string, it to lowercase
	}
	else if constexpr (std::is_same<T, char>::value)
	{
		tempValue = std::tolower(tempValue); // If it's a char, convert it to lowercase
	}
	else if constexpr (std::is_arithmetic<T>::value) // If the type is arithmetic (number), do nothing
	{
		// Do nothing for numbers
	}

	return tempValue;
}