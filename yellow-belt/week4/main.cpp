#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if ((range_end - range_begin) < 2)
        return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    int middle = (elements.end() - elements.begin()) / 2;
    auto middle_it = elements.begin() + middle;
    MergeSort(elements.begin(), middle_it);
    MergeSort(middle_it, elements.end());

    merge(range_begin, middle_it, middle_it , range_end, elements.begin());
}


int main() {
    cout << "Hello world!" << endl;
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
