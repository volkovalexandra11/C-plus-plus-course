#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>
#include <string>

using namespace std;

class Stats {
public:
	Stats();

	void AddMethod(string_view method);

	void AddUri(string_view uri);

	const map<string_view, int>& GetMethodStats() const;

	const map<string_view, int>& GetUriStats() const;

private:
	inline const static array<string, 5> http_methods_ = {"GET",
														  "POST",
														  "PUT",
														  "DELETE",
														  "UNKNOWN"
	};
	inline const static array<string, 6> http_uri_ = {"/",
													  "/order",
													  "/product",
													  "/basket",
													  "/help",
													  "unknown"
	};

	map<string_view, int> methods_records_;
	map<string_view, int> uri_records_;
};

void skip_trailing_whitespaces(string_view& line);

HttpRequest ParseRequest(string_view line);


//#pragma once
//#include "http_request.h"
//#include <map>
//#include <array>
//
//
//class Stats
//{
//public:
//	Stats();
//
//	void AddMethod(std::string_view method);
//
//	void AddUri(std::string_view uri);
//
//	const std::map<std::string_view, int>& GetMethodStats() const;
//
//	const std::map<std::string_view, int>& GetUriStats() const;
//
//private:
//	std::map<std::string_view, int> methods_to_count_;
//	std::map<std::string_view, int> uris_to_count_;
//
//	inline const static std::array<std::string, 5> methods_ = { "GET", "POST",
//																"PUT", "DELETE", "UNKNOWN" };
//	inline const static std::array<std::string, 6> uris_ = { "/", "/order",
//															 "/product", "/basket", "/help", "unknown" };
//};
//
//
//HttpRequest ParseRequest(std::string_view line);