#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

struct Record {
//	Record()= default;
	int64_t time = 0;
	string name_hotel;
	int32_t client_id = 0;
	int32_t rooms_count = 0;
};

class Hotel {
public:
	Hotel() : clients_(), rooms_(0) {}

	void BookClient(int32_t client_id, int32_t rooms) {
		rooms_ += rooms;
		clients_[client_id].push_back(rooms);
	}

	bool Remove(int32_t client_id) {
		auto find = clients_.find(client_id);
		if (find == clients_.end()) {
			return false;
		}
		if (!find->second.empty()) {
			rooms_ -= find->second.front();
			find->second.pop_front();
		}
		if (find->second.empty()) {
			clients_.erase(find);
		}
		return true;
	}

	int32_t GetClients() const {
		return clients_.size();
	}

	int32_t GetRooms() const {
		return rooms_;
	}

private:
	unordered_map<int32_t, list<int32_t>> clients_;
	int32_t rooms_;
};

class BookingManager {
public:
	BookingManager() = default;
	void Book(int64_t time, const std::string& hotel_name, int32_t client_id, int32_t room_count) {
		Record r = {time, hotel_name, client_id, room_count};
		records_.push_back(r);
		hotels_[hotel_name].BookClient(client_id, room_count);
		UpdateRecords();
	}

	int32_t Clients(const std::string& hotel_name) const {
		auto find = hotels_.find(hotel_name);
		return (find == hotels_.end()) ? 0 : find->second.GetClients();
	}

	int32_t Rooms(const std::string& hotel_name) {
		auto find = hotels_.find(hotel_name);
		return (find == hotels_.end()) ? 0 : find->second.GetRooms();
	}

private:
	static const int PERIOD_TIME = 86400;
	list<Record> records_;
	unordered_map<std::string, Hotel> hotels_;

	void UpdateRecords() {
		for (auto record = records_.begin(); record != records_.end();) {
			if (!CheckRecordTime(record->time)) {
				auto for_delete = records_.front();
				hotels_[for_delete.name_hotel].Remove(for_delete.client_id);
				record = records_.erase(records_.begin());
			}
			else {
				break;
			}
		}
	}

	bool CheckRecordTime(int32_t time) {
		int32_t current_time = records_.back().time;
		return ((current_time - PERIOD_TIME) < time) && (time <= current_time);
	}

};

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	BookingManager manager;

	int query_count;
	cin >> query_count;

	for (uint32_t query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		if (query_type == "BOOK") {
			int64_t time, client_id, room_count;
			string hotel_name;
			cin >> time >> hotel_name >> client_id >> room_count;
			manager.Book(time, hotel_name, client_id, room_count);
		} else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << manager.Clients(hotel_name) << "\n";
		}
		else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			cout << manager.Rooms(hotel_name) << "\n";
		}
	}
	return 0;
}