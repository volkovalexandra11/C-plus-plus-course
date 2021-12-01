#include <iostream>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

const double PI = 3.14;

class Figure {
public:
	virtual double Area() = 0;

	virtual double Perimeter() = 0;

	virtual string Name() = 0;
};

class Triangle : public Figure {
public:
	Triangle(int a, int b, int c) : a(a), b(b), c(c) {}

	double Area() override {
		double p = Perimeter() / 2.0;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	double Perimeter() override {
		return a + b + c;
	}

	string Name() override {
		return "TRIANGLE";
	}

private:
	int a, b, c;
};

class Circle : public Figure {
public:
	Circle(int radius) : radius(radius) {}

	double Area() override {
		return PI * radius * radius;
	}

	double Perimeter() override {
		return 2 * PI * radius;
	}

	string Name() override {
		return "CIRCLE";
	}

private:
	int radius;
};

class Rect : public Figure {
public:
	Rect(int a, int b) : a(a), b(b) {}

	double Area() override {
		return a * b;
	}

	double Perimeter() override {
		return 2 * (a + b);
	}

	string Name() override {
		return "RECT";
	}

private:
	int a, b;
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
	string type;
	is >> type;
	if (type == "RECT") {
		int a = -5, b = -5;
		is >> a >> b;
		return make_shared<Rect>(a, b);
	} else if (type == "CIRCLE") {
		int r;
		is >> r;
		return make_shared<Circle>(r);
	} else {
		int a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
}

