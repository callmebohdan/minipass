#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "../minipass.hpp"

TEST(GoogleTestMinipass, DefaultConstructor) {
	MiniPass minipass;
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
	ProgramOptions settings;
	settings.passwordLength = 32;
	settings.numbers = true;
	settings.lowercase = true;
	settings.uppercase = true;
	settings.special = true;
	settings.mnemonic = true;
	settings.history = true;
	settings.custom = "true";

	MiniPass minipass(settings);

	ASSERT_EQ(minipass.GetPasswordLength(), settings.passwordLength);
	ASSERT_EQ(minipass.IsUseNumbers(), settings.numbers);
	ASSERT_EQ(minipass.IsUseLowercase(), settings.lowercase);
	ASSERT_EQ(minipass.IsUseUppercase(), settings.uppercase);
	ASSERT_EQ(minipass.IsUseSpecial(), settings.special);
	ASSERT_EQ(minipass.IsMakeMnemonic(), settings.mnemonic);
	ASSERT_EQ(minipass.IsKeepHistory(), settings.history);
	ASSERT_EQ(minipass.GetUseCustom(), settings.custom);
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
	std::vector<int> inputSet(std::numeric_limits<int>::max()+1);
	EXPECT_THROW(GenerateRandomIndex(inputSet), std::out_of_range);
}

TEST(GoogleTestMinipass, BigSet) {
	std::vector<int> inputSet(1000000, 1);
	for (int i = 0; i < 1000000; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_OverflowSet) {
	std::vector<int> inputSet(static_cast<size_t>(std::numeric_limits<int>::max()) + 1);
	EXPECT_THROW(GenerateRandomIndex(inputSet), std::overflow_error);
}

TEST(GoogleTestMinipass, GenerateRandomIndex_IntegerSet)
{
	std::vector<int> inputSet{1, 2, 3, 4, 5};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_StringSet)
{
	std::vector<std::string> inputSet{"a", "b", "c", "d", "e"};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_DoubleSet)
{
	std::vector<double> inputSet{0.1, 0.2, 0.3, 0.4, 0.5};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_FloatSet)
{
	std::vector<float> inputSet{0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, GenerateRandomIndex_CharSet)
{
	std::vector<char> inputSet{'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(GoogleTestMinipass, ParseNoCommandLineArguments) {
	char* argv[] = {"./minipass.exe"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
	EXPECT_FALSE(settings.numbers);
	EXPECT_FALSE(settings.lowercase);
	EXPECT_FALSE(settings.uppercase);
	EXPECT_FALSE(settings.special);
	EXPECT_FALSE(settings.mnemonic);
	EXPECT_FALSE(settings.history);
	EXPECT_EQ(settings.custom, "");
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_PasswordLengthWithoutNumber) {
	char* argv[] = {"./minipass.exe", "-l"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_PasswordLengthIsNumber) {
	char* argv[] = {"./minipass.exe", "-l", "25"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 25);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_PasswordLengthIsString) {
	char* argv[] = {"./minipass.exe", "-l", "abc"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_PasswordLengthIsSpecialCharacter) {
	char* argv[] = {"./minipass.exe", "-l", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_numbersShort) {
	char* argv[] = {"./minipass.exe", "-n"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.numbers, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_numbersLong) {
	char* argv[] = {"./minipass.exe", "--numbers"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.numbers, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_lowercaseShort) {
	char* argv[] = {"./minipass.exe", "-o"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.lowercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_lowercaseLong) {
	char* argv[] = {"./minipass.exe", "--lower"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.lowercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_uppercaseShort) {
	char* argv[] = {"./minipass.exe", "-u"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.uppercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_uppercaseLong) {
	char* argv[] = {"./minipass.exe", "--upper"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.uppercase, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_specialShort) {
	char* argv[] = {"./minipass.exe", "-s"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.special, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_specialLong) {
	char* argv[] = {"./minipass.exe", "--special"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.special, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_KeepHistoryShort) {
	char* argv[] = {"./minipass.exe", "-k"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.history, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_KeepHistoryLong) {
	char* argv[] = {"./minipass.exe", "--history"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.history, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_MakeMnemonicShort) {
	char* argv[] = {"./minipass.exe", "-m"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_MakeMnemonicLong) {
	char* argv[] = {"./minipass.exe", "--mnemonic"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_MultipleShortOptions) {
	char* argv[] = {"./minipass.exe", "-dnouskm"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.numbers, true);
	EXPECT_EQ(settings.lowercase, true);
	EXPECT_EQ(settings.uppercase, true);
	EXPECT_EQ(settings.special, true);
	EXPECT_EQ(settings.history, true);
	EXPECT_EQ(settings.mnemonic, true);
}

TEST(GoogleTestMinipass, ParseCommandLineArguments_MultipleShortOptionsWithLengthAndCustom) {
	char* argv[] = {"./minipass.exe", "-nuskmlc"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	ProgramOptions settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.numbers, true);
	EXPECT_EQ(settings.uppercase, true);
	EXPECT_EQ(settings.special, true);
	EXPECT_EQ(settings.history, true);
	EXPECT_EQ(settings.mnemonic, true);
	EXPECT_EQ(settings.passwordLength, 16);
	EXPECT_EQ(settings.custom, "");
}
