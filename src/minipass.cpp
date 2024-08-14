#include <chrono>
#include <corecrt.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>
#include "../inc/minipass.hpp"
#include "../inc/utils.hpp"

std::string MiniPass::GenerateRandomMnemonicSeed(const char& ch) {
	std::string mnemonicSeed;
	std::filesystem::path filename = "../../../res/mnemonic-seeds.txt";
	std::ifstream file(filename);

	if (!std::filesystem::exists(filename)) {
		std::cerr << "File does not exist: " << filename << std::endl;
		return {};
	}

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return {};
	}

	std::vector<std::string> characterNamedSeeds;
	std::string line;

	while (std::getline(file, line)) {
		if (!line.empty() && line[0] == ch) {
			characterNamedSeeds.push_back(line);
		}
	}

	if (characterNamedSeeds.empty()) {
		std::cerr << "No words starting with '" << ch << "' found." << std::endl;
		return {};
	}

	int randomMnemonicSeedIndex = GenerateRandomIindex(characterNamedSeeds);
	std::unordered_set<int> indexCache;

	while (indexCache.find(randomMnemonicSeedIndex) != indexCache.end()) {
		randomMnemonicSeedIndex = GenerateRandomIindex(characterNamedSeeds);
	}

	indexCache.insert(randomMnemonicSeedIndex);

	return characterNamedSeeds[randomMnemonicSeedIndex];
}

std::string MiniPass::GetMnemonicPhrase() {
	return mnemonicPhrase;
}

std::string MiniPass::ApplyMnemonicFilter() {
	for (char c : password) {
		mnemonicPhrase += GenerateRandomMnemonicSeed(c) + " ";
	}
	return mnemonicPhrase;
}

std::string MiniPass::GetCurrentTime() const {
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::tm localTime = *std::localtime(&currentTime);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%D | %X");
	std::string currentTimeStr = oss.str();
	return currentTimeStr;
}

std::string MiniPass::EscapeDoubleQuotes(const std::string& str) const {
	std::string result;
	result.reserve(str.size() * 2);
	for (char c : str) {
		if (c == '"') {
			result += '"';
		}
		result += c;
	}
	return result;
}

void MiniPass::KeepHistory(const std::string& password) {
	std::fstream passwordsDB;
	passwordsDB.open("PasswordsHistory.csv", std::ios::out | std::ios::app);
	if (std::filesystem::is_empty("PasswordsHistory.csv")) {
		passwordsDB << "Date,Random Password,Mnemonic Phrase" << std::endl;
	}
	std::string quotedPassword = "\"" + EscapeDoubleQuotes(password) + "\"";
	passwordsDB << GetCurrentTime() << "," << quotedPassword << "," << GetMnemonicPhrase() << std::endl;
	passwordsDB.close();
}

std::string MiniPass::GenerateRandomPassword() {
	std::string allowedCharacters = AllowedCharacters();
	if (allowedCharacters.size() < 1) {
		return {};
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> charDistribution(0, allowedCharacters.size() - 1);

	while (password.length() < passwordLength) {
		auto randomizedCharacter = GenerateRandomIindex(allowedCharacters);
		password += allowedCharacters[randomizedCharacter];
	}
	return password;
}

void MiniPass::PrintPassword(const std::string& password) {
	std::cout << "Random Password: " << password << std::endl;
	if (makeMnemonic) {
		std::string res = GetMnemonicPhrase();
		std::cout << "Mnemonic Phrase: " << res << std::endl;
	}
}

std::string MiniPass::AllowedCharacters() const {
	std::string allowedCharacters;
	if (!removeNumbers && !makeMnemonic) allowedCharacters += "0123456789";
	if (!removeLowercaseLetters) allowedCharacters += "abcdefghijklmnopqrstuvwxyz";
	if (!removeUppercaseLetters && !makeMnemonic) allowedCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (!removeSpecialCharacters && !makeMnemonic) allowedCharacters += "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

	std::unordered_set<char> unorderedSetCustomCharacters(removeCustomCharacters.begin(), removeCustomCharacters.end());
	std::string filteredCharacters;

	for (char c : allowedCharacters) {
		if (unorderedSetCustomCharacters.find(c) == unorderedSetCustomCharacters.end()) {
			filteredCharacters += c;
		}
	}
	return filteredCharacters;
}