#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

#ifndef WEEK3_PERSON_H
#define WEEK3_PERSON_H

struct Name {
public:
	string FirstName{};
	string LastName{};
};

class Person {
public:
	Person(const string& firstName, const string& surname, const int& year) {
		name[year].FirstName = firstName;
		name[year].LastName = surname;
		birthYear = year;
	}

	void ChangeFirstName(int year, const string &first_name) {
		if (year < birthYear)
			return;
		name[year].FirstName = first_name;
	}

	void ChangeLastName(int year, const string &last_name) {
		if (year < birthYear)
			return;
		name[year].LastName = last_name;
	}

	string GetFullName(int year) const {
		if (year < birthYear)
			return "No person";

		if (name.begin()->first > year) {
			return "Incognito";
		}

		string first_name;
		string last_name;
		for (auto&[key, value]: name) {
			if (key > year) break;
			if (!value.FirstName.empty())
				first_name = value.FirstName;
			if (!value.LastName.empty())
				last_name = value.LastName;
		}

		if (first_name.empty()) {
			return last_name + " with unknown first name";
		}

		if (last_name.empty()) {
			return first_name + " with unknown last name";
		}

		return first_name + " " + last_name;
	}

	string GetFullNameWithHistory(int year) const {
		if (year < birthYear)
			return "No person";

		if (name.begin()->first > year) {
			return "Incognito";
		}

		vector<string> first_name;
		vector<string> last_name;
		string first_name_now;
		string last_name_now;

		for (auto&[y, n]: name) {
			if (y > year) break;

			if (!n.FirstName.empty() && (first_name.empty() || n.FirstName != first_name[first_name.size() - 1])) {
				first_name.push_back(n.FirstName);
				first_name_now = n.FirstName;
			}
			if (!n.LastName.empty() && (last_name.empty() || n.LastName != last_name[last_name.size() - 1])) {
				last_name.push_back(n.LastName);
				last_name_now = n.LastName;
			}
		}

		if (first_name.size() == 1 && first_name_now.empty()) {
			first_name_now = *first_name.begin();
		}

		if (last_name.size() == 1 && last_name_now.empty()) {
			last_name_now = *last_name.begin();
		}

		if (first_name_now.empty()) {
			return last_name_now + Concat(last_name, last_name_now) + " with unknown first name";
		}

		if (last_name_now.empty()) {
			return first_name_now + Concat(first_name, first_name_now) + " with unknown last name";
		}

		if (first_name.size() != 1 || *first_name.begin() != first_name_now)
			first_name_now += Concat(first_name, first_name_now);

		if (last_name.size() != 1 || *last_name.begin() != last_name_now)
			last_name_now += Concat(last_name, last_name_now);

		return first_name_now + " " + last_name_now;
	}

private:
	map<int, Name> name;
	int birthYear;

	string Concat(vector<string> v, const string &exclude) const {
		if (v.empty())
			return "";

		reverse(v.begin(), v.end());

		string res = " (";
		int i = 0;
		for (const auto &el: v) {
			if (el == exclude && i == 0)
				continue;
			res += el;
			res += ", ";
			i++;
		}

		if (res == " (")
			return "";

		res.erase(res.size() - 1);
		res[res.size() - 1] = ')';
		return res;
	}
};


#endif //WEEK3_PERSON_H
