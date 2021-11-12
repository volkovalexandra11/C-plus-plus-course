#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int sum() {
	int a, b;
	cin >> a >> b;
	cout << a + b;
	return 0;
}

int the_less_str() {
	string first, second, third;
	cin >> first >> second >> third;
	vector<string> strings = {first, second, third};
	sort(strings.begin(), strings.end());

	cout << strings[0];
	return 0;
}

int divide() {
	int a, b;
	cin >> a >> b;
	if (b == 0)
		cout << "Impossible";
	else
		cout << a / b;
	return 0;
}

int square_eq() {
	double a, b, c;
	cin >> a >> b >> c;

	if (a == 0) {
		if (b == 0)
			cout << "";
		else
			cout << -c / b;
	} else {
		double d = b * b - 4 * a * c;
		if (d < 0) {
			cout << "";
		} else if (d == 0) {
			cout << -b / (2 * a);
		} else {
			cout << (-b - sqrt(d)) / (2 * a) << " " << (-b + sqrt(d)) / (2 * a);
		}
	}

	return 0;
}

int calc_price() {
	double start_price, a, b, a_discount, b_discount;
	cin >> start_price >> a >> b >> a_discount >> b_discount;
	if (start_price <= a) {
		cout << start_price;
		return 0;
	}

	if (start_price > a && start_price <= b) {
		double discount = (1 - a_discount / 100.0);
		cout << start_price * (1 - a_discount / 100.0);
	}

	if (start_price > b) {
		auto discount = (1 - b_discount / 100.0);
		cout << start_price * discount;
	}

	return 0;
}

int even_numbers() {
	int a, b;
	cin >> a >> b;

	for (int i = a; i <= b; i++) {
		if (i % 2 == 0)
			cout << i << " ";
	}

	return 0;
}

void second_occurrence() {
	string str;
	cin >> str;
	int count = 0;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'f')
			count++;
		if (count == 2) {
			cout << i;
			return;
		}
	}

	if (count == 0)
		cout << -2;
	if (count == 1)
		cout << -1;
}

void gcd() {
	int a, b;
	cin >> a >> b;

	while (b != 0) {
		int temp = a;
		a = b;
		b = temp % b;
	}

	cout << a;
}

void to_binary() {
	int n;
	cin >> n;
	vector<int> numbers;

	while (n != 1) {
		numbers.push_back(n % 2);
		n /= 2;
	}

	numbers.push_back(1);
	reverse(numbers.begin(), numbers.end());

	for (auto x: numbers)
		cout << x;
}

int main() {
//	sum();
//	the_less_str();
//	square_eq();
//	divide();
//	calc_price();
//	even_numbers();
//	second_occurrence();
//	gcd();
	to_binary();
}
