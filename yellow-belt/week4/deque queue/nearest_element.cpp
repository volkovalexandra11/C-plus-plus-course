#include <set>


using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto border_range_greater = numbers.lower_bound(border);

    if (border_range_greater == numbers.begin())
        return border_range_greater;

    if (border_range_greater == numbers.end()) {
        return prev(numbers.end());
    }


    auto border_range_less = prev(border_range_greater);
    auto prev_el = *border_range_less;
    auto next_el = *border_range_greater;

    int distPrev = border - prev_el;
    int distNext = next_el - border;

    if (distNext == distPrev) return border_range_less;
    if (distPrev < distNext) return border_range_less;
    else return border_range_greater;
}