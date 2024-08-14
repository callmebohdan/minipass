#include <string>
#include "../inc/minipass.hpp"
#include "../inc/utils.hpp"

int main(int argc, char* argv[]) {
	PasswordSettings passwordSettings = ParseCommandLineArguments(argc, argv);

	MiniPass password(passwordSettings);

	std::string generatedPassword = password.GenerateRandomPassword();
	if (passwordSettings.makeMnemonic) password.ApplyMnemonicFilter();
	if (passwordSettings.keepHistory) password.KeepHistory(generatedPassword);
	password.PrintPassword(generatedPassword);
	return 0;
}