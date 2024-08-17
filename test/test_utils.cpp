#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "../src/utils.hpp"

TEST(UtilsGenerateRandomIndex, EmptySet)
{
    std::vector<int> inputSet;
    EXPECT_THROW(GenerateRandomIndex(inputSet), std::out_of_range);
}

TEST(GenerateRandomIndexTest, BigSet) {
    std::vector<int> inputSet(1000000, 1);
    for (int i = 0; i < 1000000; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(GenerateRandomIndexTest, OverflowSet) {
	std::vector<int> inputSet(static_cast<size_t>(std::numeric_limits<int>::max()) + 1);
    EXPECT_THROW(GenerateRandomIndex(inputSet), std::overflow_error);
}

TEST(UtilsGenerateRandomIndex, IntegerSet)
{
	std::vector<int> inputSet{ 1, 2, 3, 4, 5 };
    for (int i = 0; i < 100; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(UtilsGenerateRandomIndex, StringSet)
{
    std::vector<std::string> inputSet{ "a", "b", "c", "d", "e" };
    for (int i = 0; i < 100; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(UtilsGenerateRandomIndex, DoubleSet)
{
    std::vector<double> inputSet{ 0.1, 0.2, 0.3, 0.4, 0.5 };
    for (int i = 0; i < 100; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(UtilsGenerateRandomIndex, FloatSet)
{
    std::vector<float> inputSet{ 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
    for (int i = 0; i < 100; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(UtilsGenerateRandomIndex, CharSet)
{
	std::vector<char> inputSet{ 'a', 'b', 'c', 'd', 'e' };
    for (int i = 0; i < 100; ++i) {
        int index = GenerateRandomIndex(inputSet);
        EXPECT_GE(index, 0);
        EXPECT_LT(index, static_cast<int>(inputSet.size()));
    }
}

TEST(UtilsParseCommandLineArguments, DefaultSettings) {
    char* argv[] = { "./minipass.exe" };
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

TEST(UtilsParseCommandLineArguments, DefaultSettingsOption) {
    char* argv[] = { "./minipass.exe -d" };
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

TEST(UtilsParseCommandLineArguments, PasswordLengthWithoutNumber) {
    char* argv[] = { "./minipass.exe", "-l" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.passwordLength, 16);
}

TEST(UtilsParseCommandLineArguments, PasswordLengthWithNumber) {
    char* argv[] = { "./minipass.exe", "-l", "25" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.passwordLength, 25);
}

TEST(UtilsParseCommandLineArguments, PasswordLengthWithString) {
    char* argv[] = { "./minipass.exe", "-l", "abc" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    EXPECT_ANY_THROW({ ParseCommandLineArguments(argc, argv); });
}

TEST(UtilsParseCommandLineArguments, RemoveNumbersShort) {
    char* argv[] = { "./minipass.exe", "-n" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeNumbers, true);
}

TEST(UtilsParseCommandLineArguments, RemoveNumbersLong) {
    char* argv[] = { "./minipass.exe", "--numbers" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeNumbers, true);
}

TEST(UtilsParseCommandLineArguments, RemoveLowercaseLettersShort) {
    char* argv[] = { "./minipass.exe", "-o" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeLowercaseLetters, true);
}

TEST(UtilsParseCommandLineArguments, RemoveLowercaseLettersLong) {
    char* argv[] = { "./minipass.exe", "--lower" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeLowercaseLetters, true);
}

TEST(UtilsParseCommandLineArguments, RemoveUppercaseLettersShort) {
    char* argv[] = { "./minipass.exe", "-u" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeUppercaseLetters, true);
}

TEST(UtilsParseCommandLineArguments, RemoveUppercaseLettersLong) {
    char* argv[] = { "./minipass.exe", "--upper" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeUppercaseLetters, true);
}

TEST(UtilsParseCommandLineArguments, RemoveSpecialCharactersShort) {
    char* argv[] = { "./minipass.exe", "-s" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeSpecialCharacters, true);
}

TEST(UtilsParseCommandLineArguments, RemoveSpecialCharactersLong) {
    char* argv[] = { "./minipass.exe", "--special" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.removeSpecialCharacters, true);
}

TEST(UtilsParseCommandLineArguments, KeepHistoryShort) {
    char* argv[] = { "./minipass.exe", "-k" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.keepHistory, true);
}

TEST(UtilsParseCommandLineArguments, KeepHistoryLong) {
    char* argv[] = { "./minipass.exe", "--history" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.keepHistory, true);
}

TEST(UtilsParseCommandLineArguments, MakeMnemonicShort) {
    char* argv[] = { "./minipass.exe", "-m" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.makeMnemonic, true);
}

TEST(UtilsParseCommandLineArguments, MakeMnemonicLong) {
    char* argv[] = { "./minipass.exe", "--mnemonic" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    PasswordSettings settings = ParseCommandLineArguments(argc, argv);

    EXPECT_EQ(settings.makeMnemonic, true);
}

TEST(UtilsParseCommandLineArguments, MultipleShortOptions) {
    char* argv[] = { "./minipass.exe", "-dnouskm" };
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

TEST(UtilsParseCommandLineArguments, MultipleShortOptionsWith) {
    char* argv[] = { "./minipass.exe", "-dnouskm" };
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

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
