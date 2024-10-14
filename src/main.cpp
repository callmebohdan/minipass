#include <qapplication.h>
#include <qwindowdefs.h>
#include "minipass.hpp"

int main(int argc, char* argv[])
{
	if (argc > 1) {
		MiniPass miniPass{nullptr};
		miniPass.ParseCommandLineArguments(argc, argv);
		miniPass.ReturnGeneratedPassword();
		return 0;
	}
	else {
		QApplication app(argc, argv);
		MiniPass miniPass{nullptr};
		miniPass.show();
		return app.exec();
	}
}
