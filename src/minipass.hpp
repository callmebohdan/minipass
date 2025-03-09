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
	bool defaultSettings = true;
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
	void ToggleDefaultOptions();
	void SetPasswordLength(const QString& passwordLength);
	// User actions
	void ClickGeneratePassword();
	void ClickOpenPasswordsHistory();
	void ClickResetOptions();
	void ClickExitMinipass();
	// User output
	std::string ReturnGeneratedPasswordFromUI();
	void ClearPassword();
	void CopyPassword();
private:
	Ui::MiniPass* ui;
	std::string password;
	uint32_t passwordLength;
	bool useNumbers;
	bool useLowercase;
	bool useUppercase;
	bool useSpecial;
	bool makeMnemonic;
	bool keepHistory;
	std::string useCustom;
	std::string mnemonicPhrase;
	std::string keepHistoryFilePath;
public:
	explicit MiniPass(QWidget* parent = nullptr);
	MiniPass();
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
	void HandleCombinedShortOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);
	void HandleLongOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);
	void HandleShortOptionsWithInputValue(int& index, int argc, char* argv[], PasswordSettings& passwordSettings);

	// Getters
	uint32_t GetPasswordLength() const { return passwordLength; };
	bool IsUseNumbers() const { return useNumbers; };
	bool IsUseLowercase() const { return useLowercase; };
	bool IsUseUppercase() const { return useUppercase; };
	bool IsUseSpecial() const { return useSpecial; };
	bool IsMakeMnemonic() const { return makeMnemonic; };
	bool IsKeepHistory() const { return keepHistory; };
	std::string GetUseCustom() const { return useCustom; };
	std::string GetMnemonicPhrase() const { return mnemonicPhrase; };
	std::string GetKeepHistoryFilePath() const { return keepHistoryFilePath; };

	// UI getters
	void HandleUserOptions();
	void HandleUserActions();
	void HandleUserOutput();

	template <typename T>
	int GenerateRandomIndex(const T& inputSet) {
		if (inputSet.empty()) {
			throw std::out_of_range("Input set is empty, cannot generate a random index.");
		}

		if (inputSet.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
			throw std::overflow_error("Input set size exceeds maximum allowable value.");
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


	PasswordSettings ParseCommandLineArguments(int argc, char* argv[]);

	void PrintHelp();
};

#endif  // MINIPASS_HPP
