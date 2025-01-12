#include <iostream>
#include "List.h"
#include <string>
#include <chrono>
#include <windows.h>
#include <Lmcons.h>
#include "Filepath.h"

int main()
{
	int testRuns = 100;
	double totalTime = 0;
	Filepath file;

	for (int i = 0; i < testRuns; i++)
	{
		// Create the list isnide the loop so it is reset every test run.
		List<std::string> list;
		list.AddTextFromFile(file.FileFromDesktop("text.txt"));

		// Counting the time the sorting algorithm takes
		auto start = std::chrono::high_resolution_clock::now();
		list.MergeSort();
		auto end = std::chrono::high_resolution_clock::now();

		// Prints the whole sorted list (commented out to save time).
		//list.PrintAll();

		std::chrono::duration<double> elapsed = end - start;
		totalTime += elapsed.count();
		std::cout << "Sorted " << list.GetLength() << " words in " << elapsed.count() << " seconds.\n";
	}

	double averageTime = totalTime / testRuns;
	std::cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
	std::cout << "Sorted " << testRuns << " times. Average time to sort: " << averageTime << " seconds(" << averageTime * 1000 << " milliseconds)." << std::endl;
}