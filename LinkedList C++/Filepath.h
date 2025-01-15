#pragma once
#include <string>
#include <chrono>
#include <windows.h>
#include <Lmcons.h>

class Filepath
{
public:
	enum FilepathEnum
	{
		DESKTOP,
		DOCUMENTS,
		DOWNLOADS,
		VIDEOS
	};

protected:
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

	std::string EnumToPath(FilepathEnum fileLocation)
	{
		std::string basePath = "C:\\Users\\" + Username() + "\\";

		switch (fileLocation)
		{
		case DESKTOP:
			return basePath + "Desktop\\";

		case DOCUMENTS:
			return basePath + "Documents\\";

		case DOWNLOADS:
			return basePath + "Downloads\\";

		case VIDEOS:
			return basePath + "Videos\\";

		default:
			throw std::invalid_argument("Invalid FilepathEnum value");
		}
	}
};