#include "test_runner.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <list>

using namespace std;


class Editor {
public:
	Editor() {
		carriage_ = text_.begin();
	};

	void Left() {
		if (carriage_ != text_.begin())
			carriage_--;
	};

	void Right() {
		if (carriage_ != text_.end())
			carriage_++;
	};

	void Insert(char token) {
		text_.insert(carriage_, token);
	};

	void Cut(size_t tokens = 1) {
		tokens = get_size_(tokens);
		auto start = carriage_;
		auto end = carriage_;

		for (auto i = 0; i < tokens; i++) {
			Right();
			end++;
		}

		buffer_.clear();
		if (start != end) {
			buffer_.splice(buffer_.begin(), text_, start, end);
		}
	};

	void Copy(size_t tokens = 1) {
		tokens = get_size_(tokens);
		auto start = carriage_;
		auto end = carriage_;

		for (auto i = 0; i < tokens; i++) {
			end++;
		}

		buffer_.clear();
		if (start != end) {
			buffer_ = {start, end};
		}
	};

	void Paste(){
		text_.insert(carriage_, buffer_.begin(), buffer_.end());
	};

	string GetText() const {
		return {text_.begin(), text_.end()};
	};

private:
	list<char> buffer_;
	list<char> text_;
	list<char>::iterator carriage_;

	size_t get_size_(size_t tokens_size) {
		size_t dist_to_end = distance(carriage_, text_.end());
		return (tokens_size > dist_to_end) ? dist_to_end : tokens_size;
	}
};

void TypeText(Editor& editor, const string& text) {
	for (char c: text) {
		editor.Insert(c);
	}
}

void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for (size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);
		for (size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const string text = "esreveR";
	for (char c: text) {
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

int main5() {
	TestRunner tr;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	return 0;
}

