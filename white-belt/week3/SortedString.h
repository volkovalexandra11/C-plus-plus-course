#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef WEEK3_SORTEDSTRING_H
#define WEEK3_SORTEDSTRING_H


class SortedStrings {
public:
	void AddString(const string& s) {
		strings.push_back(s);
		Sort();
	}
	vector<string> GetSortedStrings() {
		return strings;
	}
private:
	vector<string> strings;
	void Sort() {
		sort(strings.begin(), strings.end());
	}
};



#endif //WEEK3_SORTEDSTRING_H
