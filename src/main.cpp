#include <qapplication.h>
#include "mainwindow.hpp"
#include "minipass.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		QApplication application(argc, argv);
		MainWindow mainWindow;
		mainWindow.show();
		return application.exec();
	}
	else {
		MiniPass passwordOptions{ParseCommandLineArguments(argc, argv)};
		passwordOptions.ReturnGeneratedPassword();
	}
}