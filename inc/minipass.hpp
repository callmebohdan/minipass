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
	std::string removeCustomCharacters;
	std::string mnemonicPhrase;

public:
	MiniPass(const PasswordSettings& passwordSettings)
		: passwordLength(passwordSettings.passwordLength)
		, removeNumbers(passwordSettings.removeNumbers)
		, removeLowercaseLetters(passwordSettings.removeLowercaseLetters)
		, removeUppercaseLetters(passwordSettings.removeUppercaseLetters)
		, removeSpecialCharacters(passwordSettings.removeSpecialCharacters)
		, makeMnemonic(passwordSettings.makeMnemonic)
		, removeCustomCharacters(passwordSettings.removeCustomCharacters) {}

	std::string AllowedCharacters() const;
	std::string GetCurrentTime() const;
	std::string EscapeDoubleQuotes(const std::string& str) const;
	std::string GenerateRandomPassword();
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string ApplyMnemonicFilter();
	std::string GetMnemonicPhrase();
	void KeepHistory(const std::string& password);
	void PrintPassword(const std::string& password);
	~MiniPass() = default;
};

#endif  // MINIPASS_HPP