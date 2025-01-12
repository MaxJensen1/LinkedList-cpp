#pragma once
#include <string>
#include <chrono>
#include <windows.h>
#include <Lmcons.h>

class Filepath
{
public:

	/// <summary>
	/// Returns the Windows user's username.
	/// </summary>
	/// <returns></returns>
	std::string Username()
	{
		char username[UNLEN + 1];
		DWORD username_len = UNLEN + 1;

		// Get the username from the system
		GetUserNameA(username, &username_len);

		return std::string(username);
	}

	/// <summary>
	/// Returns the filepath of the input file name on the desktop.
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	std::string FileFromDesktop(std::string fileName)
	{
		std::ostringstream oss;
		oss << "C:\\Users\\" << Username() << "\\Desktop\\" << fileName;
		std::string fileLocation = oss.str();
		return fileLocation;
	}
};