#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename RandomIt>
void MergeSort2(RandomIt range_begin, RandomIt range_end) {
	if ((range_end - range_begin) < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	int middle = (elements.end() - elements.begin()) / 2;
	auto middle_it = elements.begin() + middle;
	MergeSort2(elements.begin(), middle_it);
	MergeSort2(middle_it, elements.end());

	merge(elements.begin(), middle_it, middle_it ,elements.end(), range_begin);
}

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if ((range_end - range_begin) < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	int third = (elements.end() - elements.begin()) / 3;
	auto third_it = elements.begin() + third;
	auto two_third_it = elements.begin() + 2 * third;

	MergeSort(elements.begin(), third_it);
	MergeSort(third_it, two_third_it);
	MergeSort(two_third_it, elements.end());

	vector<typename RandomIt::value_type> tmp_result;

	merge(elements.begin(), third_it, third_it , two_third_it, back_inserter(tmp_result));
	merge(tmp_result.begin(), tmp_result.end(), two_third_it, elements.end(), range_begin);
}