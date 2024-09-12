#pragma once
#include "Node.h"

template <typename T>
class List 
{
private:
	void SwapNodes();
	Node<T> *head;

public:
	List() 
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
inline void List<T>::Sort()
{
}

template<typename T>
inline void List<T>::Add(T input)
{
	if (head == nullptr) // If there is no data in the head node, make it the first
	{
		head = new Node(this.input);
	}
	else
	{

	}
}

template<typename T>
inline void List<T>::PrintAll()
{

}

template<typename T>
inline int List<T>::GetLength()
{
	return 0;
}

template<typename T>
inline void List<T>::Clear()
{

}

template<typename T>
inline bool List<T>::Contains(T input)
{
	return false;
}

template<typename T>
inline void List<T>::SwapNodes()
{

}
