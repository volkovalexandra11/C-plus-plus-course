#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>

using namespace std;


class Date {
public:
	Date();

	explicit Date(const string& input_date);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;

	Date& operator=(const Date& rhs);

	string GetDate(char separator = '-') const;

	time_t AsTimestamp() const;

	static int ComputeDaysDiff(const Date& date_to, const Date& date_from);

private:
	int year_;
	int month_;
	int day_;

	// Проверка формата
	void CheckFormat(const string& input);

	bool CheckNumber(stringstream& ss, int& number);

	// Проверка корректности даты
	void CheckData();
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);


Date::Date() {
	year_ = 0;
	month_ = 0;
	day_ = 0;
}

Date::Date(const string& input_date) {
	CheckFormat(input_date);
	CheckData();
}

int Date::GetYear() const { return year_; }

int Date::GetMonth() const { return month_; }

int Date::GetDay() const { return day_; }

Date& Date::operator=(const Date& rhs) {
	year_ = rhs.year_;
	month_ = rhs.month_;
	day_ = rhs.day_;
	return *this;
}

string Date::GetDate(char separator) const {
	stringstream so;
	so << setfill('0');
	if (year_ < 0) {
		so << '-';
	}
	so << setw(4) << abs(year_);
	so << separator;
	so << setw(2) << month_;
	so << separator;
	so << setw(2) << day_;
	return so.str();
}

time_t Date::AsTimestamp() const {
	tm t;
	t.tm_sec = 0;
	t.tm_min = 0;
	t.tm_hour = 0;
	t.tm_mday = day_;
	t.tm_mon = month_ - 1;
	t.tm_year = year_ - 1900;
	t.tm_isdst = 0;
	return mktime(&t);
}

int Date::ComputeDaysDiff(const Date& date_to, const Date& date_from) {
	const time_t timestamp_to = date_to.AsTimestamp();
	const time_t timestamp_from = date_from.AsTimestamp();
	static const int SECONDS_IN_DAY = 60 * 60 * 24;
	return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

void Date::CheckFormat(const string& input) {
	stringstream ss(input);
	int count_data = 3;
	int date_data[3] = {-1, -1, -1};
	year_ = date_data[0];
	month_ = date_data[1];
	day_ = date_data[2];

	if (!CheckNumber(ss, date_data[0])) {
		stringstream so;
		so << "Wrong date format: " << input;
		throw runtime_error(so.str());
	}

	char input_date_separator = '-';
	for (int i = 1; i < count_data; ++i) {
		if (ss.peek() != input_date_separator) {
			stringstream so;
			so << "Wrong date format: " << input;
			throw runtime_error(so.str());
		} else {
			ss.ignore(1);
			if (!CheckNumber(ss, date_data[i])) {
				stringstream so;
				so << "Wrong date format: " << input;
				throw runtime_error(so.str());
			}
		}
	}

	if (ss.rdbuf()->in_avail() != 0) {
		stringstream so;
		so << "Wrong date format: " << input;
		throw runtime_error(so.str());
	}
	year_ = date_data[0];
	month_ = date_data[1];
	day_ = date_data[2];
}

bool Date::CheckNumber(stringstream& ss, int& number) {
	char sign = '+';
	if (ss.peek() == '+' || ss.peek() == '-') {
		sign = ss.get();
	}
	if (ss.peek() >= '0' && ss.peek() <= '9') {
		ss >> number;
		if (sign == '-') {
			number = -number;
		}
	} else {
		return false;
	}
	return true;
}

void Date::CheckData() {
	if (month_ < 1 || month_ > 12) {
		stringstream ss;
		ss << "Month value is invalid: " << month_;
		throw runtime_error(ss.str());
	}

	if (day_ < 1 || day_ > 31) {
		stringstream ss;
		ss << "Day value is invalid: " << day_;
		throw runtime_error(ss.str());
	}
}

bool operator<(const Date& lhs, const Date& rhs) {
	int l_year = lhs.GetYear(), l_month = lhs.GetMonth(), l_day = lhs.GetDay();
	int r_year = rhs.GetYear(), r_month = rhs.GetMonth(), r_day = rhs.GetDay();
	return (tie(l_year, l_month, l_day) < tie(r_year, r_month, r_day));
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay());
}


class Budget {
public:
	Budget() = default;

	double ComputeTotalIncome(const Date& from, const Date& to);

	void SetIncome(const Date& from, const Date& to, double value);

	void PayTax(const Date& from, const Date& to);

	void Spend(const Date& from, const Date& to, double value);

private:
	struct Day {
		double ComputeIncome() const {
			return income - expended;
		}
		void PayTax(double tax) {
			income *= 1 - tax/100.0;
		}
		double income;
		double expended;
	};
	static const int SECONDS_IN_DAY = 60 * 60 * 24;
	unordered_map<time_t, double> income_for_day_;

};

class BudgetManager {
public:
	BudgetManager(istream& stream) : stream_(stream) {}

	vector<double> Process();

private:
	BudgetManager() = delete;

	Budget budget_;
	istream& stream_;
};


double Budget::ComputeTotalIncome(const Date& from, const Date& to) {
	auto time_from = from.AsTimestamp();
	auto time_to = to.AsTimestamp();

	double res = 0;
	for (auto curr_day = time_from; curr_day <= time_to; curr_day += SECONDS_IN_DAY) {
//		res += income_for_day_[curr_day].ComputeIncome();
		res += income_for_day_[curr_day];
	}
	return res;
}

void Budget::PayTax(const Date& from, const Date& to) {
	auto time_from = from.AsTimestamp();
	auto time_to = to.AsTimestamp();
	for (auto curr_day = time_from; curr_day <= time_to; curr_day += SECONDS_IN_DAY) {
		income_for_day_[curr_day] *= 0.87;
	}
}

void Budget::SetIncome(const Date& from, const Date& to, double value) {
	auto time_from = from.AsTimestamp();
	auto time_to = to.AsTimestamp();
	auto diff = Date::ComputeDaysDiff(to, from) + 1;
	double value_per_day = value / diff;
	for (auto curr_day = time_from; curr_day <= time_to; curr_day += SECONDS_IN_DAY) {
		income_for_day_[curr_day] += value_per_day;
	}
}

//void Budget::Spend(const Date& from, const Date& to, double value) {
//	auto time_from = from.AsTimestamp();
//	auto time_to = to.AsTimestamp();
//	auto diff = Date::ComputeDaysDiff(to, from) + 1;
//	double value_per_day = value / diff;
//	for (auto curr_day = time_from; curr_day <= time_to; curr_day += SECONDS_IN_DAY) {
//		income_for_day_[curr_day].expended += value_per_day;
//	}
//}

vector<double> BudgetManager::Process() {
	vector<double> result;
	size_t count = 0;
	stream_ >> count;
	for (size_t i = 0; i < count; ++i) {
		string command;
		stream_ >> command;
		if (command == "Earn") {
			string from, to;
			double value = 0;
			stream_ >> from >> to >> value;
			budget_.SetIncome(Date(from), Date(to), value);
		}
		if (command == "PayTax") {
			string from, to;
			double value;
			stream_ >> from >> to;
			budget_.PayTax(Date(from), Date(to));
		}
		if (command == "ComputeIncome") {
			string from, to;
			stream_ >> from >> to;
			result.push_back(budget_.ComputeTotalIncome(Date(from), Date(to)));
		}
//		if (command == "Spend") {
//			string from, to;
//			double value = 0;
//			stream_ >> from >> to >> value;
//			budget_.Spend(Date(from), Date(to), value);
//		}
	}
	return result;
}

void PrintResult(const vector<double>& result, ostream& stream) {
	for (const auto& elem : result) {
		stream << elem << endl;
	}
}


int main() {
	cout.precision(25);
	PrintResult(BudgetManager(cin).Process(), cout);
	return 0;
}