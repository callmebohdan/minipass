#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include "utils.hpp"

static void HandleCombinedShortOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	for (size_t j = 1; j < arg.size(); j++) {
		if (arg[j] == 'l' || arg[j] == 'c') {
			std::cerr << "Error: '-" << arg[j] << "' cannot be combined with other options. Use it separately." << std::endl;
			return;
		}
		switch (arg[j]) {
		case 'h': PrintHelp(); break;
		case 'd': passwordSettings = PasswordSettings(); break;
		case 'n': passwordSettings.removeNumbers = true; break;
		case 'o': passwordSettings.removeLowercaseLetters = true; break;
		case 's': passwordSettings.removeSpecialCharacters = true; break;
		case 'u': passwordSettings.removeUppercaseLetters = true; break;
		case 'k': passwordSettings.keepHistory = true; break;
		case 'm': passwordSettings.makeMnemonic = true; break;
		default:
			std::cerr << "Error: Entered unknown option: '-" << arg[j] << "'. Skipping it." << std::endl;
		}
	}
}

static void HandleLongOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	if (arg == "--help") {
		PrintHelp();
		exit(0);
	}
	else if (arg == "--default") {
		passwordSettings = PasswordSettings();
	}
	else if (arg == "--length") {
		if (index + 1 < argc) {
			std::string nextValue{argv[++index]};
			bool isNumeric = !nextValue.empty() && std::all_of(nextValue.begin(), nextValue.end(), ::isdigit);
			if (isNumeric) {
				passwordSettings.passwordLength = std::stoi(nextValue);
			}
			else
			{
				std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
			}
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "--custom") {
		if (index + 1 < argc) {
			passwordSettings.removeCustomCharacters = argv[++index];
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a value. Default value ('" << passwordSettings.removeCustomCharacters << "') will be used instead." << std::endl;
		}
	}
	else if (arg == "--numbers") {
		passwordSettings.removeNumbers = true;
	}
	else if (arg == "--lower") {
		passwordSettings.removeLowercaseLetters = true;
	}
	else if (arg == "--upper") {
		passwordSettings.removeUppercaseLetters = true;
	}
	else if (arg == "--special") {
		passwordSettings.removeSpecialCharacters = true;
	}
	else if (arg == "--history") {
		passwordSettings.keepHistory = true;
	}
	else if (arg == "--mnemonic") {
		passwordSettings.makeMnemonic = true;
	}
	else {
		std::cerr << "Error: Entered unknown option: '" << arg << "'. Default value will be used instead." << std::endl;
	}
}

static void HandleShortOptionsWithInputValue(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	if (arg == "-l") {
		if (index + 1 < argc) {
			std::string nextValue{argv[++index]};
			bool isNumeric = !nextValue.empty() && std::all_of(nextValue.begin(), nextValue.end(), ::isdigit);
			if (isNumeric) {
				passwordSettings.passwordLength = std::stoi(nextValue);
			}
			else
			{
				std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
			}
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "-c") {
		if (index + 1 < argc) {
			passwordSettings.removeCustomCharacters = argv[++index];
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "--help") {
		PrintHelp();
		exit(0);
	}
	else if (arg == "-d") {
		passwordSettings = PasswordSettings();
	}
	else if (arg == "-n") {
		passwordSettings.removeNumbers = true;
	}
	else if (arg == "-o") {
		passwordSettings.removeLowercaseLetters = true;
	}
	else if (arg == "-u") {
		passwordSettings.removeUppercaseLetters = true;
	}
	else if (arg == "-s") {
		passwordSettings.removeSpecialCharacters = true;
	}
	else if (arg == "-k") {
		passwordSettings.keepHistory = true;
	}
	else if (arg == "-m") {
		passwordSettings.makeMnemonic = true;
	}
	else
	{
		std::cerr << "Error: " << arg << " requires a value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
	}
}

PasswordSettings ParseCommandLineArguments(int argc, char* argv[]) {
	PasswordSettings passwordSettings;

	if (argc == 1) {
		passwordSettings.defaultSettings = true;
	}
	else {
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			if (arg.substr(0, 2) == "--") {
				HandleLongOptions(i, argc, argv, passwordSettings);
			}
			else if (arg[0] == '-' && arg[1] != '-' && arg.size() == 2) {
				HandleShortOptionsWithInputValue(i, argc, argv, passwordSettings);
			}
			else if (arg[0] == '-' && arg[1] != '-' && arg.size() > 2) {
				HandleCombinedShortOptions(i, argc, argv, passwordSettings);
			}
			else {
				std::cerr << "Error: Entered unknown option: '" << arg << "'" << std::endl;
			}
		}
	}
	return passwordSettings;
}

void PrintHelp() {
	std::cout << std::endl;

	// Platform-specific usage message
#if defined(__linux__)
	std::cout << std::endl << "Usage: ./minipass [options]" << std::endl;
#elif defined (_WIN32) || defined(_WIN64)
	std::cout << std::endl << "Usage: .\\minipass.exe [options]" << std::endl;
#endif

	std::cout << "Options:" << std::endl;
	std::cout << "-h, --help           | Show this help message and exit." << std::endl;
	std::cout << "-d, --default        | Generate a password with default settings (length = 16, all options enabled)." << std::endl;
	std::cout << "-l N, --length N     | Set the length of the password to N characters (default: 16)." << std::endl;
	std::cout << "-n, --numbers        | Exclude numbers from the password." << std::endl;
	std::cout << "-o, --lower          | Exclude lowercase letters from the password." << std::endl;
	std::cout << "-u, --upper          | Exclude uppercase letters from the password." << std::endl;
	std::cout << "-s, --special        | Exclude special characters from the password." << std::endl;
	std::cout << "-k, --history		   | Save generated passwords in history." << std::endl;
	std::cout << "-m, --mnemonic       | Create a mnemonic password (a password that is easier to remember)." << std::endl;
	std::cout << "-c STR, --custom STR | Exclude specific characters from the password. STR is a string of characters to exclude." << std::endl;
	std::cout << std::endl;
}
