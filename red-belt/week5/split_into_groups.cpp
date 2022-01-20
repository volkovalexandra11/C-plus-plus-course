#include "test_runner.h"

#include <vector>

using namespace std;

template<typename Token>
using Sentence = vector<Token>;

template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> res;
	Sentence<Token> cur_sentence;

	for(auto token_iter = tokens.begin(); token_iter != tokens.end();) {
		if (token_iter -> IsEndSentencePunctuation()) {
			while (token_iter != tokens.end() && token_iter -> IsEndSentencePunctuation()) {
				cur_sentence.push_back(move(*token_iter));
				++token_iter;
			}
			res.push_back(move(cur_sentence));
		} else {
			cur_sentence.push_back(move(*token_iter));
			++token_iter;
		}
	}

	if (!cur_sentence.empty())
		res.push_back(move(cur_sentence));

	return res;
}


struct TestToken {
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
		return is_end_sentence_punctuation;
	}

	bool operator==(const TestToken& other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

ostream& operator<<(ostream& stream, const TestToken& token) {
	return stream << token.data;
}

void TestSplitting() {
	ASSERT_EQUAL(
			SplitIntoSentences(vector<TestToken>({{"Split"},
												  {"into"},
												  {"sentences"},
												  {"!"}})),
			vector<Sentence<TestToken>>({
												{{"Split"}, {"into"}, {"sentences"}, {"!"}}
										})
	);

	ASSERT_EQUAL(
			SplitIntoSentences(vector<TestToken>({{"Split"},
												  {"into"},
												  {"sentences"},
												  {"!", true}})),
			vector<Sentence<TestToken>>({
												{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
										})
	);

	ASSERT_EQUAL(
			SplitIntoSentences(vector<TestToken>({{"Split"},
												  {"into"},
												  {"sentences"},
												  {"!", true},
												  {"!", true},
												  {"Without"},
												  {"copies"},
												  {".", true}})),
			vector<Sentence<TestToken>>({
												{{"Split"},   {"into"},   {"sentences"}, {"!", true}, {"!", true}},
												{{"Without"}, {"copies"}, {".", true}},
										})
	);
}

int main4() {
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}