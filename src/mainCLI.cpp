#include "minipass.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
	MiniPass passwordOptions{ParseCommandLineArguments(argc, argv)};
	passwordOptions.ReturnGeneratedPassword();
}