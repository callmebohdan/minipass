#include <iostream>
#include <qapplication.h>
#include <qwindowdefs.h>
#include "minipass.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	MiniPass minipass{nullptr};
	
	if (argc == 1) {
		// GUI mode
		minipass.show();
		return app.exec();
	} else {
		// CLI mode
		try {
			ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);
			minipass.HandleCommandLineProgramOptions(programOptions);
			return 0;
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
			return 1;
		}
		catch (const std::overflow_error& e) {
			std::cerr << e.what() << '\n';
			return 1;
		}
		catch (const std::runtime_error& e) {
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
