#pragma once
#include "Node.h"
#include <string>

template <typename T>
class List
{
private:
    void SwapNodes(Node<T>* node1, Node<T>* node2);
    Node<T> head;

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
inline void List<T>::SwapNodes(Node<T>* node1, Node<T>* node2)
{
}

template<typename T>
inline void List<T>::Sort()
{
    if (GetLength() < 2) // Can't sort a list with only one element
    {
        return;
    }


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
        std::string messageToPrint = std::to_string(current->getValue());
        std::cout << messageToPrint << std::endl;
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