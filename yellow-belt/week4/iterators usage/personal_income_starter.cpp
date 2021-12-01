//#include "personal_income_helpers.h"
//
//void SolveIncomeStarter() {
//	vector<double> moneyByDay(DAY_COUNT, 0.0);
//	int query_count;
//	cin >> query_count;
//
//	for (int i = 0; i < query_count; i++) {
//		string q_type, date_from, date_to;
//
//		cin >> q_type >> date_from >> date_to;
//
//		int fromBegin = Date::ComputeDaysDiff(
//				Date::ParseFromString(date_from),
//				START_DATE);
//		int fromEnd = Date::ComputeDaysDiff(
//				Date::ParseFromString(date_to),
//				START_DATE);
//
//		if (q_type == "Earn") {
//			double sum;
//			cin >> sum;
//			int days_count = Date::ComputeDaysDiff(
//					Date::ParseFromString(date_to),
//					Date::ParseFromString(date_from)
//			);
//			sum /= (days_count + 1);
//			for (auto j = fromBegin; j < fromEnd + 1; j++) {
//				moneyByDay[j] += sum;
//			}
//		} else {
//			cout << setprecision(25);
//			cout << accumulate(moneyByDay.begin() + fromBegin,
//							   moneyByDay.begin() + fromEnd + 1,
//							   0.0);
//			cout << endl;
//		}
//	}
//}
