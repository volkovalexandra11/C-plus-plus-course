#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
	vector<string> words;
	string s_copy = s + ' ';
	while (s_copy.begin() != s_copy.end()) {
		auto white_space_pos = find(s_copy.begin(), s_copy.end(), ' ');
		if (white_space_pos == s_copy.end())
			break;
		string word = string(begin(s_copy), white_space_pos);
		s_copy = string(++white_space_pos, end(s_copy));
		words.push_back(word);
	}
	return words;
}