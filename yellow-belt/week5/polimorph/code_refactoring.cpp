#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name, const string& type) : Name(name), Type(type) {}

	virtual void Walk(const string& destination) {
		cout << Type << ": " << Name << " walks to: " << destination << endl;
	};

	void VisitPlaces(const vector<string>& places) {
		for (auto p: places) {
			Walk(p);
		}
	}

	string GetName() {
		return Name;
	}

	string GetType() const {
		return Type;
	}

protected:
	string Name;
	string Type;
};

class Student : public Person {
public:
	Student(const string& name, const string& favouriteSong) :
			Person(name, "Student"),
			FavouriteSong(favouriteSong) {}

	void Learn() {
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) override {
		cout << "Student: " << Name << " walks to: " << destination << endl;
		SingSong();
	}

	void SingSong() {
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	string FavouriteSong;
};


class Teacher : public Person {
public:
	Teacher(const string& name, const string& subject) :
			Person(name, "Teacher"), Subject(subject) {}

	void Teach() {
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}

private:
	string Subject;
};


class Policeman : public Person {
public:
	Policeman(const string& name) :
			Person(name, "Policeman") {}

	void Check(Person p) {
		cout << "Policeman: "
			 << Name << " checks "
			 << p.GetType() << ". " << p.GetType() << "'s Name is: " << p.GetName() << endl;
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
