//#include <iostream>
//
//int main() {
//	std::cout << "Hello, World!" << std::endl;
//	return 0;
//}
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template<class T>
class ObjectPool {
public:
	T *Allocate() {
		if (deallocated_pull_.size() == 0) {
			T *new_obj = new T;
			allocated_.insert(new_obj);
			return new_obj;
		}
		T *active_obj_ = deallocated_pull_.front();
		deallocated_pull_.pop();
		allocated_.insert(active_obj_);
		return active_obj_;
	}

	T *TryAllocate() {
		if (deallocated_pull_.size() == 0) {
			return nullptr;
		}
		T *active_obj_ = deallocated_pull_.front();
		deallocated_pull_.pop();
		allocated_.insert(active_obj_);
		return active_obj_;
	}

	void Deallocate(T *object) {
		if (allocated_.find(object) == allocated_.end())
			throw invalid_argument("No such object allocated");
		deallocated_pull_.push(object);
//		auto it = remove_if(allocated_.begin(), allocated_.end(), [object](T* o) {return o == object;});
//		allocated_.erase(it, allocated_.end());
		allocated_.erase(object);
	}

	~ObjectPool() {
		for (auto x: allocated_) {
			delete x;
		}
		allocated_.clear();
		while (deallocated_pull_.size() != 0) {
			T* obj = deallocated_pull_.front();
			delete obj;
			deallocated_pull_.pop();
		}
	};

private:
	queue<T *> deallocated_pull_;
	set<T *> allocated_;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}