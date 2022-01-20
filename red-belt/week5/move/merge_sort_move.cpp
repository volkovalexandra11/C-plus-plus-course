#include "../test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t size = range_end - range_begin;

	if (size < 2)
		return;
	vector<typename RandomIt::value_type> tmp_vec(make_move_iterator(range_begin),
												  make_move_iterator(range_end));
	vector<typename RandomIt::value_type> temp;

	size_t first_part = size / 3;
	size_t second_part = 2 * size / 3;

	MergeSort(tmp_vec.begin(), tmp_vec.begin() + tmp_vec.size() / 3);
	MergeSort(tmp_vec.begin() + tmp_vec.size() / 3, tmp_vec.begin() + tmp_vec.size() * 2 / 3);
	MergeSort(tmp_vec.begin() + tmp_vec.size() * 2 / 3, tmp_vec.end());

	merge(
			make_move_iterator(tmp_vec.begin()),
			make_move_iterator(tmp_vec.begin() + first_part),
			make_move_iterator(tmp_vec.begin() + first_part),
			make_move_iterator(tmp_vec.begin() + second_part),
			back_inserter(temp)
	);

	merge(make_move_iterator(temp.begin()),
		  make_move_iterator(temp.end()),
		  make_move_iterator(tmp_vec.begin() + second_part),
		  make_move_iterator(tmp_vec.end()),
		  range_begin
	);
}

void TestIntVector() {
	vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main6() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}

