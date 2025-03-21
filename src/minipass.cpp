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
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <cstdlib>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace bfs = boost::filesystem; 

MiniPass::MiniPass(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MiniPass)
{
	ui->setupUi(this);
	HandleUserActions();
	HandleUserOutput();
}

void MiniPass::HandleUserActions() {
	connect(ui->LineEditCustom, &QLineEdit::textChanged, this, &MiniPass::SetUserCustomCharacters);
	connect(ui->CheckBoxMnemonic, &QCheckBox::toggled, this, &MiniPass::ToggleMakeMnemonic);
	connect(ui->CheckBoxHistory, &QCheckBox::toggled, this, &MiniPass::ToggleKeepHistory);
	connect(ui->CheckBoxSpecial, &QCheckBox::toggled, this, &MiniPass::ToggleUseSpecial);
	connect(ui->CheckBoxUppercase, &QCheckBox::toggled, this, &MiniPass::ToggleUseUppercase);
	connect(ui->CheckBoxLowercase, &QCheckBox::toggled, this, &MiniPass::ToggleUseLowercase);
	connect(ui->CheckBoxNumbers, &QCheckBox::toggled, this, &MiniPass::ToggleUseNumbers);
	connect(ui->LineEditLength, &QLineEdit::textChanged, this, &MiniPass::SetPasswordLength);
	connect(ui->ButtonGeneratePassword, &QToolButton::clicked, this, &MiniPass::ClickGeneratePassword);
	connect(ui->ButtonOpenHistory, &QToolButton::clicked, this, &MiniPass::ClickOpenPasswordsHistory);
	connect(ui->ButtonResetOptions, &QToolButton::clicked, this, &MiniPass::ClickResetOptions);
	connect(ui->ButtonCopyPassword, &QToolButton::clicked, this, &MiniPass::CopyPassword);
}

void MiniPass::SetUserCustomCharacters(const QString& customCharacters) {
	programOptions.useCustom = customCharacters.toStdString();
}

void MiniPass::ToggleMakeMnemonic(bool checked) {
	programOptions.makeMnemonic = checked;
}

void MiniPass::ToggleKeepHistory(bool checked) {
	programOptions.keepHistory = checked;
}

void MiniPass::ToggleUseSpecial(bool checked) {
	programOptions.useSpecial = checked;
}

void MiniPass::ToggleUseUppercase(bool checked) {
	programOptions.useUppercase = checked;
}

void MiniPass::ToggleUseLowercase(bool checked) {
	programOptions.useLowercase = checked;
}

void MiniPass::ToggleUseNumbers(bool checked) {
	programOptions.useNumbers = checked;
}

void MiniPass::SetPasswordLength(const QString& _passwordLength) {
	programOptions.passwordLength = _passwordLength.toInt();
}

void MiniPass::CopyPassword() {
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(ui->TextEditPassword->toPlainText());
}

void MiniPass::ClickGeneratePassword() {
	password.clear();
	ui->TextEditPassword->clear();
	HandleUserActions();
	std::string randomPassword = HandleUserInterfaceProgramOptions(programOptions);
	ui->TextEditPassword->setPlainText(QString::fromStdString(randomPassword));
}

void MiniPass::ClickOpenPasswordsHistory() {
	std::string executableDir = std::filesystem::current_path().string();
#if defined(__linux__)
	passwordsDatabasePath = executableDir + "//PasswordsHistory.csv";
#elif defined (_WIN32) || defined(_WIN64)
	passwordsDatabasePath = executableDir + "\\PasswordsHistory.csv";
#endif
	QFile file(QString::fromStdString(passwordsDatabasePath));

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {}
}

void MiniPass::ClickResetOptions() {
	ui->LineEditCustom->clear();
	ui->CheckBoxMnemonic->setChecked(false);
	ui->CheckBoxHistory->setChecked(false);
	ui->CheckBoxSpecial->setChecked(false);
	ui->CheckBoxUppercase->setChecked(false);
	ui->CheckBoxLowercase->setChecked(false);
	ui->CheckBoxNumbers->setChecked(false);
	ui->LineEditLength->clear();
	ui->TextEditPassword->clear();
	password.clear();
}

MiniPass::~MiniPass() {
	delete ui;
	ui = nullptr;
}


int MiniPass::GenerateRandomIndex(const std::string& inputSet) {
	quint32 index = QRandomGenerator::global()->bounded(0, static_cast<int>(inputSet.length()-1));
	return static_cast<int>(index);
}
MiniPass::MiniPass(const PasswordSettings& passwordSettings)
: programOptions(passwordSettings){}



std::string MiniPass::AllowedCharacters(const PasswordSettings& passwordSettings) const {
	std::string allowedCharacters;
	if (programOptions.useNumbers && !programOptions.makeMnemonic) allowedCharacters += "0123456789";
	if (programOptions.useLowercase) allowedCharacters += "abcdefghijklmnopqrstuvwxyz";
	if (programOptions.useUppercase && !programOptions.makeMnemonic) allowedCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (programOptions.useSpecial && !programOptions.makeMnemonic) allowedCharacters += "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

	std::unordered_set<char> customCharacters(programOptions.useCustom.begin(), programOptions.useCustom.end());
	std::string filteredCharacters;

	for (char c : allowedCharacters) {
		if (customCharacters.find(c) == customCharacters.end()) {
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

char MiniPass::GenerateRandomMnemonicSeed(const char& ch) {
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

	std::string characterNamedSeeds;
	std::string line;

	while (std::getline(file, line)) {
		if (!line.empty() && line[0] == ch) {
			characterNamedSeeds.append(line);
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

std::string MiniPass::GenerateRandomPassword(const PasswordSettings& passwordSettings) {
	programOptions = passwordSettings;
	std::string allowedCharacters = AllowedCharacters(passwordSettings);
	if (allowedCharacters.size() < 1) {
		return {};
	}

	while (password.length() < passwordSettings.passwordLength) {
		auto randomizedCharacter = GenerateRandomIndex(allowedCharacters);
		password += allowedCharacters[randomizedCharacter];
	}

	return password;
}

std::string MiniPass::GetCurrentTime() const {
    return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
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
	bfs::fstream passwordsDatabase;
	#if defined(__linux__)
	std::string homeDir = std::getenv("HOME");
	passwordsDatabasePath = homeDir + "/Documents/minipass/passwords.csv";
#elif defined (_WIN32) || defined(_WIN64)
	passwordsDatabasePath = "%APPDATA%\\minipass\\passwords.csv";
#endif
	bfs::path boostPasswordsDatabasePath(passwordsDatabasePath);
	bfs::path parent_dir = boostPasswordsDatabasePath.parent_path();
	if (!bfs::exists(parent_dir)){
		bfs::create_directory(parent_dir);
		bfs::fstream passwordsDatabase(passwordsDatabasePath);
	}

	passwordsDatabase.open(boostPasswordsDatabasePath, std::ios::out | std::ios::app);
	
	if (passwordsDatabase)
	{
		if (bfs::is_empty(boostPasswordsDatabasePath)) {
			passwordsDatabase << "Creation Date,Password,Mnemonic Phrase" << std::endl;
		}
		
		passwordsDatabase 
			<< GetCurrentTime() << "," 
			<< password << "," 
			<< mnemonicPhrase << std::endl;
		passwordsDatabase.close();
	}
	else
	{
		std::cerr << "File could not be opened!\n";
		std::cerr << "Error code: " << strerror(errno);
	}
}

void MiniPass::HandleCommandLineProgramOptions(const PasswordSettings& passwordSettings) {
	password = GenerateRandomPassword(passwordSettings);
	std::cout << "Random Password: " << password << std::endl;
	if (passwordSettings.makeMnemonic) {
		ApplyMnemonicFilter(password);
		std::cout << "Mnemonic Phrase: " << mnemonicPhrase << std::endl;
	}
	if (passwordSettings.keepHistory) {
		KeepHistory(password);
		std::cout << "Password saved to " << passwordsDatabasePath << std::endl;
	}
}

std::string MiniPass::HandleUserInterfaceProgramOptions(const PasswordSettings& passwordSettings) {
	password = GenerateRandomPassword(passwordSettings);
	if (!password.empty() && passwordSettings.makeMnemonic) {
		ApplyMnemonicFilter(password);
	}
	if (!password.empty() && passwordSettings.keepHistory) {
		KeepHistory(password);
	}
	return password;
}
