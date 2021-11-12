#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#ifndef WEEK4_FUNCTION_H
#define WEEK4_FUNCTION_H

class FunctionPart {
public:
	FunctionPart(char operation, double value) : operation(operation), value(value) {}

	[[nodiscard]] double Apply(double source_value) const {
		switch (operation) {
			case '+':
				return source_value + value;
			case '-' :
				return source_value - value;
			case '*':
				return source_value * value;
			case '/':
				return source_value / value;
		}
		return 0;
	}

	void Invert() {
		operation = inverted_operations[operation];
	}

private:
	char operation;
	double value;
	map<char, char> inverted_operations = {{'+', '-'}, {'-', '+'},
										   {'*', '/'}, {'/', '*'}};
};

class Function {
public:
	void AddPart(const char& operation, double value) {
		parts.emplace_back(operation, value);
	}

	double Apply(double value) const {
		for (const auto& part : parts) {
			value = part.Apply(value);
		}
		return value;
	}

	void Invert() {
		for (auto& part : parts) {
			part.Invert();
		}

		reverse(parts.begin(), parts.end());
	}
private:
	vector<FunctionPart> parts;
};


#endif //WEEK4_FUNCTION_H
