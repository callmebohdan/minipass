#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <random>
#include <string>

template <typename T>
int GenerateRandomIindex(const T& inputSet) {
	std::random_device rd;
	std::mt19937 gen(rd());
	size_t size = inputSet.size() - 1;
	std::uniform_int_distribution<size_t> seedSetDistribution(0, size);
	return static_cast<int>(seedSetDistribution(gen));
};

struct PasswordSettings {
	uint32_t passwordLength = 16;
	bool defaultSettings = false;
	bool removeNumbers = false;
	bool removeLowercaseLetters = false;
	bool removeUppercaseLetters = false;
	bool removeSpecialCharacters = false;
	bool makeMnemonic = false;
	bool keepHistory = false;
	std::string removeCustomCharacters = "";
};

PasswordSettings ParseCommandLineArguments(int argc, char* argv[]);

void PrintHelp();

#endif  // UTILS_HPP