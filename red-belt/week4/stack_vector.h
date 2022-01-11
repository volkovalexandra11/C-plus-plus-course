#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) {
		if (a_size > N)
			throw invalid_argument("given size is bigger then N");
		size_ = a_size;
	};

	T& operator[](size_t index) {
		return data_[index];
	};

	const T& operator[](size_t index) const {
		return data_[index];
	};

	auto begin() {
		return data_.begin();
	};

	auto end() {
		return data_.begin() + size_;
	};

	auto begin() const {
		return data_.begin();
	};

	auto end() const {
		return data_.begin() + size_;
	};

	size_t Size() const {
		return size_;
	};

	size_t Capacity() const {
		return N;
	};

	void PushBack(const T& value) {
		if (size_ >= N)
			throw overflow_error("Cannot insert! Full vector used");
		else
			data_[size_++] = value;
	};

	T PopBack() {
		if (size_ <= 0)
			throw underflow_error("Cannot pop from empty vector");
		else {
			--size_;
			return data_[size_];
		}
	};

private:
	array<T, N> data_;
	size_t size_{};
};