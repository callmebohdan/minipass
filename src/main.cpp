#include <qapplication.h>
#include <qwindowdefs.h>
#include "minipass.hpp"
#include "boost/program_options.hpp"
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
	
	QApplication app(argc, argv);
	
	MiniPass miniPass{nullptr};
	
	try
	{
		po::options_description description("Allowed options");
		description.add_options()
			("custom", po::value<std::string>()->default_value(""), "Use custom characters")
			("default", "Use default settings")
			("help", "Print help")
			("history", "Keep passwords history")
			("length", po::value<int>()->default_value(16), "Set password length")
			("lower", "Use lowercase letters: a-z")
			("mnemonic", "Make mnemonic password")
			("numbers", "Use numbers: 0-9")
			("special", "Use special characters: !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~")
			("upper", "Use uppercase letters: A-Z")
		;

		po::variables_map variables_map;
		po::store(po::parse_command_line(argc, argv, description), variables_map);
		po::notify(variables_map);

		if(variables_map.count("custom")){
		
		}
		if(variables_map.count("default")){
			
		}
		if(variables_map.count("help")){
			
		}
		if(variables_map.count("history")){
			
		}
		if(variables_map.count("length")){
			
		}
		if(variables_map.count("lower")){
			
		}
		if(variables_map.count("mnemonic")){
			
		}
		if(variables_map.count("numbers")){
			
		}
		if(variables_map.count("special")){
			
		}
		if(variables_map.count("upper")){
			
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	if (argc > 1) {
		miniPass.ParseCommandLineArguments(argc, argv);
		miniPass.ReturnGeneratedPassword();
		return 0;
	}

	miniPass.show();
	return app.exec();
}
