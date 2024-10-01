#include <corecrt.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <qcheckbox.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qiodevicebase.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qstring.h>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <string>
#include <unordered_set>
#include <vector>
#include "minipass.hpp"
#include "ui_minipass.h"
#include "utils.hpp"

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
	ui->makeMnemonic->setChecked(false);
	ui->keepHistory->setChecked(false);
	ui->removeSpecialCharacters->setChecked(false);
	ui->removeUppercaseLetters->setChecked(false);
	ui->removeLowercaseLetters->setChecked(false);
	ui->removeNumbers->setChecked(false);
	ui->passwordLength->setText("16");
	ui->removeCustomCharacters->setText("");
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

void MiniPass::HandleUserOutput() {
	// TBD
}

void MiniPass::ClickGeneratePassword() {
	std::string generatedPassword = ReturnGeneratedPasswordFromUI();
	ui->randomPassword->setPlainText(QString::fromStdString(generatedPassword));
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
	ui->makeMnemonic->setChecked(false);
	ui->keepHistory->setChecked(false);
	ui->removeSpecialCharacters->setChecked(false);
	ui->removeUppercaseLetters->setChecked(false);
	ui->removeLowercaseLetters->setChecked(false);
	ui->removeNumbers->setChecked(false);
	ui->passwordLength->setText("16");
	ui->passwordLength->setText("");
}

void MiniPass::ClickExitMinipass() {
	ui->makeMnemonic->setChecked(false);
	ui->keepHistory->setChecked(false);
	ui->removeSpecialCharacters->setChecked(false);
	ui->removeUppercaseLetters->setChecked(false);
	ui->removeLowercaseLetters->setChecked(false);
	ui->removeNumbers->setChecked(false);
	ui->passwordLength->setText("16");
	ui->passwordLength->setText("");
}

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
