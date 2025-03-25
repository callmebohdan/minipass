#include <algorithm>
#include <cctype>
#ifdef _WIN32
    #include <corecrt.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <qapplication.h>
#include <qcheckbox.h>
#include <qclipboard.h>
#include <QDesktopServices>
#include <qfile.h>
#include <qiodevice.h>
#include <qiodevicebase.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <QtConcurrent>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <string>
#include <unordered_set>
#include <vector>
#include "minipass.hpp"
#include "ui_minipass.h"

namespace bfs = boost::filesystem; 

MiniPass::MiniPass(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MiniPass)
{
	ui->setupUi(this);
	HandleUserActions();
}

void MiniPass::HandleUserActions() {
	connect(ui->LineEditCustom, &QLineEdit::textChanged, this, &MiniPass::SetCustom);
	connect(ui->LineEditLength, &QLineEdit::textChanged, this, &MiniPass::SetLength);
	connect(ui->CheckBoxMnemonic, &QCheckBox::toggled, this, &MiniPass::ToggleMnemonic);
	connect(ui->CheckBoxHistory, &QCheckBox::toggled, this, &MiniPass::ToggleHistory);
	connect(ui->CheckBoxSpecial, &QCheckBox::toggled, this, &MiniPass::ToggleSpecial);
	connect(ui->CheckBoxUppercase, &QCheckBox::toggled, this, &MiniPass::ToggleUppercase);
	connect(ui->CheckBoxLowercase, &QCheckBox::toggled, this, &MiniPass::ToggleLowercase);
	connect(ui->CheckBoxNumbers, &QCheckBox::toggled, this, &MiniPass::ToggleNumbers);
	connect(ui->ButtonGeneratePassword, &QToolButton::clicked, this, &MiniPass::ClickGenerate);
	connect(ui->ButtonOpenHistory, &QToolButton::clicked, this, &MiniPass::ClickHistory);
	connect(ui->ButtonDefaultOptions, &QToolButton::clicked, this, &MiniPass::ClickDefault);
	connect(ui->ButtonResetOptions, &QToolButton::clicked, this, &MiniPass::ClickReset);
	connect(ui->ButtonCopyPassword, &QToolButton::clicked, this, &MiniPass::ClickCopy);
}

void MiniPass::SetCustom(const QString& customCharacters) {
	programOptions.useCustom = customCharacters.toStdString();
}

void MiniPass::ToggleMnemonic(bool checked) {
	programOptions.makeMnemonic = checked;
}

void MiniPass::ToggleHistory(bool checked) {
	programOptions.keepHistory = checked;
}

void MiniPass::ToggleSpecial(bool checked) {
	programOptions.useSpecial = checked;
}

void MiniPass::ToggleUppercase(bool checked) {
	programOptions.useUppercase = checked;
}

void MiniPass::ToggleLowercase(bool checked) {
	programOptions.useLowercase = checked;
}

void MiniPass::ToggleNumbers(bool checked) {
	programOptions.useNumbers = checked;
}

void MiniPass::SetLength(const QString& _passwordLength) {
	programOptions.passwordLength = _passwordLength.toInt();
}

void MiniPass::ClickCopy() {
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(ui->TextEditPassword->toPlainText());
}

void MiniPass::ClickGenerate() {
	password.clear();
	mnemonicPhrase.clear();
	ui->TextEditPassword->clear();
	auto ClickGeneratePassword = QtConcurrent::run([this]() {
		std::string randomPassword = HandleUserInterfaceProgramOptions(programOptions);
		QMetaObject::invokeMethod(this, [randomPassword, this]() {
			ui->TextEditPassword->setPlainText(QString::fromStdString(randomPassword));
		});
	});
}

void MiniPass::ClickHistory() {
#if defined(__linux__)
	std::string homeDir = std::getenv("HOME");
	passwordsDatabasePath = homeDir + "/Documents/minipass/passwords.csv";
#elif defined (_WIN32) || defined(_WIN64)
	passwordsDatabasePath = "%APPDATA%\\minipass\\passwords.csv";
#endif
	auto ClickOpenPasswordsHistory = QtConcurrent::run([this]() {
        QFile file(QString::fromStdString(passwordsDatabasePath));

        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            QTextStream out(&file);
            if (!file.exists()) {
                out << "Creation Date,Password,Mnemonic Phrase\n";
            }
            file.close();
        }

        QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(passwordsDatabasePath));
        QDesktopServices::openUrl(fileUrl);
    });
}

void MiniPass::ClickDefault() {
	ui->CheckBoxUppercase->setChecked(true);
	ui->CheckBoxLowercase->setChecked(true);
	ui->CheckBoxNumbers->setChecked(true);
	SetLength("16");
	ui->LineEditLength->setText("16");
}

void MiniPass::ClickReset() {
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

MiniPass::MiniPass(const PasswordSettings& passwordSettings)
: programOptions(passwordSettings){}

std::string MiniPass::AllowedCharacters(const PasswordSettings& passwordSettings) const {
	std::string allowedCharacters;
	if (programOptions.defaultOptions){
		allowedCharacters += "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return allowedCharacters;
	}
	if (programOptions.useNumbers && !programOptions.makeMnemonic) allowedCharacters += "0123456789";
	if (programOptions.useLowercase) allowedCharacters += "abcdefghijklmnopqrstuvwxyz";
	if (programOptions.useUppercase) allowedCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (programOptions.useSpecial && !programOptions.makeMnemonic) allowedCharacters += R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
	for (char c : programOptions.useCustom){
		if (allowedCharacters.find(c) == std::string::npos) {
			if (programOptions.makeMnemonic) {
				std::string specialCharacters = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)"; 
				bool isNotSpecial = specialCharacters.find(c) == std::string::npos; 
				if (isNotSpecial && !isdigit(c)){
					allowedCharacters += c;
				}
			} else {
				allowedCharacters += c;
			}
		}
	}
	return allowedCharacters;
}

void MiniPass::ApplyMnemonicFilter(const std::string& password) {
	for (char ch : password) {
		mnemonicPhrase += GenerateRandomMnemonicSeed(ch) + " ";
	}
}

std::string MiniPass::GenerateRandomMnemonicSeed(const char& ch) {
	std::string filename = "resources/seed-database/mnemonic-seeds.txt";
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

	auto loweredCharacter = std::tolower(ch);
	while (std::getline(file, line)) {
		if (!line.empty() && line[0] == loweredCharacter) {
			characterNamedSeeds.push_back(line);
		}
	}

	if (characterNamedSeeds.empty()) {
		std::cerr << "No words starting with '" << loweredCharacter << "' found." << std::endl;
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
