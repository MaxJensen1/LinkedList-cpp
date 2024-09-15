#pragma once
#include <iostream>
#include "List.h"
#include <string>

int main()
{
	List<std::string> list;
	list.Add("dfdf");
	list.Add("12s");
	list.Add("1.4");
	list.Add("1.7");
	list.Add("0.5");
	list.Add("12g");

	list.PrintAll();
	list.Sort();
	std::cout << std::endl;
	list.PrintAll();
}