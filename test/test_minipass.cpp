#include <gtest/gtest.h>
#include "../src/minipass.hpp"
#include "../src/utils.hpp"

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
