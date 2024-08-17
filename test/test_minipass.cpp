#include <gtest/gtest.h>
#include "../src/minipass.hpp"
#include "../src/utils.hpp"

TEST(Minipass, DefaultConstructor) {
	MiniPass minipass;

	ASSERT_EQ(minipass.passwordLength, 16);
	ASSERT_FALSE(minipass.removeNumbers);
	ASSERT_FALSE(minipass.removeLowercaseLetters);
	ASSERT_FALSE(minipass.removeUppercaseLetters);
	ASSERT_FALSE(minipass.removeSpecialCharacters);
	ASSERT_FALSE(minipass.makeMnemonic);
	ASSERT_FALSE(minipass.keepHistory);
	ASSERT_EQ(minipass.removeCustomCharacters, "");
}

TEST(Minipass, ParametrizedConstructor) {
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

	ASSERT_EQ(minipass.passwordLength, settings.passwordLength);
	ASSERT_EQ(minipass.removeNumbers, settings.removeNumbers);
	ASSERT_EQ(minipass.removeLowercaseLetters, settings.removeLowercaseLetters);
	ASSERT_EQ(minipass.removeUppercaseLetters, settings.removeUppercaseLetters);
	ASSERT_EQ(minipass.removeSpecialCharacters, settings.removeSpecialCharacters);
	ASSERT_EQ(minipass.makeMnemonic, settings.makeMnemonic);
	ASSERT_EQ(minipass.keepHistory, settings.keepHistory);
	ASSERT_EQ(minipass.removeCustomCharacters, settings.removeCustomCharacters);
}

TEST(Minipass, CopyConstructor) {
	MiniPass minipassOriginal;
	minipassOriginal.passwordLength = 32;
	minipassOriginal.removeNumbers = true;
	minipassOriginal.removeLowercaseLetters = true;
	minipassOriginal.removeUppercaseLetters = true;
	minipassOriginal.removeSpecialCharacters = true;
	minipassOriginal.makeMnemonic = true;
	minipassOriginal.keepHistory = true;
	minipassOriginal.removeCustomCharacters = "true";

	MiniPass minipassCopy(minipassOriginal);

	ASSERT_EQ(minipassCopy.passwordLength, minipassOriginal.passwordLength);
	ASSERT_EQ(minipassCopy.removeNumbers, minipassOriginal.removeNumbers);
	ASSERT_EQ(minipassCopy.removeLowercaseLetters, minipassOriginal.removeLowercaseLetters);
	ASSERT_EQ(minipassCopy.removeUppercaseLetters, minipassOriginal.removeUppercaseLetters);
	ASSERT_EQ(minipassCopy.removeSpecialCharacters, minipassOriginal.removeSpecialCharacters);
	ASSERT_EQ(minipassCopy.makeMnemonic, minipassOriginal.makeMnemonic);
	ASSERT_EQ(minipassCopy.keepHistory, minipassOriginal.keepHistory);
	ASSERT_EQ(minipassCopy.removeCustomCharacters, minipassOriginal.removeCustomCharacters);
}

TEST(Minipass, AssignmentOperator) {
	MiniPass minipassOriginal;
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

	ASSERT_EQ(minipassOther.passwordLength, minipassOriginal.passwordLength);
	ASSERT_EQ(minipassOther.removeNumbers, minipassOriginal.removeNumbers);
	ASSERT_EQ(minipassOther.removeLowercaseLetters, minipassOriginal.removeLowercaseLetters);
	ASSERT_EQ(minipassOther.removeUppercaseLetters, minipassOriginal.removeUppercaseLetters);
	ASSERT_EQ(minipassOther.removeSpecialCharacters, minipassOriginal.removeSpecialCharacters);
	ASSERT_EQ(minipassOther.makeMnemonic, minipassOriginal.makeMnemonic);
	ASSERT_EQ(minipassOther.keepHistory, minipassOriginal.keepHistory);
	ASSERT_EQ(minipassOther.removeCustomCharacters, minipassOriginal.removeCustomCharacters);
}
