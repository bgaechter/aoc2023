#pragma once
#include <string>
#include <vector>

void replace_all(std::string &str, const std::string &from,
                 const std::string &to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();  // In case 'to' contains 'from', like replacing
		                           // 'x' with 'yx'
	}
}

std::vector<std::string> split(std::string s, std::string delimiter) {
	std::vector<std::string> result{};

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		result.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	result.push_back(s);
	return result;
}
