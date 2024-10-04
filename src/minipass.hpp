#ifndef MINIPASS_HPP
#define MINIPASS_HPP

#include <cstdint>
#include <qmainwindow.h>
#include <qstring.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <string>
#include "utils.hpp"

namespace Ui {
	class MiniPass;
}

class MiniPass : public QMainWindow
{
	Q_OBJECT

private slots:
	// User options
	void SetUserCustomCharacters(const QString& customCharacters);
	void ToggleMakeMnemonic(bool checked);
	void ToggleKeepHistory(bool checked);
	void ToggleRemoveSpecialCharacters(bool checked);
	void ToggleRemoveUppercaseLetters(bool checked);
	void ToggleRemoveLowercaseLetters(bool checked);
	void ToggleRemoveNumbers(bool checked);
	void ToggleDefaultOptions();
	void SetPasswordLength(const QString& passwordLength);
	// User actions
	void ClickGeneratePassword();
	void ClickOpenPasswordsHistory();
	void ClickResetOptions();
	void ClickExitMinipass();
	// User output
	std::string ReturnGeneratedPasswordFromUI();
private:
	Ui::MiniPass* ui;
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
	std::string keepHistoryFilePath;
public:
	explicit MiniPass(QWidget* parent = nullptr);
	~MiniPass();
	// Constructors
	MiniPass(const PasswordSettings& passwordSettings);
	MiniPass(const MiniPass& newCopy);
	MiniPass& operator=(const MiniPass& other);

	// Member functions
	std::string AllowedCharacters() const;
	void ApplyMnemonicFilter(const std::string& str);
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string GenerateRandomPassword();
	std::string GetCurrentTime() const;
	std::string EscapeDoubleQuotes(const std::string& str) const;
	void KeepHistory(const std::string& str);
	void PrintPassword(const std::string& str) const;
	void ReturnGeneratedPassword();

	// Getters
	uint32_t GetPasswordLength() const { return passwordLength; };
	bool IsRemoveNumbers() const { return removeNumbers; };
	bool IsRemoveLowercaseLetters() const { return removeLowercaseLetters; };
	bool IsRemoveUppercaseLetters() const { return removeUppercaseLetters; };
	bool IsRemoveSpecialCharacters() const { return removeSpecialCharacters; };
	bool IsMakeMnemonic() const { return makeMnemonic; };
	bool IsKeepHistory() const { return keepHistory; };
	std::string GetRemoveCustomCharacters() const { return removeCustomCharacters; };
	std::string GetMnemonicPhrase() const { return mnemonicPhrase; };
	std::string GetKeepHistoryFilePath() const { return keepHistoryFilePath; };

	// UI getters
	void HandleUserOptions();
	void HandleUserActions();
};

#endif  // MINIPASS_HPP
