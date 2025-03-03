#include <algorithm>
#include <cctype>
#ifdef _WIN32
    #include <corecrt.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <qapplication.h>
#include <qcheckbox.h>
#include <qclipboard.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qiodevicebase.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <string>
#include <unordered_set>
#include <vector>
#include "minipass.hpp"
#include "ui_minipass.h"

MiniPass::MiniPass(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MiniPass)
{
	ui->setupUi(this);
	HandleUserOptions();
	HandleUserActions();
	HandleUserOutput();
}

void MiniPass::HandleUserOptions() {
	connect(ui->removeCustomCharacters, &QLineEdit::textChanged, this, &MiniPass::SetUserCustomCharacters);
	connect(ui->makeMnemonic, &QCheckBox::toggled, this, &MiniPass::ToggleMakeMnemonic);
	connect(ui->keepHistory, &QCheckBox::toggled, this, &MiniPass::ToggleKeepHistory);
	connect(ui->removeSpecialCharacters, &QCheckBox::toggled, this, &MiniPass::ToggleRemoveSpecialCharacters);
	connect(ui->removeUppercaseLetters, &QCheckBox::toggled, this, &MiniPass::ToggleRemoveUppercaseLetters);
	connect(ui->removeLowercaseLetters, &QCheckBox::toggled, this, &MiniPass::ToggleRemoveLowercaseLetters);
	connect(ui->removeNumbers, &QCheckBox::toggled, this, &MiniPass::ToggleRemoveNumbers);
	connect(ui->defaultOptions, &QCheckBox::toggled, this, &MiniPass::ToggleDefaultOptions);
	connect(ui->passwordLength, &QLineEdit::textChanged, this, &MiniPass::SetPasswordLength);
}

void MiniPass::SetUserCustomCharacters(const QString& _customCharacters) {
	removeCustomCharacters = _customCharacters.toStdString();
}
void MiniPass::ToggleMakeMnemonic(bool checked) {
	makeMnemonic = checked ? true : false;
}

void MiniPass::ToggleKeepHistory(bool checked) {
	keepHistory = checked ? true : false;
}

void MiniPass::ToggleRemoveSpecialCharacters(bool checked) {
	removeSpecialCharacters = checked ? true : false;
}

void MiniPass::ToggleRemoveUppercaseLetters(bool checked) {
	removeUppercaseLetters = checked ? true : false;
}

void MiniPass::ToggleRemoveLowercaseLetters(bool checked) {
	removeLowercaseLetters = checked ? true : false;
}

void MiniPass::ToggleRemoveNumbers(bool checked) {
	removeNumbers = checked ? true : false;
}

void MiniPass::ToggleDefaultOptions() {
	ui->removeCustomCharacters->clear();
	ui->makeMnemonic->setChecked(false);
	ui->keepHistory->setChecked(false);
	ui->removeSpecialCharacters->setChecked(false);
	ui->removeUppercaseLetters->setChecked(false);
	ui->removeLowercaseLetters->setChecked(false);
	ui->removeNumbers->setChecked(false);
	ui->passwordLength->setText("16");
}

void MiniPass::SetPasswordLength(const QString& _passwordLength) {
	passwordLength = _passwordLength.toInt();
}

void MiniPass::HandleUserActions() {
	connect(ui->generatePassword, &QToolButton::clicked, this, &MiniPass::ClickGeneratePassword);
	connect(ui->openPasswordsHistory, &QToolButton::clicked, this, &MiniPass::ClickOpenPasswordsHistory);
	connect(ui->resetOptions, &QToolButton::clicked, this, &MiniPass::ClickResetOptions);
	connect(ui->exitMinipass, &QToolButton::clicked, this, &MiniPass::ClickExitMinipass);
}

void MiniPass::HandleUserOutput()
{
	connect(ui->clearPassword, &QPushButton::clicked, this, &MiniPass::ClearPassword);
	connect(ui->copyPassword, &QToolButton::clicked, this, &MiniPass::CopyPassword);
}

void MiniPass::ClearPassword() {
	ui->randomPassword->clear();
}

void MiniPass::CopyPassword() {
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(ui->randomPassword->toPlainText());
}

void MiniPass::ClickGeneratePassword() {
	ui->randomPassword->clear();
	HandleUserOptions();
	std::string randomPassword = ReturnGeneratedPasswordFromUI();
	ui->randomPassword->setPlainText(QString::fromStdString(randomPassword));
}

void MiniPass::ClickOpenPasswordsHistory() {
	std::string executableDir = std::filesystem::current_path().string();
#if defined(__linux__)
	keepHistoryFilePath = executableDir + "//PasswordsHistory.csv";
#elif defined (_WIN32) || defined(_WIN64)
	keepHistoryFilePath = executableDir + "\\PasswordsHistory.csv";
#endif
	QFile file(QString::fromStdString(keepHistoryFilePath));

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {}
}

void MiniPass::ClickResetOptions() {
	//checkboxes
	ui->removeCustomCharacters->clear();
	ui->makeMnemonic->setChecked(false);
	ui->keepHistory->setChecked(false);
	ui->removeSpecialCharacters->setChecked(false);
	ui->removeUppercaseLetters->setChecked(false);
	ui->removeLowercaseLetters->setChecked(false);
	ui->removeNumbers->setChecked(false);
	ui->defaultOptions->setChecked(false);
	ui->passwordLength->clear();
	//output
	ui->randomPassword->clear();
}

void MiniPass::ClickExitMinipass() {
	close();
}

MiniPass::MiniPass()
	: passwordLength(16)
	, removeNumbers(false)
	, removeLowercaseLetters(false)
	, removeUppercaseLetters(false)
	, removeSpecialCharacters(false)
	, makeMnemonic(false)
	, keepHistory(false)
	, removeCustomCharacters() {}

MiniPass::~MiniPass() {
	delete ui;
	ui = nullptr;
}

MiniPass::MiniPass(const PasswordSettings& passwordSettings)
	: passwordLength(passwordSettings.passwordLength)
	, removeNumbers(passwordSettings.removeNumbers)
	, removeLowercaseLetters(passwordSettings.removeLowercaseLetters)
	, removeUppercaseLetters(passwordSettings.removeUppercaseLetters)
	, removeSpecialCharacters(passwordSettings.removeSpecialCharacters)
	, makeMnemonic(passwordSettings.makeMnemonic)
	, keepHistory(passwordSettings.keepHistory)
	, removeCustomCharacters(passwordSettings.removeCustomCharacters) {}

MiniPass::MiniPass(const MiniPass& newCopy)
	: passwordLength(newCopy.passwordLength)
	, removeNumbers(newCopy.removeNumbers)
	, removeLowercaseLetters(newCopy.removeLowercaseLetters)
	, removeUppercaseLetters(newCopy.removeUppercaseLetters)
	, removeSpecialCharacters(newCopy.removeSpecialCharacters)
	, makeMnemonic(newCopy.makeMnemonic)
	, keepHistory(newCopy.keepHistory)
	, removeCustomCharacters(newCopy.removeCustomCharacters) {}

MiniPass& MiniPass::operator=(const MiniPass& other) {
	if (this != &other) {
		passwordLength = other.passwordLength;
		removeNumbers = other.removeNumbers;
		removeLowercaseLetters = other.removeLowercaseLetters;
		removeUppercaseLetters = other.removeUppercaseLetters;
		removeSpecialCharacters = other.removeSpecialCharacters;
		makeMnemonic = other.makeMnemonic;
		keepHistory = other.keepHistory;
		removeCustomCharacters = other.removeCustomCharacters;
	}
	return *this;
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

void MiniPass::ApplyMnemonicFilter(const std::string& password) {
	for (char ch : password) {
		mnemonicPhrase += GenerateRandomMnemonicSeed(ch) + " ";
	}
}

std::string MiniPass::GenerateRandomMnemonicSeed(const char& ch) {
	std::string mnemonicSeed;
	std::string filename = "assets/db/mnemonic-seeds.txt";
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

	int randomMnemonicSeedIndex = GenerateRandomIndex(characterNamedSeeds);
	std::unordered_set<int> indexCache;

	while (indexCache.find(randomMnemonicSeedIndex) != indexCache.end()) {
		randomMnemonicSeedIndex = GenerateRandomIndex(characterNamedSeeds);
	}

	indexCache.insert(randomMnemonicSeedIndex);

	return characterNamedSeeds[randomMnemonicSeedIndex];
}

std::string MiniPass::GenerateRandomPassword() {
	std::string allowedCharacters = AllowedCharacters();
	if (allowedCharacters.size() < 1) {
		return {};
	}

	while (password.length() < passwordLength) {
		auto randomizedCharacter = GenerateRandomIndex(allowedCharacters);
		password += allowedCharacters[randomizedCharacter];
	}

	return password;
}

std::string MiniPass::GetCurrentTime() const {
	std::time_t now = std::time(nullptr);
	char currentTime[26];
	std::tm* tmNow = std::localtime(&now); // Convert to local time
	if (std::strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", tmNow) == 0) {
		return "";
	}
	return currentTime;
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
	std::string executableDir = std::filesystem::current_path().string();
#if defined(__linux__)
	keepHistoryFilePath = executableDir + "//PasswordsHistory.csv";
#elif defined (_WIN32) || defined(_WIN64)
	keepHistoryFilePath = executableDir + "\\PasswordsHistory.csv";
#endif
	std::fstream passwordsDB;
	passwordsDB.open(keepHistoryFilePath, std::ios::out | std::ios::app);
	if (std::filesystem::is_empty(keepHistoryFilePath)) {
		passwordsDB << "Creation Date,Password,Mnemonic Phrase" << std::endl;
	}
	std::string quotedPassword = "\"" + EscapeDoubleQuotes(password) + "\"";
	passwordsDB << GetCurrentTime() << "," << quotedPassword << "," << GetMnemonicPhrase() << std::endl;
	passwordsDB.close();
}

void MiniPass::PrintPassword(const std::string& password) const {
	std::cout << "Random Password: " << password << std::endl;
	if (makeMnemonic) {
		std::cout << "Mnemonic Phrase: " << GetMnemonicPhrase() << std::endl;
	}
	if (keepHistory) {
		std::cout << "Password saved to " << GetKeepHistoryFilePath() << std::endl;
	}
}

void MiniPass::ReturnGeneratedPassword() {
	std::string generatedPassword = GenerateRandomPassword();

	if (makeMnemonic) {
		ApplyMnemonicFilter(generatedPassword);
	}

	if (keepHistory) {
		KeepHistory(generatedPassword);
	}

	PrintPassword(generatedPassword);
}

std::string MiniPass::ReturnGeneratedPasswordFromUI() {
	std::string generatedPassword = GenerateRandomPassword();

	if (makeMnemonic) {
		ApplyMnemonicFilter(generatedPassword);
	}

	if (keepHistory) {
		KeepHistory(generatedPassword);
	}

	return generatedPassword;
}

void MiniPass::HandleCombinedShortOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	for (size_t j = 1; j < arg.size(); j++) {
		if (arg[j] == 'l' || arg[j] == 'c') {
			std::cerr << "Error: '-" << arg[j] << "' cannot be combined with other options. Use it separately." << std::endl;
			return;
		}
		switch (arg[j]) {
		case 'h': PrintHelp(); break;
		case 'd': passwordSettings = PasswordSettings(); break;
		case 'n': passwordSettings.removeNumbers = true; break;
		case 'o': passwordSettings.removeLowercaseLetters = true; break;
		case 's': passwordSettings.removeSpecialCharacters = true; break;
		case 'u': passwordSettings.removeUppercaseLetters = true; break;
		case 'k': passwordSettings.keepHistory = true; break;
		case 'm': passwordSettings.makeMnemonic = true; break;
		default:
			std::cerr << "Error: Entered unknown option: '-" << arg[j] << "'. Skipping it." << std::endl;
		}
	}
}

void MiniPass::HandleLongOptions(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	if (arg == "--help") {
		PrintHelp();
		exit(0);
	}
	else if (arg == "--default") {
		passwordSettings = PasswordSettings();
	}
	else if (arg == "--length") {
		if (index + 1 < argc) {
			std::string nextValue{argv[++index]};
			bool isNumeric = !nextValue.empty() && std::all_of(nextValue.begin(), nextValue.end(), ::isdigit);
			if (isNumeric) {
				passwordSettings.passwordLength = std::stoi(nextValue);
			}
			else
			{
				std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
			}
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "--custom") {
		if (index + 1 < argc) {
			passwordSettings.removeCustomCharacters = argv[++index];
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a value. Default value ('" << passwordSettings.removeCustomCharacters << "') will be used instead." << std::endl;
		}
	}
	else if (arg == "--numbers") {
		passwordSettings.removeNumbers = true;
	}
	else if (arg == "--lower") {
		passwordSettings.removeLowercaseLetters = true;
	}
	else if (arg == "--upper") {
		passwordSettings.removeUppercaseLetters = true;
	}
	else if (arg == "--special") {
		passwordSettings.removeSpecialCharacters = true;
	}
	else if (arg == "--history") {
		passwordSettings.keepHistory = true;
	}
	else if (arg == "--mnemonic") {
		passwordSettings.makeMnemonic = true;
	}
	else {
		std::cerr << "Error: Entered unknown option: '" << arg << "'. Default value will be used instead." << std::endl;
	}
}

void MiniPass::HandleShortOptionsWithInputValue(int& index, int argc, char* argv[], PasswordSettings& passwordSettings) {
	std::string arg = argv[index];
	if (arg == "-l") {
		if (index + 1 < argc) {
			std::string nextValue{argv[++index]};
			bool isNumeric = !nextValue.empty() && std::all_of(nextValue.begin(), nextValue.end(), ::isdigit);
			if (isNumeric) {
				passwordSettings.passwordLength = std::stoi(nextValue);
			}
			else
			{
				std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
			}
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "-c") {
		if (index + 1 < argc) {
			passwordSettings.removeCustomCharacters = argv[++index];
		}
		else
		{
			std::cerr << "Error: " << arg << " requires a numeric value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
		}
	}
	else if (arg == "--help") {
		PrintHelp();
		exit(0);
	}
	else if (arg == "-d") {
		passwordSettings = PasswordSettings();
	}
	else if (arg == "-n") {
		passwordSettings.removeNumbers = true;
	}
	else if (arg == "-o") {
		passwordSettings.removeLowercaseLetters = true;
	}
	else if (arg == "-u") {
		passwordSettings.removeUppercaseLetters = true;
	}
	else if (arg == "-s") {
		passwordSettings.removeSpecialCharacters = true;
	}
	else if (arg == "-k") {
		passwordSettings.keepHistory = true;
}
	else if (arg == "-m") {
		passwordSettings.makeMnemonic = true;
	}
	else
	{
		std::cerr << "Error: " << arg << " requires a value. Default value (" << passwordSettings.passwordLength << ") will be used instead." << std::endl;
	}
}

PasswordSettings MiniPass::ParseCommandLineArguments(int argc, char* argv[]) {
	PasswordSettings passwordSettings;

	if (argc == 1) {
		passwordSettings.defaultSettings = true;
	}
	else {
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			if (arg.substr(0, 2) == "--") {
				HandleLongOptions(i, argc, argv, passwordSettings);
			}
			else if (arg[0] == '-' && arg[1] != '-' && arg.size() == 2) {
				HandleShortOptionsWithInputValue(i, argc, argv, passwordSettings);
			}
			else if (arg[0] == '-' && arg[1] != '-' && arg.size() > 2) {
				HandleCombinedShortOptions(i, argc, argv, passwordSettings);
			}
			else {
				std::cerr << "Error: Entered unknown option: '" << arg << "'" << std::endl;
			}
		}
	}
	return passwordSettings;
}

void MiniPass::PrintHelp() {
	std::cout << std::endl;

	// Platform-specific usage message
#if defined(__linux__)
	std::cout << std::endl << "Usage: ./minipass [options]" << std::endl;
#elif defined (_WIN32) || defined(_WIN64)
	std::cout << std::endl << "Usage: .\\minipass.exe [options]" << std::endl;
#endif

	std::cout << "Options:" << std::endl;
	std::cout << "-h, --help           | Show this help message and exit." << std::endl;
	std::cout << "-d, --default        | Generate a password with default settings (length = 16, all options enabled)." << std::endl;
	std::cout << "-l N, --length N     | Set the length of the password to N characters (default: 16)." << std::endl;
	std::cout << "-n, --numbers        | Exclude numbers from the password." << std::endl;
	std::cout << "-o, --lower          | Exclude lowercase letters from the password." << std::endl;
	std::cout << "-u, --upper          | Exclude uppercase letters from the password." << std::endl;
	std::cout << "-s, --special        | Exclude special characters from the password." << std::endl;
	std::cout << "-k, --history		   | Save generated passwords in history." << std::endl;
	std::cout << "-m, --mnemonic       | Create a mnemonic password (a password that is easier to remember)." << std::endl;
	std::cout << "-c STR, --custom STR | Exclude specific characters from the password. STR is a string of characters to exclude." << std::endl;
	std::cout << std::endl;
}
