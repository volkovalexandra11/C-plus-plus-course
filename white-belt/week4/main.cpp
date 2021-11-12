#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <sstream>
#include "rational/Rational.h"
#include "exception/exceptions.cpp"

using namespace std;

void PrintFile(const string &path) {
	ifstream input(path);

	if (input.is_open()) {
		string line;
		while (getline(input, line))
			cout << line << endl;
	}
}

void PrintFileToFile(const string &path_in, const string path_out) {
	ifstream input(path_in);
	ofstream output(path_out, ios::trunc);

	if (input) {
		string line;
		while (getline(input, line))
			output << line << endl;
	}
}

void PrintWithPrecision(const string &path) {
	ifstream input(path);
	cout << fixed << setprecision(3);
	if (input) {
		double line;
		while (input >> line) {
			cout << line << endl;
		}
	}
}

void PrintTable(const string &path) {
	ifstream input(path);
	int width, height;
	input >> height >> width;
	input.ignore(1);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			string cell;
			if (j == width - 1) {
				getline(input, cell);
				cout << setw(10);
				cout << cell;
			} else {
				getline(input, cell, ',');
				cout << setw(10);
				cout << cell << " ";
			}
		}
		if (i != height - 1)
			cout << endl;
	}
}

struct Student {
	string name;
	string surname;
	int day;
	int month;
	int year;
};

vector<Student> ReadAndSaveStudents() {
	int n;
	cin >> n;
	vector<Student> students(n);

	for (int i = 0; i < n; i++) {
		string name, surname;
		int day, month, year;
		cin >> name >> surname >> day >> month >> year;
		students[i] = {name, surname, day, month, year};
	}

	return students;

}

void ProcessStudents() {
	auto students = ReadAndSaveStudents();
	auto students_number = students.size();
	int query_count;
	cin >> query_count;

	for (int i = 0; i < query_count; i++) {
		string query;
		int number;
		cin >> query >> number;
		if (number > students_number || number < 1) {
			cout << "bad request" << endl;
			continue;
		}

		auto student = students[number - 1];

		if (query == "name") {
			cout << student.name << " " << student.surname << endl;
		} else if (query == "date") {
			cout << student.day << "." << student.month << "." << student.year << endl;
		} else {
			cout << "bad request" << endl;
		}
	}

}

//int main() {
////	PrintFile("input.txt");
////	PrintFileToFile("input.txt", "output.txt");
////	PrintWithPrecision("input.txt");
////	PrintTable("input.txt");
//	ProcessStudents();
//	return 0;
//}

//int main() {
//	{
//		Rational r1(4, 6);
//		Rational r2(2, 3);
//		bool equal = r1 == r2;
//		if (!equal) {
//			cout << "4/6 != 2/3" << endl;
//			return 1;
//		}
//	}
//
//	{
//		Rational a(2, 3);
//		Rational b(4, 3);
//		Rational c = a + b;
//		bool equal = c == Rational(2, 1);
//		if (!equal) {
//			cout << "2/3 + 4/3 != 2" << endl;
//			return 2;
//		}
//	}
//
//	{
//		Rational a(5, 7);
//		Rational b(2, 9);
//		Rational c = a - b;
//		bool equal = c == Rational(31, 63);
//		if (!equal) {
//			cout << "5/7 - 2/9 != 31/63" << endl;
//			return 3;
//		}
//	}
//
//	{
//		Rational a(25, 7);
//		Rational b(25, 7);
//		Rational c = a - b;
//		bool equal = c == Rational(0, 1);
//		if (!equal) {
//			cout << "25/7 - 25/7 != 0" << endl;
//			return 4;
//		}
//	}
//
//	{
//		Rational a(5, 7);
//		Rational b(2, 9);
//		Rational c = a - b;
//		bool equal = c == Rational(31, 63);
//		if (!equal) {
//			cout << "5/7 - 2/9 != 31/63" << endl;
//			return 3;
//		}
//	}
//
//	cout << "OK" << endl;
//	return 0;
//}

int main() {
	try {
		EnsureEqual("C++ White", "C++ White");
		EnsureEqual("C++ White", "C++ Yellow");
	} catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	return 0;
}