#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

class ReadingManager {
public:
	void Read(int user_id, int page_count){
		if (user_to_page_.find(user_id) == user_to_page_.end()) {
			user_to_page_[user_id] = page_count;
			page_to_users_[page_count].insert(user_id);
		} else {
			int old_page_count = user_to_page_[user_id];
			user_to_page_[user_id] = page_count;
			page_to_users_[old_page_count].erase(user_id);
			page_to_users_[page_count].insert(user_id);

			if (page_to_users_[old_page_count].empty()) {
				page_to_users_.erase(old_page_count);
			}
		}
	}

	double Cheer(int user_id) const{
		const auto users_page_count = user_to_page_.count(user_id);
		if (users_page_count == 0)
			return 0;
		if (user_to_page_.size() == 1 && users_page_count > 0)
			return 1;

		const auto user_page = user_to_page_.at(user_id);
		auto rating = page_to_users_.find(user_page);

		if (rating == page_to_users_.begin())
			return 0;

		rating--;
		double res = 0;

		while (true) {
			res += rating->second.size();
			if (rating == page_to_users_.begin())
				break;
			rating--;
		}

		return res / (user_to_page_.size() - 1);
	}
private:
	map<int, int> user_to_page_;
	map<int, set<int>> page_to_users_;
};


class ReadingManager1 {
public:
	ReadingManager1()
			: user_page_counts_(MAX_USER_COUNT_ + 1, 0),
			  sorted_users_(),
			  user_positions_(MAX_USER_COUNT_ + 1, -1) {}

	void Read(int user_id, int page_count) {
		if (user_page_counts_[user_id] == 0) {
			AddUser(user_id);
		}
		user_page_counts_[user_id] = page_count;
		int& position = user_positions_[user_id];
		while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
			SwapUsers(position, position - 1);
		}
	}

	double Cheer(int user_id) const {
		if (user_page_counts_[user_id] == 0) {
			return 0;
		}
		const int user_count = GetUserCount();
		if (user_count == 1) {
			return 1;
		}
		const int page_count = user_page_counts_[user_id];
		int position = user_positions_[user_id];
		while (position < user_count &&
			   user_page_counts_[sorted_users_[position]] == page_count) {
			++position;
		}
		if (position == user_count) {
			return 0;
		}
		return (user_count - position) * 1.0 / (user_count - 1);
	}

private:
	static const int MAX_USER_COUNT_ = 100'000;

	vector<int> user_page_counts_;
	vector<int> sorted_users_;   // РѕС‚СЃРѕСЂС‚РёСЂРѕРІР°РЅС‹ РїРѕ СѓР±С‹РІР°РЅРёСЋ РєРѕР»РёС‡РµСЃС‚РІР° СЃС‚СЂР°РЅРёС†
	vector<int> user_positions_; // РїРѕР·РёС†РёРё РІ РІРµРєС‚РѕСЂРµ sorted_users_

	int GetUserCount() const {
		return sorted_users_.size();
	}
	void AddUser(int user_id) {
		sorted_users_.push_back(user_id);
		user_positions_[user_id] = sorted_users_.size() - 1;
	}
	void SwapUsers(int lhs_position, int rhs_position) {
		const int lhs_id = sorted_users_[lhs_position];
		const int rhs_id = sorted_users_[rhs_position];
		swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
		swap(user_positions_[lhs_id], user_positions_[rhs_id]);
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}