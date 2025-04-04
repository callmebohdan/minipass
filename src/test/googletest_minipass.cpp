#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "../minipass.hpp"

TEST(GoogleTestMinipass, DefaultConstructor) {
	MiniPass minipass{nullptr};
	ASSERT_EQ(minipass.GetPasswordLength(), 16);
	ASSERT_FALSE(minipass.IsUseNumbers());
	ASSERT_FALSE(minipass.IsUseLowercase());
	ASSERT_FALSE(minipass.IsUseUppercase());
	ASSERT_FALSE(minipass.IsUseSpecial());
	ASSERT_FALSE(minipass.IsMakeMnemonic());
	ASSERT_FALSE(minipass.IsKeepHistory());
	ASSERT_EQ(minipass.GetUseCustom(), "");
}

TEST(GoogleTestMinipass, ParametrizedConstructor) {
	ProgramOptions programOptions;
	programOptions.passwordLength = 32;
	programOptions.numbers = true;
	programOptions.lowercase = true;
	programOptions.uppercase = true;
	programOptions.special = true;
	programOptions.mnemonic = true;
	programOptions.history = true;
	programOptions.custom = "true";

	MiniPass minipass(programOptions);

	ASSERT_EQ(minipass.GetPasswordLength(), programOptions.passwordLength);
	ASSERT_EQ(minipass.IsUseNumbers(), programOptions.numbers);
	ASSERT_EQ(minipass.IsUseLowercase(), programOptions.lowercase);
	ASSERT_EQ(minipass.IsUseUppercase(), programOptions.uppercase);
	ASSERT_EQ(minipass.IsUseSpecial(), programOptions.special);
	ASSERT_EQ(minipass.IsMakeMnemonic(), programOptions.mnemonic);
	ASSERT_EQ(minipass.IsKeepHistory(), programOptions.history);
	ASSERT_EQ(minipass.GetUseCustom(), programOptions.custom);
}

TEST(GoogleTestMinipass, CopyConstructor) {
	ProgramOptions minipassOriginal;
	minipassOriginal.passwordLength = 32;
	minipassOriginal.numbers = true;
	minipassOriginal.lowercase = true;
	minipassOriginal.uppercase = true;
	minipassOriginal.special = true;
	minipassOriginal.mnemonic = true;
	minipassOriginal.history = true;
	minipassOriginal.custom = "true";

	MiniPass minipassCopy(minipassOriginal);

	ASSERT_EQ(minipassCopy.GetPasswordLength(), minipassOriginal.passwordLength);
	ASSERT_EQ(minipassCopy.IsUseNumbers(), minipassOriginal.numbers);
	ASSERT_EQ(minipassCopy.IsUseLowercase(), minipassOriginal.lowercase);
	ASSERT_EQ(minipassCopy.IsUseUppercase(), minipassOriginal.uppercase);
	ASSERT_EQ(minipassCopy.IsUseSpecial(), minipassOriginal.special);
	ASSERT_EQ(minipassCopy.IsMakeMnemonic(), minipassOriginal.mnemonic);
	ASSERT_EQ(minipassCopy.IsKeepHistory(), minipassOriginal.history);
	ASSERT_EQ(minipassCopy.GetUseCustom(), minipassOriginal.custom);
}

TEST(GoogleTestMinipass, AssignmentOperator) {
	ProgramOptions minipassOriginal;
	minipassOriginal.passwordLength = 32;
	minipassOriginal.numbers = true;
	minipassOriginal.lowercase = true;
	minipassOriginal.uppercase = true;
	minipassOriginal.special = true;
	minipassOriginal.mnemonic = true;
	minipassOriginal.history = true;
	minipassOriginal.custom = "true";

	MiniPass minipassOther{nullptr};
	minipassOther = minipassOriginal;

	ASSERT_EQ(minipassOther.GetPasswordLength(), minipassOriginal.passwordLength);
	ASSERT_EQ(minipassOther.IsUseNumbers(), minipassOriginal.numbers);
	ASSERT_EQ(minipassOther.IsUseLowercase(), minipassOriginal.lowercase);
	ASSERT_EQ(minipassOther.IsUseUppercase(), minipassOriginal.uppercase);
	ASSERT_EQ(minipassOther.IsUseSpecial(), minipassOriginal.special);
	ASSERT_EQ(minipassOther.IsMakeMnemonic(), minipassOriginal.mnemonic);
	ASSERT_EQ(minipassOther.IsKeepHistory(), minipassOriginal.history);
	ASSERT_EQ(minipassOther.GetUseCustom(), minipassOriginal.custom);
}

TEST(GoogleTestMinipass, GenerateRandomIndex_EmptySet)
{
	std::vector<int> inputSet(std::numeric_limits<int>::max());
	MiniPass minipass{nullptr};
	EXPECT_THROW(minipass.GenerateRandomIndex(inputSet), std::out_of_range);
}

TEST(GoogleTestMinipass, BigSet) {
	std::vector<int> inputSet(1000000, 1);
	MiniPass minipass{nullptr};
	for (int i = 0; i < 1000000; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_OverflowSet) {
	std::vector<int> inputSet(static_cast<size_t>(std::numeric_limits<int>::max()) + 1);
	MiniPass minipass{nullptr};
	EXPECT_THROW(minipass.GenerateRandomIndex(inputSet), std::overflow_error);
}

TEST(GoogleTestMinipass, GenerateRandomIndex_IntegerSet)
{
	std::vector<int> inputSet{1, 2, 3, 4, 5};
	MiniPass minipass{nullptr};
	for (int i = 0; i < 100; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_StringSet)
{
	std::vector<std::string> inputSet{"a", "b", "c", "d", "e"};
	MiniPass minipass{nullptr};
	for (int i = 0; i < 100; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_DoubleSet)
{
	std::vector<double> inputSet{0.1, 0.2, 0.3, 0.4, 0.5};
	MiniPass minipass{nullptr};
	for (int i = 0; i < 100; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_FloatSet)
{
	std::vector<float> inputSet{0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
	MiniPass minipass{nullptr};
	for (int i = 0; i < 100; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_CharSet)
{
	std::vector<char> inputSet{'a', 'b', 'c', 'd', 'e'};
	MiniPass minipass{nullptr};
	for (int i = 0; i < 100; ++i) {
		int index = minipass.GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, ParseNoCommandLineArguments) {
	char* input = {"./minipass"};

	ProgramOptions programOptions{};
	// programOptions.passwordLength = 16;
	// programOptions.numbers = false;
	// programOptions.lowercase = false;
	// programOptions.uppercase = false;
	// programOptions.special = false;
	// programOptions.mnemonic = false;
	// programOptions.history = false;
	// programOptions.custom = "";

	EXPECT_EQ(programOptions.passwordLength, 16);
	EXPECT_FALSE(programOptions.numbers);
	EXPECT_FALSE(programOptions.lowercase);
	EXPECT_FALSE(programOptions.uppercase);
	EXPECT_FALSE(programOptions.special);
	EXPECT_FALSE(programOptions.mnemonic);
	EXPECT_FALSE(programOptions.history);
	EXPECT_EQ(programOptions.custom, std::string(""));
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_PasswordLengthWithoutNumber) {
	char* input = {"./minipass -l"};

	ProgramOptions programOptions{};
	// programOptions.passwordLength = 16;

	EXPECT_EQ(programOptions.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_PasswordLengthIsNumber) {
	char* argv[] = {"./minipass.exe", "-l", "25"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.passwordLength, 25);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_PasswordLengthIsString) {
	char* argv[] = {"./minipass.exe", "-l", "abc"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_PasswordLengthIsSpecialCharacter) {
	char* argv[] = {"./minipass.exe", "-l", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_numbersShort) {
	char* argv[] = {"./minipass.exe", "-n"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.numbers, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_numbersLong) {
	char* argv[] = {"./minipass.exe", "--numbers"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.numbers, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_lowercaseShort) {
	char* argv[] = {"./minipass.exe", "-o"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.lowercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_lowercaseLong) {
	char* argv[] = {"./minipass.exe", "--lower"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.lowercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_uppercaseShort) {
	char* argv[] = {"./minipass.exe", "-u"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.uppercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_uppercaseLong) {
	char* argv[] = {"./minipass.exe", "--upper"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.uppercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_specialShort) {
	char* argv[] = {"./minipass.exe", "-s"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.special, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_specialLong) {
	char* argv[] = {"./minipass.exe", "--special"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.special, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_KeepHistoryShort) {
	char* argv[] = {"./minipass.exe", "-k"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.history, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_KeepHistoryLong) {
	char* argv[] = {"./minipass.exe", "--history"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.history, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_MakeMnemonicShort) {
	char* argv[] = {"./minipass.exe", "-m"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_MakeMnemonicLong) {
	char* argv[] = {"./minipass.exe", "--mnemonic"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_MultipleShortOptions) {
	char* argv[] = {"./minipass.exe", "-dnouskm"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.numbers, true);
	EXPECT_EQ(programOptions.lowercase, true);
	EXPECT_EQ(programOptions.uppercase, true);
	EXPECT_EQ(programOptions.special, true);
	EXPECT_EQ(programOptions.history, true);
	EXPECT_EQ(programOptions.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineOptions_MultipleShortOptionsWithLengthAndCustom) {
	char* argv[] = {"./minipass.exe", "-nuskmlc"};
	int argc = sizeof(argv) / sizeof(argv[0]);
	MiniPass minipass{nullptr};
	ProgramOptions programOptions = minipass.ParseCommandLineOptions(argc, argv);

	EXPECT_EQ(programOptions.numbers, true);
	EXPECT_EQ(programOptions.uppercase, true);
	EXPECT_EQ(programOptions.special, true);
	EXPECT_EQ(programOptions.history, true);
	EXPECT_EQ(programOptions.mnemonic, true);
	EXPECT_EQ(programOptions.passwordLength, 16);
	EXPECT_EQ(programOptions.custom, "");
}
