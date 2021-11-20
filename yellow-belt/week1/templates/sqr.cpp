#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template<typename T>
T Sqr(T item);

template<typename TFirst, typename TSecond>
pair<TFirst, TSecond> Sqr(pair<TFirst, TSecond> p);

template<typename T>
vector<T> Sqr(vector<T> v);

template<typename TKey, typename TValue>
map<TKey, TValue> Sqr(map<TKey, TValue> m);


template<typename T>
T Sqr(T item) {
	return (item * item);
}

template<typename T>
vector<T> Sqr(vector<T> v) {
	vector<T> squared;
	for (const auto& x: v)
		squared.push_back(Sqr(x));
	return squared;
}

template<typename TKey, typename TValue>
map<TKey, TValue> Sqr(map<TKey, TValue> m) {
	map<TKey, TValue> squared;
	for (const auto& [key, value]: m)
		squared[key] = Sqr(value);

	return squared;
}

template<typename TFirst, typename TSecond>
pair<TFirst, TSecond> Sqr(pair<TFirst, TSecond> p) {
	return make_pair(Sqr(p.first), Sqr(p.second));
}


int main5() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};

	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}

