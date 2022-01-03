#include "test_runner.h"
#include <sstream>
#include <string>

using namespace std;

class Logger {
public:
	explicit Logger(ostream& output_stream) : os(output_stream) {
	}

	void SetLogLine(bool value) { log_line = value; }

	void SetLogFile(bool value) { log_file = value; }

	void Log(const string& message);

	bool IsLogLine() const {
		return log_line;
	}

	bool IsLogFile() const {
		return log_file;
	}

private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
};

void Logger::Log(const string& message) {
	os << message;
}


#define LOG(logger, message) { 				  			\
    ostringstream os;                          			\
    if ((logger).IsLogFile() && (logger).IsLogLine()) { \
        os << __FILE__ << ":" << __LINE__ << " "; 		\
    } else if ((logger).IsLogLine()) { 					\
        os << "Line " << __LINE__ << " "; 				\
    } else if ((logger).IsLogFile()) {					\
        os << __FILE__ << " ";          				\
	}													\
    os << (message) << endl;      						\
    (logger).Log(os.str());								\
}

void TestLog() {
#line 1 "logger.cpp"

	ostringstream logs;
	Logger l(logs);
	LOG(l, "hello");

	l.SetLogFile(true);
	LOG(l, "hello");

	l.SetLogLine(true);
	LOG(l, "hello");

	l.SetLogFile(false);
	LOG(l, "hello");

	string expected = "hello\n";
	expected += "logger.cpp hello\n";
	expected += "logger.cpp:10 hello\n";
	expected += "Line 13 hello\n";
	ASSERT_EQUAL(logs.str(), expected);
}

int main2() {
	TestRunner tr;
	RUN_TEST(tr, TestLog);
}