#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
    );
    return middle->age;
}

enum class Gender {
  FEMALE,
  MALE
};


struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

struct Answer {
  string message;
  int median_age;
};

ostream& operator<<(ostream& os, Answer a) {
    os << a.message << " = " << a.median_age;
    return os;
}

template<typename TFunc>
int GetMedianAgeByFunc(vector<Person> persons, TFunc func) {
    auto border = partition(persons.begin(), persons.end(), func);
    return ComputeMedianAge(persons.begin(), border);
}

Answer GetAllPeopleMedianAge(vector<Person> persons) {
    return {"Median age", ComputeMedianAge(persons.begin(), persons.end())};
}

Answer GetAllFemaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::FEMALE;
    };
    return {"Median age for females", GetMedianAgeByFunc(move(persons), p_function)};
}

Answer GetAllMaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::MALE;
    };
    return {"Median age for males", GetMedianAgeByFunc(move(persons), p_function)};
}

Answer GetAllEmployedFemaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::FEMALE && person.is_employed;
    };
    return {"Median age for employed females", GetMedianAgeByFunc(move(persons), p_function)};
}

Answer GetAllUnemployedFemaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::FEMALE && !(person.is_employed);
    };
    return {"Median age for unemployed females", GetMedianAgeByFunc(move(persons), p_function)};
}

Answer GetAllEmployedMaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::MALE && person.is_employed;
    };
    return {"Median age for employed males", GetMedianAgeByFunc(move(persons), p_function)};
}

Answer GetAllUnemployedMaleStat(vector<Person> persons) {
    auto p_function = [](Person person) {
      return person.gender == Gender::MALE && !(person.is_employed);
    };
    return {"Median age for unemployed males", GetMedianAgeByFunc(move(persons), p_function)};
}


void PrintStats(const vector<Person>& persons) {
    auto funcs = {GetAllPeopleMedianAge, GetAllFemaleStat, GetAllMaleStat, GetAllEmployedFemaleStat,
                  GetAllUnemployedFemaleStat, GetAllEmployedMaleStat, GetAllUnemployedMaleStat};

    for (auto func: funcs) {
        cout << func(persons) << endl;
    }
}
