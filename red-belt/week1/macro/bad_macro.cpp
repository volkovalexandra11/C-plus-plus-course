//#include <iostream>
//
//using namespace std;
//
//int main() {
//	cout << "Hello, world!" << endl;
//	return 0;
//}

#include "../test_runner.h"

#include <ostream>

using namespace std;

#define PRINT_VALUES(out, x, y) (out) << (x) << endl << (y) << endl

int main4() {
	TestRunner tr;
	tr.RunTest([] {
		ostringstream output;
		PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
	}, "PRINT_VALUES usage example");
	tr.RunTest([] {
		ostringstream output;
		int a, b;
		cin >> a >> b;
		if (a < b) PRINT_VALUES(output, 15, "red belt");
		else PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
	}, "PRINT_VALUES in else");
	return 0;
}