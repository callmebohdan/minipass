#include <qapplication.h>
#include "mainwindow.hpp"
#include "minipass.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	MainWindow mainWindow;

	//MiniPass passwordOptions{ ParseCommandLineArguments(argc, argv) };

	//passwordOptions.ReturnGeneratedPassword();

	mainWindow.show();

	return application.exec();
}