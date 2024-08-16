#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <random>
#include <string>

template <typename T>
int GenerateRandomIndex(const T& inputSet) {
	if (inputSet.empty()) {
		throw std::out_of_range("Input set is empty, cannot generate a random index.");
	}
	
	std::random_device rd;
	std::mt19937 gen(rd());
	size_t size = inputSet.size() - 1;
	std::uniform_int_distribution<size_t> seedSetDistribution(0, size);
	
	size_t index = seedSetDistribution(gen);

	if (index > std::numeric_limits<int>::max()) {
		throw std::overflow_error("Generated index is too large to fit in an int.");
	}

	return static_cast<int>(index);
};

struct PasswordSettings {
	uint32_t passwordLength = 16;
	bool defaultSettings = true;
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