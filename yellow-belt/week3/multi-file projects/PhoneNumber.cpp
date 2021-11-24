#include <sstream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string &international_number) {
	stringstream ss(international_number);

	char first_symbol;
	ss >> first_symbol;
	if (first_symbol != '+')
		throw invalid_argument("Must start with +");

	int temp;

	if (!(ss >> temp)) {
		throw invalid_argument("Must have country code");
	}

	country_code_ = to_string(temp);

	if (ss.peek() != '-') {
		throw invalid_argument("Must be separated with -");
	}

	ss.ignore();


	if (!(ss >> temp)) {
		throw invalid_argument("Must have city code");
	}

	city_code_ = to_string(temp);

	if (ss.peek() != '-') {
		throw invalid_argument("Must be separated with -");
	}

	ss.ignore();

	if (!(ss >> local_number_)) {
		throw invalid_argument("Must have local number");
	}
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	stringstream ss;
	ss << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
	return ss.str();
}