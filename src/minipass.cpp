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
#include <boost/program_options.hpp>
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
namespace po = boost::program_options;

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
	programOptions.custom = customCharacters.toStdString();
}

void MiniPass::ToggleMnemonic(bool state) {
	programOptions.mnemonic = state;
}

void MiniPass::ToggleHistory(bool state) {
	programOptions.history = state;
}

void MiniPass::ToggleSpecial(bool state) {
	programOptions.special = state;
}

void MiniPass::ToggleUppercase(bool state) {
	programOptions.uppercase = state;
}

void MiniPass::ToggleLowercase(bool state) {
	programOptions.lowercase = state;
}

void MiniPass::ToggleNumbers(bool state) {
	programOptions.numbers = state;
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

MiniPass::MiniPass(const ProgramOptions& _programOptions)
: programOptions(_programOptions){}

std::string MiniPass::AllowedCharacters(const ProgramOptions& _programOptions) const {
	std::string allowedCharacters;
	if (_programOptions.defaultOptions){
		allowedCharacters += "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return allowedCharacters;
	}
	if (_programOptions.numbers && !_programOptions.mnemonic) allowedCharacters += "0123456789";
	if (_programOptions.lowercase) allowedCharacters += "abcdefghijklmnopqrstuvwxyz";
	if (_programOptions.uppercase) allowedCharacters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (_programOptions.special && !_programOptions.mnemonic) allowedCharacters += R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
	for (char c : _programOptions.custom){
		if (allowedCharacters.find(c) == std::string::npos) {
			if (_programOptions.mnemonic) {
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

std::string MiniPass::GenerateRandomPassword(const ProgramOptions& _programOptions) {
	programOptions = _programOptions;
	std::string allowedCharacters = AllowedCharacters(programOptions);
	if (allowedCharacters.size() < 1) {
		return {};
	}

	while (password.length() < programOptions.passwordLength) {
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

ProgramOptions MiniPass::ParseCommandLineOptions(int argc, char** argv)
{
	po::options_description description("Allowed options");
		description.add_options()
			("default,d", "Default program options")
			("custom,c", po::value<std::string>()->default_value(""), "Use custom characters")
			("help,h", "Print help")
			("history,k", "Keep passwords history")
			("length,l", po::value<int>()->default_value(16), "Set password length")
			("lower,o", "Use lowercase letters: a-z")
			("mnemonic,m", "Make mnemonic password")
			("numbers,n", "Use numbers: 0-9")
			("special,s", "Use special characters: !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~")
			("upper,u", "Use uppercase letters: A-Z");

	po::variables_map variables_map;
	po::store(po::command_line_parser(argc, argv).options(description).run(), variables_map);
	po::notify(variables_map);

		if(variables_map.count("help")) {
	#if defined(__linux__)
		std::cout << "Usage:" << std::endl;
		std::cout << "  minipass [ options ]" << std::endl;
	#elif defined (_WIN32) || defined(_WIN64)
		std::cout << "Usage:" << std::endl;
		std::cout << "  .\\minipass [ options ]" << std::endl;
	#endif
		std::cout << description;
		std::exit(0);
	}

	ProgramOptions programOptions{};
	programOptions.defaultOptions = variables_map.count("default");
	programOptions.custom = variables_map["custom"].as<std::string>();
	programOptions.history = variables_map.count("history");
	programOptions.passwordLength = variables_map["length"].as<int>();
	programOptions.lowercase = variables_map.count("lower");
	programOptions.mnemonic = variables_map.count("mnemonic");
	programOptions.numbers = variables_map.count("numbers");
	programOptions.special = variables_map.count("special");
	programOptions.uppercase = variables_map.count("upper");
    
	return programOptions;
}

void MiniPass::HandleCommandLineProgramOptions(const ProgramOptions& _programOptions) {
	programOptions = _programOptions;
	password = GenerateRandomPassword(programOptions);
	std::cout << "Random Password: " << password << std::endl;
	if (programOptions.mnemonic) {
		ApplyMnemonicFilter(password);
		std::cout << "Mnemonic Phrase: " << mnemonicPhrase << std::endl;
	}
	if (programOptions.history) {
		KeepHistory(password);
		std::cout << "Password saved to " << passwordsDatabasePath << std::endl;
	}
}

std::string MiniPass::HandleUserInterfaceProgramOptions(const ProgramOptions& _programOptions) {
	programOptions = _programOptions;
	password = GenerateRandomPassword(programOptions);
	if (!password.empty() && programOptions.mnemonic) {
		ApplyMnemonicFilter(password);
	}
	if (!password.empty() && programOptions.history) {
		KeepHistory(password);
	}
	return password;
}
