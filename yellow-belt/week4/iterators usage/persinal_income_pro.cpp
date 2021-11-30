#include "personal_income_helpers.h"

static const Date START_DATE = Date::ParseFromString("1700-01-01");
static const Date END_DATE = Date::ParseFromString("2100-01-01");
static const size_t DAY_COUNT = Date::ComputeDaysDiff(END_DATE, START_DATE);

void SolveIncomePro() {
	vector<double> moneyByDay(DAY_COUNT, 0.0);
	vector<uint64_t> partial_sums(DAY_COUNT, 0.0);
	int earn_query_count, compute_query_count;
	cin >> earn_query_count;

	for (int i = 0; i < earn_query_count; i++) {
		string date;
		double sum;
		cin >> date >> sum;
		int fromBegin = Date::ComputeDaysDiff(
				Date::ParseFromString(date),
				START_DATE);
		moneyByDay[fromBegin] += sum;
	}

	partial_sum(moneyByDay.begin(), moneyByDay.end(), partial_sums.begin());

	cin >> compute_query_count;
	for (int i = 0; i < compute_query_count; i++) {
		string date_from, date_to;

		cin >> date_from >> date_to;

		int fromBegin = Date::ComputeDaysDiff(
				Date::ParseFromString(date_from),
				START_DATE);
		int fromEnd = Date::ComputeDaysDiff(
				Date::ParseFromString(date_to),
				START_DATE);

		cout << setprecision(25);
		if (fromBegin > 0) {
			cout << partial_sums[fromEnd] - partial_sums[fromBegin - 1];
		} else {
			cout << partial_sums[fromEnd];
		}
		cout << endl;
	}
}


