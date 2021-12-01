#include <memory>
#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);

class INotifier {
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier{
public:
	SmsNotifier(const string &number) : number(number) {}

	void Notify(const string& message) override {
		SendSms(number, message);
	}
private:
	const string &number;
};

class EmailNotifier : public INotifier{
public:
	EmailNotifier(const string &number) : email(number) {}

	void Notify(const string& message) override {
		SendEmail(email, message);
	}
private:
	const string &email;
};