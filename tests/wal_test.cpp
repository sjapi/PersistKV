#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include "WAL.h"

int main() {
	const std::string wal_filename = "/tmp/wal.log";

	/* replay tests */
	std::ofstream out(wal_filename, std::ios::trunc);
	out << "PUT best 42" << std::endl;
	out << "PUT Nucleus 1" << std::endl;
	out << "PUT Arseniy 23" << std::endl;
	out << "DEL Arseniy" << std::endl;
	out.close();

	WAL<std::string, int> wal(wal_filename);
	auto ops = wal.get_replay_log();

	assert(ops.size() == 4);
	assert(ops[0].type == "PUT" && ops[0].key == "best" && ops[0].val.value() == 42);
	assert(ops[1].type == "PUT" && ops[1].key == "Nucleus" && ops[1].val.value() == 1);
	assert(ops[2].type == "PUT" && ops[2].key == "Arseniy" && ops[2].val.value() == 23);
	assert(ops[3].type == "DEL" && ops[3].key == "Arseniy");

	std::ofstream(wal_filename, std::ios::trunc).close();

	/* Logs test */
	WAL<std::string, int> wal2(wal_filename);

	wal2.log_put("tests_are_cool", 1);
	wal2.log_put("idk", 42);
	wal2.log_del("idk");
	wal2.log_put("100%", 100);

	std::ifstream infile(wal_filename);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}

	assert(lines.size() == 4);
	assert(lines[0] == "PUT tests_are_cool 1");
	assert(lines[1] == "PUT idk 42");
	assert(lines[2] == "DEL idk");
	assert(lines[3] == "PUT 100% 100");
	return 0;
}
