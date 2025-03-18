#ifndef MINIPASS_HPP
#define MINIPASS_HPP

#include <cstdint>
#include <limits>
#include <qmainwindow.h>
#include <qstring.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <random>
#include <stdexcept>
#include <string>

struct PasswordSettings {
	uint32_t passwordLength{16};
	bool useNumbers = false;
	bool useLowercase = false;
	bool useUppercase = false;
	bool useSpecial = false;
	bool makeMnemonic = false;
	bool keepHistory = false;
	std::string useCustom{};
};

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
	void ToggleUseSpecial(bool checked);
	void ToggleUseUppercase(bool checked);
	void ToggleUseLowercase(bool checked);
	void ToggleUseNumbers(bool checked);
	void SetPasswordLength(const QString& passwordLength);
	// User actions
	void ClickGeneratePassword();
	void ClickOpenPasswordsHistory();
	void ClickResetOptions();
	void ClickExitMinipass();
	// User output
	void ClearPassword();
	void CopyPassword();
private:
	PasswordSettings programOptions;
	Ui::MiniPass* ui;
	std::string password;
	std::string mnemonicPhrase;
	std::string keepHistoryFilePath;
public:
	explicit MiniPass(QWidget* parent = nullptr);
	MiniPass()=default;
	~MiniPass();
	// Constructors
	MiniPass(const PasswordSettings& passwordSettings);
	MiniPass(const MiniPass& newCopy)=default;
	MiniPass& operator=(const MiniPass& other)=default;	
	// Member functions
	std::string AllowedCharacters() const;
	void ApplyMnemonicFilter(const std::string& str);
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string GenerateRandomPassword();
	std::string GetCurrentTime() const;
	void HandleCommandLineProgramOptions(const PasswordSettings&);
	std::string HandleUserInterfaceProgramOptions(const PasswordSettings& passwordSettings);
	std::string EscapeDoubleQuotes(const std::string& str) const;
	void KeepHistory(const std::string& str);
	void PrintPassword(const std::string& str);
	void ReturnGeneratedPassword();
	void HandleCombinedShortOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);
	void HandleLongOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);
	void HandleShortOptionsWithInputValue(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);

	// Getters
	uint32_t GetPasswordLength() const { return programOptions.passwordLength; };
	bool IsUseNumbers() const { return programOptions.useNumbers; };
	bool IsUseLowercase() const { return programOptions.useLowercase; };
	bool IsUseUppercase() const { return programOptions.useUppercase; };
	bool IsUseSpecial() const { return programOptions.useSpecial; };
	bool IsMakeMnemonic() const { return programOptions.makeMnemonic; };
	bool IsKeepHistory() const { return programOptions.keepHistory; };
	std::string GetUseCustom() const { return programOptions.useCustom; };

	// UI getters
	void HandleUserOptions();
	void HandleUserActions();
	void HandleUserOutput();

	PasswordSettings ParseCommandLineArguments(int argc, char* argv[]);

	void PrintHelp();
};

#endif  // MINIPASS_HPP
