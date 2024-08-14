#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <random>
#include <string>

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

void PrintHelp();

PasswordSettings ParseCommandLineArguments(int argc, char* argv[]);

template <typename T>
int GenerateRandomIindex(const T& inputSet) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> seedSetDistribution(0, inputSet.size() - 1);
	return seedSetDistribution(gen);
};

#endif  // UTILS_HPP