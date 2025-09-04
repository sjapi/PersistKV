#ifndef __PERSIST_KV__
#define __PERSIST_KV__

#include <optional>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "Serializer.h"
#include "WAL.h"

/*
 * Requirements for template parameter K (key):
 *  - must be hashable (std::hash<K> specification must exist)
 *  - must be equality comparable (operator== must be defined)
 *  - must be serializable via PersistKVSerializer<K>
 *
 * Requirements for template parameter V (value):
 *  - must be copyable/movable 
 *  - must be serializable via PersistKVSerializer<V>
 */
template <typename K, typename V>
class PersistKV {
public:
	PersistKV(const std::string& wal_file = "wal.log") :
		wal_(wal_file)
	{
		replay_wal();
	}

	virtual ~PersistKV() {
	}

	bool put(const K& key, const V& val) {
		wal_.log_put(key, val);
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
		wal_.log_del(key);
		return memory_.erase(key) > 0;
	}

	bool clear() {
		memory_.clear();
		// clear wal file
		return true;
	}

	size_t size() const {
		return memory_.size();
	}

private:
	std::unordered_map<K, V> memory_;
	WAL<K, V> wal_;

	void replay_wal() {
		for (auto op : wal_.get_replay_log()) {
			if (op.type == "PUT") {
				memory_[op.key] = op.val.value();
			} else if (op.type == "DEL") {
				memory_.erase(op.key);
			}
		}
	}
};

#endif
