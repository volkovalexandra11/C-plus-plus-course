#include <algorithm>
#include <iostream>
#include <future>

#include "test_runner.h"
#include <vector>
#include <numeric>

using namespace std;

template<typename TIter>
struct Page {
public:
	Page(TIter start, TIter finish) : start(start), finish(finish) {}

	TIter begin() const {
		return start;
	}

	TIter end() const {
		return finish;
	}

	size_t size() const {
		return finish - start;
	}

private:
	TIter start;
	TIter finish;
};

template<typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator anEnd, size_t pageSize) :
			start_iter(begin), end_iter(anEnd), page_size(pageSize) {
		for (auto i = start_iter; i != end_iter;) {
			size_t length = (end_iter - start_iter);
			auto rest_elements_count = length - page_size * pages.size();
			auto iter_shift = min(page_size, rest_elements_count);
			pages.push_back({i, next(i, iter_shift)});
			i += iter_shift;
		}
	}

	size_t size() const {
		return pages.size();
	}

	auto begin() const {
		return pages.begin();
	};

	auto end() const {
		return pages.end();
	}

private:
	Iterator start_iter;
	Iterator end_iter;
	size_t page_size;
	vector<Page<Iterator>> pages;
};

template<typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}

template <typename Container>
int64_t SumSubMatrix(const Container& matrix) {
	int64_t result = 0;
	for (const auto& row: matrix) {
		result += accumulate(row.begin(), row.end(), 0);
	}

	return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	int64_t result = 0;
	size_t page_size = 2500;
	vector<future<int64_t>> futures;
	futures.reserve(4);
	for (auto page: Paginate(matrix, page_size)) {
		futures.push_back(async([page] {
			return SumSubMatrix(page);
		}));
	}

	for (auto& f : futures) {
		result += f.get();
	}

	return result;
}

void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
			{1,  2,  3,  4},
			{5,  6,  7,  8},
			{9,  10, 11, 12},
			{13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main6() {
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
	return 0;
}