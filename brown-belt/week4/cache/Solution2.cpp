//#include "Common.h"
#include "Common2.h"
#include <list>
#include <unordered_map>
#include <mutex>


using namespace std;

class LruCache : public ICache {
public:
	LruCache(
			shared_ptr<IBooksUnpacker> books_unpacker,
			const Settings& settings
	) {
		settings_ = {settings, settings.max_memory};
		books_unpacker_ = move(books_unpacker);
	}

	BookPtr GetBook(const string& book_name) override {
		// Если книга уже есть в кэше
		{
			lock_guard<mutex> a(mutex_);
			if (cache_elements_.count(book_name)) {
				auto point_to_cache = cache_elements_.at(book_name);
				cache_.splice(cache_.begin(), cache_, point_to_cache);
				return cache_.front().book;
			}
		}
		unique_ptr<IBook> book;
		size_t book_size;
		{
			lock_guard<mutex> a(mutex_);
			book = books_unpacker_->UnpackBook(book_name);
			book_size = book->GetContent().size();
		}
		// Если книга больше размера кэша

		if (book_size > settings_.default_settings_.max_memory) {
			return move(book);
		}
		// Если размер книги больше свободного места
		if (book_size > settings_.free_memory_) {
			ClearCache(book_size);
		}
		shared_ptr<IBook> result;
		{
			lock_guard<mutex> a(mutex_);
			cache_.push_front({book_name, move(book)});
			cache_elements_[book_name] = cache_.begin();
			settings_.free_memory_ -= book_size;
			result = cache_.front().book;
		}
		return result;
	}

private:

	shared_ptr<IBooksUnpacker> books_unpacker_;

	struct SettingsState {
		Settings default_settings_;
		size_t free_memory_;
	} settings_;
	struct CacheItem {
		string name;
		shared_ptr<IBook> book;
	};

	unordered_map<string, list<CacheItem>::iterator> cache_elements_;
	list<CacheItem> cache_;
	mutex mutex_;

	void ClearCache(size_t need_free_space) {
		while (settings_.free_memory_ < need_free_space) {
			lock_guard<mutex> a(mutex_);
			auto deleted = cache_.back();
			cache_.pop_back();
			settings_.free_memory_ += deleted.book->GetContent().size();
			cache_elements_.erase(deleted.name);
		}
	}
};


unique_ptr<ICache> MakeCache(
		shared_ptr<IBooksUnpacker> books_unpacker,
		const ICache::Settings& settings
) {
	return make_unique<LruCache>(books_unpacker, settings);
}
