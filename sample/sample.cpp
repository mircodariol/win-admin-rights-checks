// sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <sddl.h>
#include <iostream>

// Function to check if the current user is the built-in administrator account
// Returns true if the user is the built-in administrator, false otherwise
bool IsBuiltInAdministratorAccount() {
	// Get the SID of the current user
	HANDLE tokenHandle = nullptr;
	DWORD bufferSize = 0;
	PTOKEN_USER tokenUser = nullptr;
	LPWSTR sidString = nullptr;

	// Open the access token associated with the current process
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tokenHandle)) {
		std::cerr << "Failed to open process token." << std::endl;
		return 1;
	}

	// Get the size of the buffer needed for the token information
	GetTokenInformation(tokenHandle, TokenUser, nullptr, 0, &bufferSize);
	tokenUser = (PTOKEN_USER)malloc(bufferSize);

	// Get the token information
	if (!GetTokenInformation(tokenHandle, TokenUser, tokenUser, bufferSize, &bufferSize)) {
		std::cerr << "Failed to get token information." << std::endl;
		CloseHandle(tokenHandle);
		free(tokenUser);
		return 1;
	}

	// Convert the SID to a string
	if (!ConvertSidToStringSid(tokenUser->User.Sid, &sidString)) {
		std::cerr << "Failed to convert SID to string." << std::endl;
		CloseHandle(tokenHandle);
		free(tokenUser);
		return 1;
	}

	// Output the SID
	std::wcout << L"Current user SID: " << sidString << std::endl;

	// If the SID ends with -500, this means that the user is an administrator
	auto isBuiltInAdministrator = wcsstr(sidString, L"-500") != nullptr;

	// Clean up
	LocalFree(sidString);
	CloseHandle(tokenHandle);
	free(tokenUser);

	return isBuiltInAdministrator;
}

// Function to check if User Account Control (UAC) is disabled
// Returns true if UAC is disabled, false otherwise
static bool IsUserAccountControlDisabled() {
	int uacState = 0;
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		DWORD uacValue = 0;
		DWORD uacValueSize = sizeof(uacValue);

		if (RegQueryValueEx(hKey, L"EnableLUA", NULL, NULL, (LPBYTE)&uacValue, &uacValueSize) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			throw std::exception("Failed to query UAC value.");
		}

		RegCloseKey(hKey);
		return uacValue == 0;
	}
	else {
		throw std::exception("Failed to open registry key.");
	}
}

// Application entry-point
int main()
{
	try {
		auto isBuiltInAdministrator = IsBuiltInAdministratorAccount();
		auto isUACDisabled = IsUserAccountControlDisabled();

		if (isBuiltInAdministrator) {
			std::wcout << L"User is the Windows system built-in administrator." << std::endl;
		}
		else {
			std::wcout << L"User is not the Windows system built-in administrator." << std::endl;
		}

		std::cout << "UAC state: " << ((isUACDisabled) ? "Disabled" : "Enabled") << std::endl;

		if (isBuiltInAdministrator) {
			// Promp a message box to ask the user if he wants more information about why its dangerous to use the built-in administrator account
			// if the user want receive more information about, open a browser instance to a link with more details:
			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Using the Windows system built-in administrator account is dangerous. Do you want to know why?",
				(LPCWSTR)L"Warning",
				MB_ICONWARNING | MB_YESNO
			);

			if (msgboxID == IDYES) {
				ShellExecute(NULL, L"open", L"https://answers.microsoft.com/en-us/windows/forum/all/to-use-or-not-to-use-the-administrator-account-on/01bbf467-2250-e011-8dfc-68b599b31bf5", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		else if (isUACDisabled) {
			// Promp a message box to ask the user if he wants more information about why its dangerous to disable the UAC on Windows
			// if the user want receive more information about, open a browser instance to a link with more details:
			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Disabling the UAC on Windows is dangerous. Do you want to know why?",
				(LPCWSTR)L"Warning",
				MB_ICONWARNING | MB_YESNO
			);

			if (msgboxID == IDYES) {
				ShellExecute(NULL, L"open", L"https://www.howtogeek.com/124754/htg-explains-why-you-shouldnt-disable-uac/", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		else {
			std::cout << "Everything seems to be good." << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
