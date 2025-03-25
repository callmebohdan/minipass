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

struct ProgramOptions {
	bool defaultOptions = false;
	uint32_t passwordLength{16};
	bool numbers = false;
	bool lowercase = false;
	bool uppercase = false;
	bool special = false;
	bool mnemonic = false;
	bool history = false;
	std::string custom{};
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
	ProgramOptions programOptions;
	Ui::MiniPass* ui;
	std::string password;
	std::string mnemonicPhrase;
	std::string passwordsDatabasePath;
public:
	// Constructors
	explicit MiniPass(QWidget* parent = nullptr);
	MiniPass()=default;
	MiniPass(const ProgramOptions& programOptions);
	MiniPass(const MiniPass& newCopy)=default;
	MiniPass& operator=(const MiniPass& other)=default;	
	~MiniPass();
	// Member functions
	std::string AllowedCharacters(const ProgramOptions& programOptions) const;
	void ApplyMnemonicFilter(const std::string& str);
	std::string GenerateRandomMnemonicSeed(const char& ch);
	std::string GenerateRandomPassword(const ProgramOptions& programOptions);
	std::string GetCurrentTime() const;
	void HandleCommandLineProgramOptions(const ProgramOptions&);
	std::string HandleUserInterfaceProgramOptions(const ProgramOptions& programOptions);
	void KeepHistory(const std::string& str);

	// Private data member getters for tests
	uint32_t GetPasswordLength() const { return programOptions.passwordLength; };
	bool IsUseNumbers() const { return programOptions.numbers; };
	bool IsUseLowercase() const { return programOptions.lowercase; };
	bool IsUseUppercase() const { return programOptions.uppercase; };
	bool IsUseSpecial() const { return programOptions.special; };
	bool IsMakeMnemonic() const { return programOptions.mnemonic; };
	bool IsKeepHistory() const { return programOptions.history; };
	std::string GetUseCustom() const { return programOptions.custom; };

	// Handle user input in UI
	void HandleUserActions();
	
	template <typename T>
	int GenerateRandomIndex(T inputSet) {
		quint32 index = QRandomGenerator::global()->bounded(0, static_cast<int>(inputSet.size()));
		return static_cast<int>(index);
	}
};

#endif  // MINIPASS_HPP
