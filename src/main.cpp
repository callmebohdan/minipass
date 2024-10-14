#include <qapplication.h>
#include "minipass.hpp"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	MiniPass miniPass{};

	if (argc > 1) {
		miniPass = ParseCommandLineArguments(argc, argv);
		miniPass.ReturnGeneratedPassword();
	}
	else
	{
		miniPass.show();
	}

	return application.exec();
}
