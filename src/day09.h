#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::pair<int, int> extrapolate_next_value(std::vector<int> nums) {
	int last_num = nums[nums.size() - 1];
	int first_num = nums[0];
	std::vector<int> last_diff{};
	std::vector<int> first_diff{};
	while (true) {
		std::vector<int> diffs{};
		for (size_t i = 1; i < nums.size(); i++) {
			diffs.push_back(nums[i] - nums[i - 1]);
		}
		if (std::all_of(diffs.begin(), diffs.end(), [](int diff) { return diff == 0; })) {
			break;
		}
		last_diff.push_back(diffs[diffs.size() - 1]);
		first_diff.push_back(diffs[0]);
		nums = diffs;
	}
	int next = 0;
	while (!last_diff.empty()) {
		int num = last_diff.back();
		last_diff.pop_back();
		next = num + next;
	}
	int prev = 0;
	while (!first_diff.empty()) {
		int num = first_diff.back();
		first_diff.pop_back();
		prev = num - prev;
	}

	return std::make_pair(first_num - prev, next + last_num);
}

void solve_day09(std::ifstream &infile) {
	std::string line;
	std::vector<std::vector<int>> rows{};
	while (getline(infile, line)) {
		std::istringstream iss(line);
		std::vector<int> row{};
		int num{};
		while (iss >> num) {
			row.push_back(num);
		}
		rows.push_back(row);
	}
	int result_p01 = 0;
	int result_p02 = 0;
	for (auto const &row : rows) {
		auto res = extrapolate_next_value(row);
		result_p01 += res.second;
		result_p02 += res.first;
	}
	std::cout << "Part 01 " << result_p01 << std::endl;
	std::cout << "Part 02 " << result_p02 << std::endl;
}
