#include "stats.h"
#include <algorithm>
#include <array>
#include <string>

Stats::Stats() {
	for (size_t i = 0; i < 5; ++i) {
		methods_records_[http_methods_.at(i)] = 0;
		uri_records_[http_uri_.at(i)] = 0;
	}

	uri_records_[http_uri_.at(5)] = 0;
}

void Stats::AddMethod(string_view method) {
	const auto pos = find(http_methods_.begin(),
						  http_methods_.end(), method);

	string_view method_inserting;
	if (pos == http_methods_.end()) {
		method_inserting = *prev(http_methods_.end());
	} else {
		method_inserting = http_methods_.at(pos - http_methods_.begin());
	}

	++methods_records_[method_inserting];
}

void Stats::AddUri(string_view uri) {
	const auto pos = std::find(http_uri_.begin(),
							   http_uri_.end(), uri);

	string_view uri_inserting;
	if (pos == http_uri_.end()) {
		uri_inserting = *prev(http_uri_.end());
	} else {
		uri_inserting = http_uri_.at(pos - http_uri_.begin());
	}

	++uri_records_[uri_inserting];
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methods_records_;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_records_;
}

HttpRequest ParseRequest(string_view line) {
	array<string_view, 3> data;
	auto pos = line.find_first_not_of(' ');
	line.remove_prefix(pos);

	size_t i = 0;
	while (true) {
		size_t position = line.find(' ');
		data[i] = line.substr(0, position);
		if (position == string_view::npos) {
			break;
		} else {
			i++;
			line.remove_prefix(position + 1);
		}
	}
	return {data[0], data[1], data[2]};
}

//#include "stats.h"
//#include <algorithm>
//
//
//HttpRequest ParseRequest(std::string_view line)
//{
//	auto pos = line.find_first_not_of(' ');
//	line.remove_prefix(pos);
//
//	pos = line.find(' ');
//	const std::string_view method = std::string_view(line.data(), pos);
//	line.remove_prefix(pos + 1);
//
//	pos = line.find(' ');
//	const std::string_view uri = std::string_view(line.data(), pos);
//	line.remove_prefix(pos + 1);
//
//	const std::string_view protocol = std::string_view(line.data());
//
//	return { method, uri, protocol };
//}
//
//
//Stats::Stats()
//{
//	for (size_t i = 0; i < 5; ++i)
//	{
//		methods_to_count_[methods_.at(i)] = 0;
//		uris_to_count_[uris_.at(i)] = 0;
//	}
//
//	uris_to_count_[uris_.at(5)] = 0;
//}
//
//
//void Stats::AddMethod(std::string_view method)
//{
//	const auto find_iter = std::find(methods_.begin(),
//									 methods_.end(), method);
//
//	if (find_iter == methods_.end())
//	{
//		++methods_to_count_[*std::prev(methods_.end())];
//	}
//	else
//	{
//		++methods_to_count_[methods_.at(find_iter - methods_.begin())];
//	}
//}
//
//
//void Stats::AddUri(std::string_view uri)
//{
//	const auto find_iter = std::find(uris_.begin(),
//									 uris_.end(), uri);
//
//	if (find_iter == uris_.end())
//	{
//		++uris_to_count_[*std::prev(uris_.end())];
//	}
//	else
//	{
//		++uris_to_count_[uris_.at(find_iter - uris_.begin())];
//	}
//}
//
//
//const std::map<std::string_view, int>& Stats::GetMethodStats() const
//{
//	return methods_to_count_;
//}
//
//
//const std::map<std::string_view, int>& Stats::GetUriStats() const
//{
//	return uris_to_count_;
//}