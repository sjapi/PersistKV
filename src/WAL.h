#ifndef WAL_H
#define WAL_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Serializer.h"
#include "utils.h"

template <typename K, typename V>
class WAL {
public:
	struct Operation {
		std::string type;
		K key;
		std::optional<V> val;
	};

	WAL(const std::string& filename) :
		filename_(filename)
	{
		ofs_.open(filename_, std::ios::app);
		replay();
	}

	~WAL() {
		if (ofs_.is_open()) {
			ofs_.close();
		}
	}

	void log_put(const K& key, const V& val) {
		write_log("PUT " + PersistKVSerializer<K>::serialize(key) + " " + PersistKVSerializer<V>::serialize(val));
	}

	void log_del(const K& key) {
		write_log("DEL " + PersistKVSerializer<K>::serialize(key));
	}

	void clear() {
		ofs_.close();
		std::ofstream(filename_, std::ios::trunc).close();
		replay_log_.clear();
	}

	std::vector<Operation> get_replay_log() const {
		return replay_log_;
	}
private:
	std::string filename_;
	std::ofstream ofs_;
	std::vector<Operation> replay_log_;

	void write_log(const std::string& line) {
		if (!ofs_.is_open()) {
			ofs_.open(filename_, std::ios::app);
		}
		ofs_ << line << "\n";
		ofs_.flush();
	}

	void replay() {
		std::ifstream ifs(filename_);
		if (!ifs) {
			return;
		}
		
		std::string line;
		while (std::getline(ifs, line)) {
			std::vector<std::string> tokens = split(line, ' ');
			if (tokens.empty()) {
				continue;
			}
			const std::string op = tokens[0];
			if (op == "PUT" && tokens.size() == 3) {
				K key = PersistKVSerializer<K>::deserialize(tokens[1]);
				V val = PersistKVSerializer<V>::deserialize(tokens[2]);
				replay_log_.push_back({"PUT", key, val});
			} else if (op == "DEL" && tokens.size() == 2) {
				K key = PersistKVSerializer<K>::deserialize(tokens[1]);
				replay_log_.push_back({"DEL", key});
			}
		}
	}
};

#endif
