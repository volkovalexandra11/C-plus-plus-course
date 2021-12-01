#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
      names[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
      surnames[year] = last_name;
  }

  string GetFullName(int year) {
      auto name_till_year = names.lower_bound(year);
      auto surname_till_year = surnames.lower_bound(year);
      if (name_till_year != names.end() && surname_till_year != surnames.end() &&
          name_till_year == names.begin() && surname_till_year == surnames.begin() &&
          name_till_year->first > year && surname_till_year->first > year) {
          return "Incognito";
      }

      string name;
      string surname;

      if (name_till_year != names.end() && name_till_year->first == year) {
          name = name_till_year->second;
      } else {
          if (name_till_year != names.begin()) {
              name_till_year--;
              name = name_till_year->second;
          }
      }

      if (surname_till_year != surnames.end() && surname_till_year->first == year) {
          surname = surname_till_year->second;
      } else {
          if (surname_till_year != surnames.begin()) {
              surname_till_year--;
              surname = surname_till_year->second;
          }
      }

      if (name.empty() && !surname.empty()) {
          stringstream ss;
          ss << surname << " with unknown first name";
          return ss.str();
      } else if (!name.empty() && surname.empty()) {
          stringstream ss;
          ss << name << " with unknown last name";
          return ss.str();
      }

      return name + " " + surname;

  }

private:
  map<int, string> names;
  map<int, string> surnames;
};




