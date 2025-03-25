#ifndef MINIPASS_HPP
#define MINIPASS_HPP

#include <cstdint>
#include <limits>
#include <qmainwindow.h>
#include <QRandomGenerator>
#include <qstring.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <random>
#include <stdexcept>
#include <string>

struct PasswordSettings {
	bool defaultOptions = false;
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
	// Callback for handling user input
	void SetCustom(const QString& customCharacters);
	void SetLength(const QString& passwordLength);
	void ToggleMnemonic(bool checked);
	void ToggleHistory(bool checked);
	void ToggleSpecial(bool checked);
	void ToggleUppercase(bool checked);
	void ToggleLowercase(bool checked);
	void ToggleNumbers(bool checked);
	void ClickGenerate();
	void ClickHistory();
    void ClickDefault();
	void ClickReset();
	void ClickCopy();
private:
	PasswordSettings programOptions;
	Ui::MiniPass* ui;
	std::string password;
	std::string mnemonicPhrase;
	std::string passwordsDatabasePath;
public:
	// Constructors
	explicit MiniPass(QWidget* parent = nullptr);
	MiniPass()=default;
	MiniPass(const PasswordSettings& passwordSettings);
	MiniPass(const MiniPass& newCopy)=default;
	MiniPass& operator=(const MiniPass& other)=default;	
	~MiniPass();
	// Member functions
	std::string AllowedCharacters(const PasswordSettings& passwordSettings) const;
	void ApplyMnemonicFilter(const std::string& str);
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string GenerateRandomPassword(const PasswordSettings& passwordSettings);
	std::string GetCurrentTime() const;
	void HandleCommandLineProgramOptions(const PasswordSettings&);
	std::string HandleUserInterfaceProgramOptions(const PasswordSettings& passwordSettings);
	void KeepHistory(const std::string& str);

	// Private data member getters for tests
	uint32_t GetPasswordLength() const { return programOptions.passwordLength; };
	bool IsUseNumbers() const { return programOptions.useNumbers; };
	bool IsUseLowercase() const { return programOptions.useLowercase; };
	bool IsUseUppercase() const { return programOptions.useUppercase; };
	bool IsUseSpecial() const { return programOptions.useSpecial; };
	bool IsMakeMnemonic() const { return programOptions.makeMnemonic; };
	bool IsKeepHistory() const { return programOptions.keepHistory; };
	std::string GetUseCustom() const { return programOptions.useCustom; };

	// Handle user input in UI
	void HandleUserActions();
	
	template <typename T>
	int GenerateRandomIndex(T inputSet) {
		quint32 index = QRandomGenerator::global()->bounded(0, static_cast<int>(inputSet.size()));
		return static_cast<int>(index);
	}
};

#endif  // MINIPASS_HPP
