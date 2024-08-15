#ifndef MINIPASS_HPP
#define MINIPASS_HPP

#include <cstdint>
#include <string>
#include "../inc/utils.hpp"

class MiniPass
{
private:
	std::string password;
	uint32_t passwordLength;
	bool removeNumbers;
	bool removeLowercaseLetters;
	bool removeUppercaseLetters;
	bool removeSpecialCharacters;
	bool makeMnemonic;
	bool keepHistory;
	std::string removeCustomCharacters;
	std::string mnemonicPhrase;

public:
	MiniPass();
	~MiniPass() = default;
	MiniPass(const PasswordSettings& passwordSettings);
	MiniPass(const MiniPass& newCopy);
	MiniPass& operator=(const MiniPass& other);

	std::string AllowedCharacters() const;
	std::string ApplyMnemonicFilter();
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string GenerateRandomPassword();
	std::string GetCurrentTime() const;
	std::string GetMnemonicPhrase() const;
	std::string EscapeDoubleQuotes(const std::string& str) const;
	void KeepHistory(const std::string& password) const;
	void PrintPassword(const std::string& password) const;
};

#endif  // MINIPASS_HPP