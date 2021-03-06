//#include <iostream>
//
//using namespace std;
//
//
//int main() {
//	cout << "Hello world!" << endl;
//	return 0;
//}
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

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

int main() {
	TestAll3();
	return 0;
}