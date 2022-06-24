#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

vector<string> ReadFullDomains(istream& stream) {
	int count;
	stream >> count;
	vector<string> res(count);
	for (auto& s: res) {
		stream >> s;
	}
	return res;
}

class DomainFilter {
public:
	explicit DomainFilter(const vector<string>& raw_domains) {
		ParseFullDomains(raw_domains);
	}

	// true - можно пропустить
	// false - пропустить нельзя
	bool FilterDomain(const string& domain) {
		auto subdomains = SplitBy(domain);

		auto dom_first = subdomains.back();
		auto *curr_line = &bad_domains_.data_;
		if (!curr_line->count(dom_first)) {
			return true;
		}
		curr_line = &curr_line->at(dom_first)->data_;
		if (curr_line->count("")) {
			return false;
		}
		subdomains.pop_back();
		for (auto i = subdomains.rbegin(); i != subdomains.rend(); ++i) {
			if (!curr_line->count(*i)) {
				return true;
			}
			auto b = *i;
			curr_line = &curr_line->at(*i)->data_;
			if (curr_line->count("")) {
				return false;
			}
		}
		return true;
	}

private:
	struct Item {
		unordered_map<string, shared_ptr<Item>> data_;
	};
	Item bad_domains_;

	void ParseFullDomains(const vector<string>& raw_domains) {
		for (const auto& domain: raw_domains) {
			auto subdomains = SplitBy(domain);
			reverse(subdomains.begin(), subdomains.end());
			auto *curr_line = &bad_domains_.data_;
			for (auto& dom: subdomains) {
				curr_line->insert({dom, move(make_shared<Item>())});
				curr_line = &curr_line->at(dom)->data_;
			}
			curr_line->insert({"", make_shared<Item>()});
		}
	}

	static vector<string> SplitBy(const string& s, char separator = '.') {
		vector<string> result;
		auto curr = s.begin();
		while (curr != s.end()) {
			auto space = find(curr, s.end(), separator);
			result.emplace_back(string(curr, space));
			if (space != s.end()) curr = (space + 1);
			else curr = s.end();
		}
		return result;
	}
};

int main() {
	auto bad_domains = ReadFullDomains(cin);
	auto domains = ReadFullDomains(cin);
	DomainFilter filter(bad_domains);
	for (const auto& d: domains) {
		auto res = filter.FilterDomain(d);
		if (res) {
			cout << "Good" << endl;
		} else {
			cout << "Bad" << endl;
		}
	}
	return 0;
}