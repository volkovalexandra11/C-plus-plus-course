#include "test_runner.h"

#include <map>
#include <string>
#include <future>
#include <cmath>
#include <numeric>
#include <iostream>
#include <vector>

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

struct Stats {
	map<string, int> word_frequences;

	void operator+=(const Stats& other);
};

void Stats::operator+=(const Stats& other) {
	for (auto[word, freq]: other.word_frequences) {
		word_frequences[word] += freq;
	}
}

vector<string> SplitStream(istream& input) {
	vector<string> result;
	string line;

	while (input >> line) {
		result.push_back(line);
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, const vector<string>& input) {
	Stats result;
	for (const auto& i: input) {
		if (key_words.find(i) != key_words.end()) {
			result.word_frequences[i] += 1;
		}
	}

	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	Stats main;
	const size_t THREAD_COUNT = 4;
	vector<future<Stats>> futures;
	auto words = SplitStream(input);
	const size_t PAGE_SIZE = ceil(words.size() * 1.0 / THREAD_COUNT);
	auto const pages = Paginate(words, PAGE_SIZE);

	for (auto& page: pages) {
		vector<string> a = vector(page.begin(), page.end());
		futures.push_back(
				async(
						ExploreKeyWordsSingleThread, ref(key_words), a
				)
		);
	}

	for (auto& f: futures) {
		auto a = f.get();
		main += a;
	}

	return main;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
			{"yangle", 6},
			{"rocks",  2},
			{"sucks",  1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}