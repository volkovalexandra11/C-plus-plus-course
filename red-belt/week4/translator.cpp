#include <iostream>
#include <algorithm>

#include "test_runner.h"
#include <string>
#include <deque>
#include <vector>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		const auto source_pos = natural_.find(source);
		const auto target_pos = reverse_.find(target);

		if (source_pos == natural_.end() && target_pos == reverse_.end()) {
			storage_.push_front(string(source));
			storage_.push_front(string(target));

			natural_[*next(storage_.begin())] = *storage_.begin();
			reverse_[*storage_.begin()] = *next(storage_.begin());

		} else if (target_pos == reverse_.end()) {
			storage_.push_front(string(target));
			natural_[source] = *storage_.begin();
			reverse_[*storage_.begin()] = source_pos->first;

		} else if (source_pos == natural_.end()) {
			storage_.push_front(string(source));
			reverse_[target] = *storage_.begin();
			natural_[*storage_.begin()] = target_pos->first;
		}
	};

	string_view TranslateForward(string_view source) const {
		try {
			return natural_.at(source);
		} catch (out_of_range&) {
			return "";
		}
	};

	string_view TranslateBackward(string_view target) const {
		try {
			return reverse_.at(target);
		} catch (out_of_range&) {
			return "";
		}
	};

private:
	map<string_view, string_view> natural_;
	map<string_view, string_view> reverse_;
	deque<string> storage_;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

void NoSimpleTest()
{
	Translator translator;

	{
		string s = "okno";
		string t = "window";

		translator.Add(s, t);
	}

	{
		string s = "stol";
		string t = "table";

		translator.Add(s, t);
	}

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

	{
		string s = "okoshko";
		string t = "window";

		translator.Add(s, t);
	}

	{
		string s = "stol";
		string t = "desk";

		translator.Add(s, t);
	}

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateForward("okoshko"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("window"), "okoshko");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

	ASSERT_EQUAL(translator.TranslateForward("stol"), "desk");
	ASSERT_EQUAL(translator.TranslateBackward("desk"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateForward("table"), "");

	{
		string s1 = "roman";
		string t1 = "novel";
		string t2 = "romance";

		translator.Add(s1, t1);
		ASSERT_EQUAL(translator.TranslateForward("roman"), "novel");
		ASSERT_EQUAL(translator.TranslateBackward("novel"), "roman");

		translator.Add(s1, t2);
		ASSERT_EQUAL(translator.TranslateForward("roman"), "romance");
		ASSERT_EQUAL(translator.TranslateBackward("novel"), "roman");
		ASSERT_EQUAL(translator.TranslateBackward("romance"), "roman");
	}

	ASSERT_EQUAL(translator.TranslateBackward("novel"), "roman");
	ASSERT_EQUAL(translator.TranslateForward("roman"), "romance");
	ASSERT_EQUAL(translator.TranslateBackward("romance"), "roman");
}


int main3() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	RUN_TEST(tr, NoSimpleTest);
	return 0;
}