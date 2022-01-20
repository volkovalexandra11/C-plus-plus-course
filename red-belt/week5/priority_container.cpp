#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class PriorityCollection {
public:
	using Id = int;

	Id Add(T object) {
		const Id new_id = items.size();
		items.push_back({move(object)});
		sorted.insert({0, new_id});
		return new_id;
	};

	template<typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
			 IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			*ids_begin++ = Add(move(*range_begin++));
		}
	}

	bool IsValid(Id id) const {
		return id >= 0 && id < static_cast<int>(items.size()) && items[id].priority != MIN_PRIORITY;
	}

	const T& Get(Id id) const {
		return items[id].data;
	}

	void Promote(Id id) {
		auto& item = items[id];
		const int old_priority = item.priority;
		const int new_priority = ++item.priority;
		sorted.erase({old_priority, id});
		sorted.insert({new_priority, id});
	}

	pair<const T&, int> GetMax() const {
		const auto& item = items[prev(sorted.end())->second];
		return {item.data, item.priority};
	}

	pair<T, int> PopMax() {
		const auto sorted_objects_it = prev(sorted.end());
		auto& item = items[sorted_objects_it->second];
		sorted.erase(sorted_objects_it);
		const int priority = item.priority;
		item.priority = MIN_PRIORITY;
		return { move(item.data), priority };
	}

private:
	struct PriorityItem {
		T data;
		int priority = 0;
	};

	static const int MIN_PRIORITY = -1;

	vector<PriorityItem> items;
	set<pair<int, Id>> sorted;
};


class StringNonCopyable : public string {
public:
	using string::string;
	StringNonCopyable(const StringNonCopyable&) = delete;

	StringNonCopyable(StringNonCopyable&&) = default;

	StringNonCopyable& operator=(const StringNonCopyable&) = delete;

	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main8() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}