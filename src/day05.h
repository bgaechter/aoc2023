#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using Range = std::pair<long long, long long>;

bool process_map(std::ifstream &infile, std::vector<unsigned int> &initial, std::vector<unsigned int> &mapped) {
	std::string line;
	mapped = initial;

	while (getline(infile, line)) {
		if (line == "")
			return true;

		if (!isdigit(line[0]))
			continue;

		std::istringstream iss(line);
		unsigned int dest, source, range;
		iss >> dest >> source >> range;

		for (unsigned int i = 0; i < (unsigned int)initial.size(); i++) {
			if (initial[i] < source)
				continue;

			if (initial[i] > source + range)
				continue;

			unsigned int offset = initial[i] - source;

			mapped[i] = dest + offset;
		}
	}

	return false;
}
bool process_map_p2(std::ifstream &infile, std::vector<Range> &initial, std::vector<Range> &mapped) {
	std::string line;
	mapped = initial;

	while (getline(infile, line)) {
		if (line == "")
			return true;

		if (!isdigit(line[0]))
			continue;

		std::istringstream iss(line);
		long long dest, source, range;
		iss >> dest >> source >> range;

		long long source_end = source + range - 1;

		for (int i = 0; i < (int)initial.size(); i++) {

			long long start = initial[i].first;
			long long len = initial[i].second;

			long long end = start + len - 1;

			if (start > source_end || end < source)
				continue;

			long long min = std::max(source, start);
			long long min_offset = min - source;

			mapped.erase(mapped.begin() + i);

			mapped.insert(mapped.begin() + i, Range(dest + min_offset, dest + min_offset + len));

			if (min > start)
				mapped.push_back(Range(start, min - 1));
			if (source_end < end)
				mapped.push_back(Range(source_end + 1, end));
		}
	}

	return false;
}

void day05_part02(std::ifstream &infile) {
	std::string line;
	getline(infile, line);

	std::vector<Range> seeds;
	std::istringstream iss(line);

	iss.ignore(6);

	long long seed_start, seed_len;
	while (iss >> seed_start >> seed_len) {
		seeds.push_back(Range(seed_start, seed_len));
	}

	std::vector<Range> mapped;

	while (process_map_p2(infile, seeds, mapped)) {
		if (mapped.size() > 0)
			swap(seeds, mapped);
	}

	auto const min = std::min_element(mapped.begin(), mapped.end());

	std::cout << "Part 02: " << (*min).first << std::endl;
}

void solve_day05(std::ifstream &infile) {
	std::string line;
	getline(infile, line);

	std::vector<unsigned int> seeds;
	std::istringstream iss(line);
	unsigned int tmp;
	for (unsigned int i = 0; i < 6; i++)
		iss.get();

	while (!iss.eof()) {
		iss >> tmp;
		seeds.push_back(tmp);
	}
	std::vector<unsigned int> mapped;

	while (process_map(infile, seeds, mapped)) {
		swap(seeds, mapped);
	}

	auto const m = std::min_element(mapped.begin(), mapped.end());

	std::cout << "Part 01 " << *m << std::endl;
	infile.clear();  // clear fail and eof bits
	infile.seekg(0, std::ios::beg);
	day05_part02(infile);
}
