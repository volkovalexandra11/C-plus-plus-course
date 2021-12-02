#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Person {
public:
	Person(const string& name, const string& type) : Name(name), Type(type) {}

	virtual void Walk(const string& destination) {
		cout << Type << ": " << Name << " walks to: " << destination << endl;
	};

	void VisitPlaces(const vector<string>& places) {
		for (const auto& p: places) {
			Walk(p);
		}
	}

	string GetName() const {
		return Name;
	}

	string GetType() const {
		return Type;
	}

protected:
	const string Name;

	void Log(vector<string>& strings) {
		//можно было бы дальше убирать дублирование, но как-то так себе,
		// потому что ну там шило на мыло меняется
		auto str = FormatStr(strings);
		cout << Type << ": " << Name << str;
	}

private:
	const string Type;

	static string FormatStr(const vector<string>& parts) {
		ostringstream os;
		for (const auto& p: parts) {
			os << p;
		}
		return os.str();
	}
};

class Student : public Person {
public:
	Student(const string& name, const string& favouriteSong) :
			Person(name, "Student"),
			FavouriteSong(favouriteSong) {}

	void Learn() {
		vector<string> strings = {" learns"};
		Log(strings);
	}

	void Walk(const string& destination) override {
		vector<string> strings = {" walks to: ", destination};
		Log(strings);
		SingSong();
	}

	void SingSong() {
		vector<string> strings = {" sings a song: ", FavouriteSong};
		Log(strings);
	}

private:
	const string FavouriteSong;
};


class Teacher : public Person {
public:
	Teacher(const string& name, const string& subject) :
			Person(name, "Teacher"), Subject(subject) {}

	void Teach() {
		vector<string> strings = {" teaches: ", Subject};
		Log(strings);
	}

private:
	const string Subject;
};


class Policeman : public Person {
public:
	Policeman(const string& name) :
			Person(name, "Policeman") {}

	void Check(const Person& p) {
		vector<string> strings = {
				" checks ", p.GetType(), ". ",
				p.GetType(), "'s Name is: ", p.GetName()
		};
		Log(strings);
	}
};


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	t.VisitPlaces({"Moscow", "London"});
	p.Check(s);
	s.VisitPlaces({"Moscow", "London"});
	return 0;
}
