#include <string>
#include <algorithm>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const {
		return front_.empty() && back_.empty();
	}

	size_t Size() const {
		return front_.size() + back_.size();
	}

	T& operator[](size_t index) {
		if (index >= front_.size()) {
			return back_[index - front_.size()];
		}
		return front_[front_.size() - index - 1];
	}

	const T& operator[](size_t index) const {
		if (index >= front_.size())
		{
			return back_[index - front_.size()];
		}

		return front_[front_.size() - index - 1];
	}

	const T& At(size_t index) const {
		if (index < 0 || index >= Size()) {
			throw out_of_range("Index must be non negative and less then deque size");
		}

		return (*this)[index];
	}

	T& At(size_t index) {
		if (index < 0 || index >= Size()) {
			throw out_of_range("Index must be non negative and less then deque size");
		}

		return (*this)[index];
	}

	T& Front() {
		return At(0);
	}

	const T& Front() const {
		return At(0);
	}

	T& Back() {
		return Empty() ? At(0) : At(Size() - 1);
	}

	const T& Back() const {
		return Empty() ? At(0) : At(Size() - 1);
	}

	void PushFront(T elem) {
		front_.push_back(elem);
	}

	void PushBack(T elem) {
		back_.push_back(elem);
	}

private:
	vector<T> front_;
	vector<T> back_;
};