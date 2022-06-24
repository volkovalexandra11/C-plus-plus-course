#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t
#include <algorithm>

using namespace std;

// Реализуйте шаблон класса UniquePtr
template<typename T>
class UniquePtr {
private:
	T *raw_ptr;
public:
	UniquePtr() {
		raw_ptr = nullptr;
	};

	UniquePtr(T *ptr) : raw_ptr(ptr) {};

	UniquePtr(const UniquePtr&) = delete;

	UniquePtr(UniquePtr&& other) {
		raw_ptr = other.Release();
	};

	UniquePtr& operator=(const UniquePtr&) = delete;

	UniquePtr& operator=(nullptr_t) {
		Reset(nullptr);
		return *this;
	};

	UniquePtr& operator=(UniquePtr&& other) {
		delete raw_ptr;
		raw_ptr = other.Release();
		return *this;
	};

	~UniquePtr() {
		delete raw_ptr;
	};

	T& operator*() const {
		return *Get();
	};

	T *operator->() const {
		return Get();
	};

	T *Release() {
		auto tmp = raw_ptr;
		raw_ptr = nullptr;
		return tmp;
	};

	void Reset(T *ptr) {
		delete raw_ptr;
		raw_ptr = ptr;
	};

	void Swap(UniquePtr& other) {
		swap(raw_ptr, other.raw_ptr);
	};

	T *Get() const {
		return raw_ptr;
	};
};


struct Item {
	static int counter;
	int value;

	Item(int v = 0) : value(v) {
		++counter;
	}

	Item(const Item& other) : value(other.value) {
		++counter;
	}

	~Item() {
		--counter;
	}
};

int Item::counter = 0;


void TestLifetime() {
	Item::counter = 0;
	{
		UniquePtr<Item> ptr(new Item);
		ASSERT_EQUAL(Item::counter, 1);

		ptr.Reset(new Item);
		ASSERT_EQUAL(Item::counter, 1);
	}
	ASSERT_EQUAL(Item::counter, 0);

	{
		UniquePtr<Item> ptr(new Item);
		ASSERT_EQUAL(Item::counter, 1);

		auto rawPtr = ptr.Release();
		ASSERT_EQUAL(Item::counter, 1);

		delete rawPtr;
		ASSERT_EQUAL(Item::counter, 0);
	}
	ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
	UniquePtr<Item> ptr(new Item(42));
	ASSERT_EQUAL(ptr.Get()->value, 42);
	ASSERT_EQUAL((*ptr).value, 42);
	ASSERT_EQUAL(ptr->value, 42);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestLifetime);
	RUN_TEST(tr, TestGetters);
}
