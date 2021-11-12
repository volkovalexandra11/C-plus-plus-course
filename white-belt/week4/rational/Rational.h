#include <numeric>
#include <iostream>
#include <map>

using namespace std;


using namespace std;

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator == 0) {
			throw invalid_argument("Zero division");
		}

		if (numerator <= 0 && denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}

		if (numerator >= 0 && denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}

		this->numerator = numerator;
		this->denominator = denominator;
		reduce();
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

	void Invert() {
		swap(numerator, denominator);
	}

private:
	int numerator;
	int denominator;

	void reduce() {
		int divisor = gcd(denominator, numerator);
		numerator /= divisor;
		denominator /= divisor;
	}
};


Rational operator+(const Rational &first, const Rational &other) {
	int new_den = first.Denominator() * other.Denominator();
	int first_a = first.Numerator() * other.Denominator();
	int second = other.Numerator() * first.Denominator();
	return {first_a + second, new_den};
}

Rational operator-(const Rational &first, const Rational &other) {
	int new_den = first.Denominator() * other.Denominator();
	int first_a = first.Numerator() * other.Denominator();
	int second = other.Numerator() * first.Denominator();
	return {first_a - second, new_den};
}

Rational operator*(const Rational &first, const Rational &other) {
	int new_den = first.Denominator() * other.Denominator();
	int new_num = first.Numerator() * other.Numerator();
	return {new_num, new_den};
}

Rational operator/(const Rational &first, Rational other) {
	if (other.Numerator() == 0) {
		throw domain_error("Zero division");
	}
	other.Invert();
	return first * other;
}

bool operator==(const Rational &first, const Rational &other) {
	return first.Numerator() == other.Numerator() && first.Denominator() == other.Denominator();
}

bool operator<(const Rational &first, const Rational &second) {
	auto first_num = first.Numerator() * second.Denominator();
	auto second_num = second.Numerator() * first.Denominator();
	return first_num < second_num;
}

istream &operator>>(istream &stream, Rational &rational) {
	int num, den;
	char del;

	if (!stream)
		return stream;

	if (!(stream >> num)) return stream;
	stream >> del;
	if (!(stream >> den)) return stream;

	if (del != '/')
		return stream;

	rational = {num, den};

	return stream;
}

ostream &operator<<(ostream &stream, const Rational &rational) {
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

Rational Apply(const char &operation, const Rational &first, const Rational &second) {
	switch (operation) {
		case '+':
			return first + second;
		case '-':
			return first - second;
		case '*':
			return first * second;
		case '/':
			return first / second;
		default:
			throw invalid_argument("Unknown operation");
	}
}

void CalcRational() {
	Rational r1, r2;
	char operation;

	try {
		cin >> r1 >> operation >> r2;
		cout << Apply(operation, r1, r2);
	} catch (invalid_argument& e) {
		cout << "Invalid argument";
	} catch (domain_error& e) {
		cout << "Division by zero";
	}
}

int main() {
	CalcRational();
}