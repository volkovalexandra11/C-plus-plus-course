#include "test_runner.h"

using namespace std;


bool IsPalindrom(const string& str) {
	// Р’С‹ РјРѕР¶РµС‚Рµ РІСЃС‚Р°РІР»СЏС‚СЊ СЃСЋРґР° СЂР°Р·Р»РёС‡РЅС‹Рµ СЂРµР°Р»РёР·Р°С†РёРё С„СѓРЅРєС†РёРё,
	// С‡С‚РѕР±С‹ РїСЂРѕРІРµСЂРёС‚СЊ, С‡С‚Рѕ РІР°С€Рё С‚РµСЃС‚С‹ РїСЂРѕРїСѓСЃРєР°СЋС‚ РєРѕСЂСЂРµРєС‚РЅС‹Р№ РєРѕРґ
	// Рё Р»РѕРІСЏС‚ РЅРµРєРѕСЂСЂРµРєС‚РЅС‹Р№
}

bool isPalindrome(const string& str) {
	cerr << std::boolalpha;
	cerr << "Line is " << str << " result is " << IsPalindrom(str) << endl;
	return IsPalindrom(str);
}

void TestEmpty() {
	Assert(isPalindrome(""), "Empty is palindrome");
}

void TestLengthOne() {
	Assert(isPalindrome("a"), "One symbol is palindrome");
}

void TestBasic() {
	Assert(isPalindrome("madam"), "Madam must be palindrome");
	Assert(isPalindrome("level"), "Level must be palindrome");
}

void TestDoesNotIgnoreWhitespace() {
	Assert(isPalindrome("mama amam"), "mama amam must be palindrome");
}

void TestEvenLength() {
	Assert(isPalindrome("mammam"), "mammam must be palindrome");
}

void TestDoesNotIgnoreCase() {
	Assert(!isPalindrome("maaM"), "maaM must be palindrome");
	Assert(!isPalindrome("Maam"), "Maam must be palindrome ");
	Assert(!isPalindrome("mAam"), "mAam must be palindrome");
	Assert(isPalindrome("mAAm"), "mAAm must be palindrome");
	Assert(!isPalindrome("Madam, I'm Adam"), "Madam, I'm Adam");
	Assert(isPalindrome("madam i madam"), "madam i madam");
	Assert(!isPalindrome(" madam i madam"), "madam i madam");
	Assert(!isPalindrome("madam i madam "), "madam i madam");
}

void TestMultiplePalindromeString() {
	Assert(!isPalindrome("MaaM ssss a issi"), "MaaM ssss a issi is not palindrome");
}

void TestFirstAndLast() {
	Assert(!isPalindrome("amaam"), "amaam not palindrome");
	Assert(!isPalindrome("maama"), "maama not palindrome");
}

void TestAll3() {
	TestRunner runner;
	runner.RunTest(TestEmpty, "TestEmpty");
	runner.RunTest(TestLengthOne, "TestLengthOne");
	runner.RunTest(TestBasic, "TestBasic");
	runner.RunTest(TestDoesNotIgnoreWhitespace,"TestDoesNotIgnoreWhitespace");
	runner.RunTest(TestEvenLength, "TestEvenLength");
	runner.RunTest(TestDoesNotIgnoreCase, "TestDoesNotIgnoreCase");
	runner.RunTest(TestMultiplePalindromeString, "TestMultiplePalindromeString");
	runner.RunTest(TestFirstAndLast, "TestFirstAndLast");
}

int main34() {
	TestAll3();
	return 0;
}

