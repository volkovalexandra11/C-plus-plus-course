#include "test_runner.h"

using namespace std;

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