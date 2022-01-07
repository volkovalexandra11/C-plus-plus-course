#include <iostream>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct Event{
	int64_t time;
	string hotel;
	int client_id;
	int rooms_count;
};

class HotelManager {
public:
	HotelManager() : current_time_(0) {}

	void Book(int64_t time, const string& hotel_name, int client_id, int room_count) {
		current_time_ = time;

		if (events_.empty()) {
			insert(time, hotel_name, client_id, room_count);
		} else {
			delete_(time, hotel_name, client_id, room_count);
			insert(time, hotel_name, client_id, room_count);
		}
	}

	int GetClients(const string& hotel_name) {
		if (hotel_to_clients_.find(hotel_name) == hotel_to_clients_.end())
			return 0;
		return hotel_to_clients_[hotel_name].size();
	}

	int GetRooms(const string& hotel_name) {
		if (hotel_to_rooms_.find(hotel_name) == hotel_to_rooms_.end())
			return 0;
		return hotel_to_rooms_[hotel_name];
	}

private:
	int64_t current_time_;
	queue<Event> events_;

	map<string, set<int>> hotel_to_clients_;
	map<string, int> hotel_to_rooms_;

	int64_t day_as_seconds_ = 86400;

	void insert(int64_t time, const string& hotel_name, int client_id, int room_count) {
		events_.push({time, hotel_name, client_id, room_count});
		hotel_to_clients_[hotel_name].insert(client_id);
		hotel_to_rooms_[hotel_name] += room_count;
	}

	void delete_(int64_t time, const string& hotel_name, int client_id, int room_count) {
		auto event = events_.front();
		while (true) {
			if (event.time > (current_time_ - day_as_seconds_))
				break;

			hotel_to_clients_[event.hotel].erase(event.client_id);
			hotel_to_rooms_[event.hotel] -= event.rooms_count;
			events_.pop();

			if (events_.empty())
				break;

			event = events_.front();
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelManager hm;
	int query_count;
	cin >> query_count;

	for (int i = 0; i < query_count; ++i) {
		string query;
		cin >> query;

		if (query == "BOOK") {
			int64_t time;
			int client_id, room_count;
			string hotel_name;

			cin >> time >> hotel_name >> client_id >> room_count;
			hm.Book(time, hotel_name, client_id, room_count);
		} else if (query == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << hm.GetClients(hotel_name) << "\n";
		} else {
			string hotel_name;
			cin >> hotel_name;
			cout << hm.GetRooms(hotel_name) << "\n";
		}
	}
}
