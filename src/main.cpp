#include <qapplication.h>
#include <qwindowdefs.h>
#include "minipass.hpp"
#include "boost/program_options.hpp"
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
	
	QApplication app(argc, argv);
	
	if (argc == 1) {
		// GUI mode
		MiniPass minipassGUI{nullptr};
		minipassGUI.show();
		return app.exec();
	} else {
		// CLI mode
		try {
			po::options_description description("Allowed options");
			description.add_options()
				("custom,c", po::value<std::string>()->default_value(""), "Use custom characters")
				("help,h", "Print help")
				("history,k", "Keep passwords history")
				("length,l", po::value<int>()->default_value(16), "Set password length")
				("lower,o", "Use lowercase letters: a-z")
				("mnemonic,m", "Make mnemonic password")
				("numbers,n", "Use numbers: 0-9")
				("special,s", "Use special characters: !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~")
				("upper,u", "Use uppercase letters: A-Z")
			;

			po::variables_map variables_map;
			po::store(po::command_line_parser(argc, argv).options(description).run(), variables_map);
			po::notify(variables_map);

			if(variables_map.count("help")) {
				#if defined(__linux__)
					std::cout << "Usage:" << std::endl;
					std::cout << "  ./minipass [ options ]" << std::endl;
				#elif defined (_WIN32) || defined(_WIN64)
					std::cout << "Usage:" << std::endl;
					std::cout << "  .\\minipass [ options ]" << std::endl;
				#endif
				std::cout << description;
				return 0;
			}

			PasswordSettings passwordSettings{};
			passwordSettings.useCustom = variables_map["custom"].as<std::string>();
			passwordSettings.keepHistory = variables_map.count("history");
			passwordSettings.passwordLength = variables_map["length"].as<int>();
			passwordSettings.useLowercase = variables_map.count("lower");
			passwordSettings.makeMnemonic = variables_map.count("mnemonic");
			passwordSettings.useNumbers = variables_map.count("numbers");
			passwordSettings.useSpecial = variables_map.count("special");
			passwordSettings.useUppercase = variables_map.count("upper");

			MiniPass minipassCLI{nullptr};
			minipassCLI.HandleCommandLineProgramOptions(passwordSettings);
			return 0;
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
			return 1;
		}
		catch(...) {
			std::cerr << "Exception of unknown type!\n";
			return 1;
		}
	}
	return 0;
}
