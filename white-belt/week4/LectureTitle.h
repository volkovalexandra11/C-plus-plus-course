#include <string>
using namespace std;

#ifndef WEEK4_LECTURETITLE_H
#define WEEK4_LECTURETITLE_H

struct Specialization {
	string value;

	explicit Specialization(const string &value) : value(value) {}
};

struct Course {
	string value;

	 explicit Course(const string &value) : value(value) {}
};

struct Week {
	string value;

	explicit Week(const string &value) : value(value) {}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	LectureTitle(const Specialization &specialization, const Course &course, const Week &week) {
		this->specialization = specialization.value;
		this->course = course.value;
		this->week = week.value;
	}
};

#endif //WEEK4_LECTURETITLE_H
