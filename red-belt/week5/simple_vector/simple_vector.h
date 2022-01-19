#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

template<typename T>
class SimpleVector {
public:
	SimpleVector() {
		data_ = nullptr;
		end_ = nullptr;
		capacity_ = 0;
		size_ = 0;
	};

	explicit SimpleVector(size_t size) {
		data_ = new T[size];
		end_ = data_ + size;
		capacity_ = size;
		size_ = size;
	}

	~SimpleVector() {
		delete[] data_;
	}

	T& operator[](size_t index) {
		return data_[index];
	}

	T *begin() {
		return data_;
	};

	T *end() {
		return end_;
	};

	const T *begin() const {
		return data_;
	};

	const T *end() const {
		return end_;
	};

	size_t Size() const {
		return size_;
	};

	size_t Capacity() const {
		return capacity_;
	};

	void PushBack(const T& value) {
		if (!capacity_) {
			Resize(1);
		}
		if (size_ == capacity_) {
			Resize(capacity_ * 2);
		}
		*end_ = value;
		size_++;
		end_++;
	};

	SimpleVector<T>& operator=(const SimpleVector<T>& other) {
		delete[] data_;

		data_ = new T[other.size_];
		size_ = other.size_;
		capacity_ = other.capacity_;

		copy(other.begin(), other.end(), begin());

		end_ = data_ + other.size_;
		return *this;
	}

//	SimpleVector<T>& operator=(SimpleVector&& other) {
//		data_ = other.data_;
//		capacity_ = other.Capacity();
//		size_ = other.Size();
//
//		other.data_ = nullptr;
//		other.size_ = other.capacity_ = 0;
//
//		return *this;
//	}

	SimpleVector(const SimpleVector& other) : data_(new T[other.capacity_]),
											  size_(other.size_), capacity_(other.capacity_) {
		copy(other.begin(), other.end(), begin());
	}


//	SimpleVector(SimpleVector&& other) : data_(other.data_),
//										 size_(other.size_), capacity_(other.capacity_) {
//		other.data_ = nullptr;
//		other.size_ = other.capacity_ = 0;
//	}

//	SimpleVector(const SimpleVector& other) : data_(new T[other.capacity_]),
//											  size_(other.size_), capacity_(other.capacity_) {
//		copy(other.begin(), other.end(), begin());
//	}

private:
	T *data_;
	T *end_;
	size_t capacity_;
	size_t size_;

	void Resize(size_t new_size) {
		T *temp_data = new T[new_size];
		size_t old_size = size_;
		capacity_ = new_size;
		for (size_t i = 0; i < size_; ++i) {
			temp_data[i] = data_[i];
		}
		delete[] data_;
		data_ = temp_data;
		end_ = data_ + size_;
	}
};