#pragma once
#include <iostream>
#include "List.h"
#include <string>
#include <chrono>

int main()
{
	List<std::string> list2;

	auto start = std::chrono::high_resolution_clock::now();

	list2.AddTextFromFile("C:\\Users\\Max\\Desktop\\text.txt");
	list2.MergeSort();

	auto end = std::chrono::high_resolution_clock::now();
	list2.PrintAll();

	std::chrono::duration<double> elapsed = end - start;
	std::cout << "\nList length: " << list2.GetLength() << std::endl;
	std::cout << "Operation took " << elapsed.count() << " seconds." << std::endl;
}