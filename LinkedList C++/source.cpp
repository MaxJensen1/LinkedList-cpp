#pragma once
#include <iostream>
#include "List.h"
#include <string>
#include <chrono>

int main()
{
	List<std::string> list;
	list.AddTextFromFile("C:\\Users\\Max\\Desktop\\text.txt");

	// Counting the time the sorting algorithm takes
	auto start = std::chrono::high_resolution_clock::now();
	list.MergeSort();
	auto end = std::chrono::high_resolution_clock::now();

	list.PrintAll();

	std::chrono::duration<double> elapsed = end - start;
	std::cout << "\nList length: " << list.CountLength() << std::endl;
	std::cout << "Operation took " << elapsed.count() << " seconds." << std::endl;
}