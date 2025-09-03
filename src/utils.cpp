#include <vector>
#include <string>
#include <iostream>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}
