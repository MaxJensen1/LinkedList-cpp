#include <iostream>
#include "List.h"
#include <string>
#include <chrono>
#include <windows.h>
#include <Lmcons.h>

// Forward declaration
void SpeedTesting();
void RemoveTest();

int main()
{
	SpeedTesting();
	//RemoveTest(); // Ignore this, it was for testing new features.
}

void RemoveTest()
{
	List<int> list;
	list.AddAtTail(1);
	list.AddAtTail(2);
	list.AddAtTail(3);
	list.AddAtTail(4);

	std::cout << "Unmodified:" << std::endl;
	list.PrintAll();

	std::cout << "\nModified:" << std::endl;
	list.ReverseOrder();
	list.AddAtIndex(8, 3);
	list.PrintAll();
	std::cout << "" << std::endl;

	std::cout << "\nRemoved from to" << std::endl;
	list.RemoveFromTo(0, 1);
	list.PrintAll();
}

void SpeedTesting()
{
	int testRuns = 100;
	double totalTime = 0;

	for (int i = 0; i < testRuns; i++)
	{
		// Create the list isnide the loop so it is reset every test run.
		List<std::string> list;
		list.AddTextFromFile(list.DESKTOP, "text");

		// Counting the time the sorting algorithm takes
		auto start = std::chrono::high_resolution_clock::now();
		list.MergeSort();
		auto end = std::chrono::high_resolution_clock::now();

		// Prints the whole sorted list (commented out to save time).
		//list.PrintAll();
		list.WriteOutputToFile(list.DESKTOP, "cppOutput");

		std::chrono::duration<double> elapsed = end - start;
		totalTime += elapsed.count();
		std::cout << "Sorted " << list.GetLength() << " words in " << elapsed.count() << " seconds.\n";
	}

	double averageTime = totalTime / testRuns;
	std::cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
	std::cout << "Sorted " << testRuns << " times. Average time to sort: " << averageTime << " seconds (" << averageTime * 1000 << " milliseconds)." << std::endl;
}