#include <algorithm>
#include <string>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    return equal_range(
      range_begin,
      range_end,
      string(1, prefix),
      [](string l, string r) {
        if (l.empty() || r.empty()) {
            return true;
        }
        return l[0] < r[0];
      }
    );
}

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto pref_len = prefix.size();
    return equal_range(
      range_begin, range_end, prefix,
      [pref_len](string l, string r) {
        return l.compare(0, pref_len, r, 0, pref_len) < 0;
      }
    );
}