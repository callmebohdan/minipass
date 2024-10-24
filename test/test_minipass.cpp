#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "../src/minipass.hpp"

TEST(TestMiniPass, DefaultConstructor) {
	MiniPass minipass;
	ASSERT_EQ(minipass.GetPasswordLength(), 16);
	ASSERT_FALSE(minipass.IsRemoveNumbers());
	ASSERT_FALSE(minipass.IsRemoveLowercaseLetters());
	ASSERT_FALSE(minipass.IsRemoveUppercaseLetters());
	ASSERT_FALSE(minipass.IsRemoveSpecialCharacters());
	ASSERT_FALSE(minipass.IsMakeMnemonic());
	ASSERT_FALSE(minipass.IsKeepHistory());
	ASSERT_EQ(minipass.GetRemoveCustomCharacters(), "");
}

TEST(TestMiniPass, ParametrizedConstructor) {
	PasswordSettings settings;
	settings.passwordLength = 32;
	settings.removeNumbers = true;
	settings.removeLowercaseLetters = true;
	settings.removeUppercaseLetters = true;
	settings.removeSpecialCharacters = true;
	settings.makeMnemonic = true;
	settings.keepHistory = true;
	settings.removeCustomCharacters = "true";

	MiniPass minipass(settings);

	ASSERT_EQ(minipass.GetPasswordLength(), settings.passwordLength);
	ASSERT_EQ(minipass.IsRemoveNumbers(), settings.removeNumbers);
	ASSERT_EQ(minipass.IsRemoveLowercaseLetters(), settings.removeLowercaseLetters);
	ASSERT_EQ(minipass.IsRemoveUppercaseLetters(), settings.removeUppercaseLetters);
	ASSERT_EQ(minipass.IsRemoveSpecialCharacters(), settings.removeSpecialCharacters);
	ASSERT_EQ(minipass.IsMakeMnemonic(), settings.makeMnemonic);
	ASSERT_EQ(minipass.IsKeepHistory(), settings.keepHistory);
	ASSERT_EQ(minipass.GetRemoveCustomCharacters(), settings.removeCustomCharacters);
}

TEST(TestMiniPass, CopyConstructor) {
	PasswordSettings minipassOriginal;
	minipassOriginal.passwordLength = 32;
	minipassOriginal.removeNumbers = true;
	minipassOriginal.removeLowercaseLetters = true;
	minipassOriginal.removeUppercaseLetters = true;
	minipassOriginal.removeSpecialCharacters = true;
	minipassOriginal.makeMnemonic = true;
	minipassOriginal.keepHistory = true;
	minipassOriginal.removeCustomCharacters = "true";

	MiniPass minipassCopy(minipassOriginal);

	ASSERT_EQ(minipassCopy.GetPasswordLength(), minipassOriginal.passwordLength);
	ASSERT_EQ(minipassCopy.IsRemoveNumbers(), minipassOriginal.removeNumbers);
	ASSERT_EQ(minipassCopy.IsRemoveLowercaseLetters(), minipassOriginal.removeLowercaseLetters);
	ASSERT_EQ(minipassCopy.IsRemoveUppercaseLetters(), minipassOriginal.removeUppercaseLetters);
	ASSERT_EQ(minipassCopy.IsRemoveSpecialCharacters(), minipassOriginal.removeSpecialCharacters);
	ASSERT_EQ(minipassCopy.IsMakeMnemonic(), minipassOriginal.makeMnemonic);
	ASSERT_EQ(minipassCopy.IsKeepHistory(), minipassOriginal.keepHistory);
	ASSERT_EQ(minipassCopy.GetRemoveCustomCharacters(), minipassOriginal.removeCustomCharacters);
}

TEST(TestMiniPass, AssignmentOperator) {
	PasswordSettings minipassOriginal;
	minipassOriginal.passwordLength = 32;
	minipassOriginal.removeNumbers = true;
	minipassOriginal.removeLowercaseLetters = true;
	minipassOriginal.removeUppercaseLetters = true;
	minipassOriginal.removeSpecialCharacters = true;
	minipassOriginal.makeMnemonic = true;
	minipassOriginal.keepHistory = true;
	minipassOriginal.removeCustomCharacters = "true";

	MiniPass minipassOther;
	minipassOther = minipassOriginal;

	ASSERT_EQ(minipassOther.GetPasswordLength(), minipassOriginal.passwordLength);
	ASSERT_EQ(minipassOther.IsRemoveNumbers(), minipassOriginal.removeNumbers);
	ASSERT_EQ(minipassOther.IsRemoveLowercaseLetters(), minipassOriginal.removeLowercaseLetters);
	ASSERT_EQ(minipassOther.IsRemoveUppercaseLetters(), minipassOriginal.removeUppercaseLetters);
	ASSERT_EQ(minipassOther.IsRemoveSpecialCharacters(), minipassOriginal.removeSpecialCharacters);
	ASSERT_EQ(minipassOther.IsMakeMnemonic(), minipassOriginal.makeMnemonic);
	ASSERT_EQ(minipassOther.IsKeepHistory(), minipassOriginal.keepHistory);
	ASSERT_EQ(minipassOther.GetRemoveCustomCharacters(), minipassOriginal.removeCustomCharacters);
}

TEST(TestMiniPass, GenerateRandomIndex_EmptySet)
{
	std::vector<int> inputSet;
	EXPECT_THROW(GenerateRandomIndex(inputSet), std::out_of_range);
}

TEST(TestMiniPass, BigSet) {
	std::vector<int> inputSet(1000000, 1);
	for (int i = 0; i < 1000000; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, GenerateRandomIndex_OverflowSet) {
	std::vector<int> inputSet(static_cast<size_t>(std::numeric_limits<int>::max()) + 1);
	EXPECT_THROW(GenerateRandomIndex(inputSet), std::overflow_error);
}

TEST(TestMiniPass, GenerateRandomIndex_IntegerSet)
{
	std::vector<int> inputSet{1, 2, 3, 4, 5};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, GenerateRandomIndex_StringSet)
{
	std::vector<std::string> inputSet{"a", "b", "c", "d", "e"};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, GenerateRandomIndex_DoubleSet)
{
	std::vector<double> inputSet{0.1, 0.2, 0.3, 0.4, 0.5};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, GenerateRandomIndex_FloatSet)
{
	std::vector<float> inputSet{0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, GenerateRandomIndex_CharSet)
{
	std::vector<char> inputSet{'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i < 100; ++i) {
		int index = GenerateRandomIndex(inputSet);
		EXPECT_GE(index, 0);
		EXPECT_LT(index, static_cast<int>(inputSet.size()));
	}
}

TEST(TestMiniPass, ParseCommandLineArguments_DefaultSettings) {
	char* argv[] = {"./minipass.exe"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_TRUE(settings.defaultSettings);
	EXPECT_EQ(settings.passwordLength, 16);
	EXPECT_FALSE(settings.removeNumbers);
	EXPECT_FALSE(settings.removeLowercaseLetters);
	EXPECT_FALSE(settings.removeUppercaseLetters);
	EXPECT_FALSE(settings.removeSpecialCharacters);
	EXPECT_FALSE(settings.makeMnemonic);
	EXPECT_FALSE(settings.keepHistory);
	EXPECT_EQ(settings.removeCustomCharacters, "");
}

TEST(TestMiniPass, ParseCommandLineArguments_DefaultSettingsOption) {
	char* argv[] = {"./minipass.exe -d"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_TRUE(settings.defaultSettings);
	EXPECT_EQ(settings.passwordLength, 16);
	EXPECT_FALSE(settings.removeNumbers);
	EXPECT_FALSE(settings.removeLowercaseLetters);
	EXPECT_FALSE(settings.removeUppercaseLetters);
	EXPECT_FALSE(settings.removeSpecialCharacters);
	EXPECT_FALSE(settings.makeMnemonic);
	EXPECT_FALSE(settings.keepHistory);
	EXPECT_EQ(settings.removeCustomCharacters, "");
}

TEST(TestMiniPass, ParseCommandLineArguments_PasswordLengthWithoutNumber) {
	char* argv[] = {"./minipass.exe", "-l"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(TestMiniPass, ParseCommandLineArguments_PasswordLengthIsNumber) {
	char* argv[] = {"./minipass.exe", "-l", "25"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 25);
}

TEST(TestMiniPass, ParseCommandLineArguments_PasswordLengthIsString) {
	char* argv[] = {"./minipass.exe", "-l", "abc"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(TestMiniPass, ParseCommandLineArguments_PasswordLengthIsSpecialCharacter) {
	char* argv[] = {"./minipass.exe", "-l", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.passwordLength, 16);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveNumbersShort) {
	char* argv[] = {"./minipass.exe", "-n"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeNumbers, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveNumbersLong) {
	char* argv[] = {"./minipass.exe", "--numbers"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeNumbers, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveLowercaseLettersShort) {
	char* argv[] = {"./minipass.exe", "-o"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeLowercaseLetters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveLowercaseLettersLong) {
	char* argv[] = {"./minipass.exe", "--lower"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeLowercaseLetters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveUppercaseLettersShort) {
	char* argv[] = {"./minipass.exe", "-u"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeUppercaseLetters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveUppercaseLettersLong) {
	char* argv[] = {"./minipass.exe", "--upper"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeUppercaseLetters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveSpecialCharactersShort) {
	char* argv[] = {"./minipass.exe", "-s"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeSpecialCharacters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_RemoveSpecialCharactersLong) {
	char* argv[] = {"./minipass.exe", "--special"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeSpecialCharacters, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_KeepHistoryShort) {
	char* argv[] = {"./minipass.exe", "-k"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.keepHistory, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_KeepHistoryLong) {
	char* argv[] = {"./minipass.exe", "--history"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.keepHistory, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_MakeMnemonicShort) {
	char* argv[] = {"./minipass.exe", "-m"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.makeMnemonic, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_MakeMnemonicLong) {
	char* argv[] = {"./minipass.exe", "--mnemonic"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.makeMnemonic, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_MultipleShortOptions) {
	char* argv[] = {"./minipass.exe", "-dnouskm"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.defaultSettings, true);
	EXPECT_EQ(settings.removeNumbers, true);
	EXPECT_EQ(settings.removeLowercaseLetters, true);
	EXPECT_EQ(settings.removeUppercaseLetters, true);
	EXPECT_EQ(settings.removeSpecialCharacters, true);
	EXPECT_EQ(settings.keepHistory, true);
	EXPECT_EQ(settings.makeMnemonic, true);
}

TEST(TestMiniPass, ParseCommandLineArguments_MultipleShortOptionsWithLengthAndCustom) {
	char* argv[] = {"./minipass.exe", "-nuskmlc"};
	int argc = sizeof(argv) / sizeof(argv[0]);

	PasswordSettings settings = ParseCommandLineArguments(argc, argv);

	EXPECT_EQ(settings.removeNumbers, true);
	EXPECT_EQ(settings.removeUppercaseLetters, true);
	EXPECT_EQ(settings.removeSpecialCharacters, true);
	EXPECT_EQ(settings.keepHistory, true);
	EXPECT_EQ(settings.makeMnemonic, true);
	EXPECT_EQ(settings.passwordLength, 16);
	EXPECT_EQ(settings.removeCustomCharacters, "");
}
