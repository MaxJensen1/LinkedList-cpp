#include <iostream>
#include "List.h"
#include <string>
#include <chrono>
#include <windows.h>
#include <Lmcons.h>

std::string Username();
std::string FileFromDesktop(std::string fileName);

int main()
{
	uint8_t testRuns = 10;
	double totalTime = 0;

	for (int i = 0; i < testRuns; i++)
	{
		//list.Scramble(list.GetLength()*2);	
		List<std::string> list;
		list.AddTextFromFile(FileFromDesktop("text.txt"));

		// Counting the time the sorting algorithm takes
		auto start = std::chrono::high_resolution_clock::now();
		list.MergeSort();
		auto end = std::chrono::high_resolution_clock::now();

		//list.PrintAll();

		std::chrono::duration<double> elapsed = end - start;
		totalTime += elapsed.count();
		std::cout << "Sorted " << list.GetLength() << " words in " << elapsed.count() << " seconds.\n";
	}

	std::cout << "\nAverage time to sort: " << totalTime / testRuns << " seconds." << std::endl;
}

std::string Username()
{
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;

    // Get the username from the system
    GetUserNameA(username, &username_len);
    
	return std::string(username);
}

std::string FileFromDesktop(std::string fileName)
{
	std::ostringstream oss;
	oss << "C:\\Users\\" << Username() << "\\Desktop\\" << fileName;
	std::string fileLocation = oss.str();
	return fileLocation;
}