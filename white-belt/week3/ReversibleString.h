#include <string>
#include <algorithm>

using namespace std;

#ifndef WEEK3_REVERSIBLESTRING_H
#define WEEK3_REVERSIBLESTRING_H


class ReversibleString {
public:
	ReversibleString() = default;;

	explicit ReversibleString(string s) {
		str = s;
	}

	void Reverse() {
		reverse(str.begin(), str.end());
	}

	string ToString() const {
		return str;
	}
private:
	string str;
};


#endif //WEEK3_REVERSIBLESTRING_H
