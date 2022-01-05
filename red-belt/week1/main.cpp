//#include <iostream>
//
//using namespace std;
//
//int main() {
//	cout << "Hello, world!" << endl;
//	return 0;
//}

#include "test_runner.h"

using namespace std;

template<typename T>
class Table {
public:
	Table(size_t rows, size_t cols) {
		Resize(rows, cols);
	}

	pair<size_t, size_t> Size() const {
		if (!content.empty() && !content[0].empty())
			return {x, y};
		return {0, 0};
	}

	void Resize(size_t rows, size_t cols) {
		x = rows;
		y = cols;
		content.resize(rows);
		for (auto& row: content) {
			row.resize(cols);
		}
	}

	vector<T>& operator[](size_t ind) {
		return content[ind];
	}

	vector<T>& operator[](size_t ind) const {
		return content[ind];
	}

private:
	vector<vector<T>>content;
	size_t x;
	size_t y;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
