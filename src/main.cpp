#include <qapplication.h>
#include <qwindowdefs.h>
#include "minipass.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MiniPass miniPass{nullptr};

	if (argc > 1) {
		miniPass.ParseCommandLineArguments(argc, argv);
		miniPass.ReturnGeneratedPassword();
		return 0;
	}

	miniPass.show();
	return app.exec();
}
