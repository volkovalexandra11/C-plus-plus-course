#include "test_runner.h"
#include "deque.cpp"

#include <iostream>

using namespace std;

void TestDeque() {
	Deque<int> d;
	ASSERT_EQUAL(d.Empty(), true)

	d.PushBack(1);
	ASSERT_EQUAL(d.Front(), 1);
	ASSERT_EQUAL(d.Back(), 1);

	d.PushBack(2);
	ASSERT_EQUAL(d.Front(), 1);
	ASSERT_EQUAL(d.Back(), 2);

	d.PushFront(3);

	ASSERT_EQUAL(d.Front(), 3);
	ASSERT_EQUAL(d.Back(), 2);
	ASSERT_EQUAL(d.Size(), 3);
}

int main() {
	cout << "Hello, world!" << endl;
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;

	Deque<int> my_deque{};
	my_deque.PushFront(1);
	my_deque.PushFront(2);
	my_deque.PushBack(1);
	my_deque.PushFront(4);
	my_deque.PushBack(2);
	my_deque.PushBack(3);
	for (size_t i = 0; i < my_deque.Size(); ++i) {
		printf("%d ", my_deque.At(i)) ;
	}
}
