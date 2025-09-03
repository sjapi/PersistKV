#ifndef __PERSIST_KV__
#define __PERSIST_KV__

#include <optional>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "Serializer.h"

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
	PersistKV(const std::string& wal_filename = "wal.log") :
		wal_filename_(wal_filename)
	{
		replay_wal();
	}

	virtual ~PersistKV() {
		wal_.close();
	}

	bool put(const K& key, const V& val) {
		write_wal("PUT " + PersistKVSerializer<K>::serialize(key) + " " + PersistKVSerializer<V>::serialize(val));
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
		write_wal("DEL" + PersistKVSerializer<K>::serialize(key));
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
	std::string wal_filename_;
	std::ofstream wal_;

	void write_wal(const std::string& entry) {
		if (!wal_.is_open()) {
			wal_.open(wal_filename_, std::ios::app); // ??
		}
		wal_ << entry << std::endl;
		wal_.flush();
	}

	void replay_wal() {
		std::ifstream f(wal_filename_);
		if (!f) {
			return;
		}
		
		std::string line;
		while (std::getline(f, line)) {
			std::vector<std::string> tokens = split(line, ' ');
			if (tokens.empty()) {
				continue;
			}
			const std::string op = tokens[0];
			if (op == "PUT" && tokens.size() == 3) {
				K key = PersistKVSerializer<K>::deserialize(tokens[1]);
				V val = PersistKVSerializer<V>::deserialize(tokens[2]);
				memory_[key] = val;
			} else if (op == "DEL"&& tokens.size() == 2) {
				K key = PersistKVSerializer<K>::deserialize(tokens[1]);
				memory_.erase(key);
			}
		}
	}
};

#endif
