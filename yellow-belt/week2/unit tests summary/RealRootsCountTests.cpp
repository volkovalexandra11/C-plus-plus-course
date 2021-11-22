#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x: s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x: s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
	os << "{";
	bool first = true;
	for (const auto &kv: m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string &hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const string &test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception &e) {
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

int GetDistinctRealRootCount(double a, double b, double c) {
	return a + b + c;
}

void TestLinearEquation() {
	auto expected = GetDistinctRealRootCount(0, 2, 5);
	Assert(expected == 1, "Failed basic");
	expected = GetDistinctRealRootCount(0, 0, 1);
	Assert(expected == 0, "Zero equals to non-zero");
	expected = GetDistinctRealRootCount(0, 1, 0);
	Assert(expected == 1, "Non-zero equals zero");
}

void TestBIsZero() {
	auto expected = GetDistinctRealRootCount(1, 0, -4);
	Assert(expected == 2, "Basic b = 0");
	expected = GetDistinctRealRootCount(0, 0, 4);
	Assert(expected == 0, "a = 0, b = 0, c != 0");
	expected = GetDistinctRealRootCount(-1, 0, 4);
	Assert(expected == 2, "a < 0, b = 0, c > 0");
	expected = GetDistinctRealRootCount(1, 0, 4);
	Assert(expected == 0, "a > 0, b = 0, c < 0");
}

void TestCIsZero() {
	auto expected = GetDistinctRealRootCount(1, 4, 0);
	Assert(expected == 2, "Basic c = 0");
	expected = GetDistinctRealRootCount(0, 4, 0);
	Assert(expected == 1, "a = 0, b != 0, c = 0");
	expected = GetDistinctRealRootCount(-1, 2, 0);
	Assert(expected == 2, "a < 0, b = 0, c > 0");
	expected = GetDistinctRealRootCount(1, -4, 0);
	Assert(expected == 2, "a > 0, b < 0, c = 0");
	expected = GetDistinctRealRootCount(1, 0, 0);
	Assert(expected == 1, "a != 0, b = 0, c = 0");
}

void TestDLtZero() {
	auto expected = GetDistinctRealRootCount(1, 2, 5);
	Assert(expected == 0, "D < 0");
}

void TestDEqZero() {
	auto expected = GetDistinctRealRootCount(1, 4, 4);
	Assert(expected == 1, "D = 0");
}

void TestDGtZero() {
	auto expected = GetDistinctRealRootCount(1, -5, 6);
	Assert(expected == 2, "D > 0");
}

void TestAll() {
	TestRunner runner;
	runner.RunTest(TestLinearEquation, "TestLinearEquation");
	runner.RunTest(TestBIsZero, "TestBIsZero");
	runner.RunTest(TestCIsZero, "TestCIsZero");
	runner.RunTest(TestDLtZero, "TestDLtZero");
	runner.RunTest(TestDEqZero, "TestDEqZero");
	runner.RunTest(TestDGtZero, "TestDGtZero");
}

int main23() {
	TestAll();
	return 0;
}