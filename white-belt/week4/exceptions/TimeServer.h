#include <iostream>
#include <exception>
#include <string>
using namespace std;

#ifndef WEEK4_TIMESERVER_H
#define WEEK4_TIMESERVER_H


string AskTimeServer() {}

class TimeServer {
public:
	string GetCurrentTime() {
		try {
			last_fetched_time = AskTimeServer();
			return last_fetched_time;
		} catch (system_error& e) {
			return last_fetched_time;
		}
	}

private:
	string last_fetched_time = "00:00:00";
};


#endif //WEEK4_TIMESERVER_H
