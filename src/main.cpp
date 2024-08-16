#include <string>
#include "minipass.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
	MiniPass passwordSettings{ ParseCommandLineArguments(argc, argv) };

	std::string generatedPassword = passwordSettings.GenerateRandomPassword();
	
	if (passwordSettings.makeMnemonic) {
		passwordSettings.ApplyMnemonicFilter();
	}
	
	if (passwordSettings.keepHistory) {
		passwordSettings.KeepHistory();
	}
	passwordSettings.PrintPassword();
	return 0;
}