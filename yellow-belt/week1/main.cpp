#include <map>
#include <string>
#include <iostream>

using namespace std;

template<typename TKey, typename TValue>
TValue& GetRefStrict(map<TKey, TValue>& m, const TKey& k) {
	if (m.find(k) == m.end()) {
		throw runtime_error("Key not found");
	}
	return m[k];
}


int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl;
}