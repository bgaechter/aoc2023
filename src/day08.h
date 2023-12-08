#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void solve_day08_part01(std::unordered_map<std::string, std::pair<std::string, std::string>> &nodes, std::string &instructions) {
	auto node = nodes["AAA"];
	int count = 0;
	while (true) {
		for (auto const instruction : instructions) {
			if (instruction == 'L') {
				if (node.first == "ZZZ") {
					count++;
					std::cout << "Part 01: " << count << std::endl;
					return;
				}
				node = nodes[node.first];
			} else if (instruction == 'R') {
				if (node.second == "ZZZ") {
					count++;
					std::cout << "Part 01: " << count << std::endl;
					return;
				}
				node = nodes[node.second];
			}
			count++;
		}
	}
}

void solve_day08(std::ifstream &infile) {
	std::string instructions{};
	getline(infile, instructions);
	{
		std::string buf;
		getline(infile, buf);
	}
	std::string line;
	std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
	while (getline(infile, line)) {
		std::istringstream iss(line);
		std::vector<std::string> node_def;
		std::string def;
		while (iss >> def) {
			node_def.push_back(def);
		}
		std::string left = node_def[2].substr(1, 3);
		std::string right = node_def[3].substr(0, 3);
		nodes[node_def[0]] = std::make_pair(left, right);
	}
	solve_day08_part01(nodes, instructions);
	std::vector<std::pair<std::string, std::string>> start_points{};
	for (auto n : nodes) {
		if (n.first[2] == 'A') {
			std::cout << n.first << std::endl;
			start_points.push_back(n.second);
		}
	}

	int count = 0;
	while (true) {
		for (auto const instruction : instructions) {
			std::cout << instruction << std::endl;
			for (auto &node : start_points) {
				std::cout << node.first << "|" << node.second << std::endl;
			}
			if (instruction == 'L') {
				for (auto &node : start_points) {
					if (std::all_of(start_points.begin(), start_points.end(), [](std::pair<std::string, std::string> node) { return node.first[2] == 'Z'; })) {
						count++;
						std::cout << "Part 02: " << count << std::endl;
						return;
					}
					node = nodes[node.first];
				}
			} else if (instruction == 'R') {
				for (auto &node : start_points) {
					if (std::all_of(start_points.begin(), start_points.end(), [](std::pair<std::string, std::string> node) { return node.second[2] == 'Z'; })) {
						count++;
						std::cout << "Part 02: " << count << std::endl;
						return;
					}
					node = nodes[node.second];
				}
			}
			count++;
		}
	}
}
