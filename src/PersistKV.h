#ifndef __PERSIST_KV__
#define __PERSIST_KV__

#include <optional>
#include <unordered_map>

/*
 * Requirements for template parameter K (key):
 *  - must be hashable (std::hash<K> specification must exist)
 *  - must be equality comparable (operator== must be defined)
 *
 * Requirements for template parameter V (value):
 *  - must be copyable/movable 
 */
template <typename K, typename V>
class PersistKV {
public:
	PersistKV() {
	}

	virtual ~PersistKV() {
	}

	bool put(const K& key, const V& val) {
		memory_[key] = val;
		return true;
	}

	std::optional<V> get(const K& key) const {
		auto iterator = memory_.find(key);
		if (iterator != memory_.end()) {
			return iterator->second;
		} else {
			return {};
		}
	}

	bool del(const K& key) {
		return memory_.erase(key) > 0;
	}

	bool clear() {
		memory_.clear();
		return true;
	}

	size_t size() const {
		return memory_.size();
	}

private:
	std::unordered_map<K, V> memory_;
};

#endif
