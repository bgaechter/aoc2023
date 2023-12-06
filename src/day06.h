#include <fstream>
#include <iostream>
#include <mutex>
#include <numeric>
#include <sstream>
#include <thread>
#include <vector>

std::mutex result_mutex;
int result_p2 = 0;

int calculate_distance(int windup, int max_time) {
	return windup * (max_time - windup);
}

int calculate_distance_range(long start, long stop, long max_time, long distance_record) {
	for (long i = start; i < stop; i++) {
		if (i * (max_time - i) > distance_record) {
			// std::cout << "found solution " << i << std::endl;
			std::lock_guard<std::mutex> guard(result_mutex);
			result_p2 += 1;
		}
	}
}

void solve_day06(std::ifstream &infile) {
	std::vector<int> times;
	std::vector<int> distances;
	std::string line;

	getline(infile, line);
	std::istringstream isst(line);
	isst.ignore(5);
	int time;
	while (isst >> time) {
		times.push_back(time);
	}

	getline(infile, line);
	std::istringstream issd(line);
	issd.ignore(10);
	int distance;
	while (issd >> distance) {
		distances.push_back(distance);
	}
	std::vector<int> results(4, 0);
	for (size_t i = 0; i < times.size(); i++) {
		std::cout << "time " << times[i] << " distance " << distances[i] << std::endl;
		for (int j = 0; j <= times[i]; j++) {
			if (calculate_distance(j, times[i]) > distances[i]) {
				//				std::cout << "Surpassing record with " << j << " seconds" << std::endl;
				results[i]++;
			}
		}
	}
	std::cout << std::accumulate(results.begin(), results.end(), 1, [](std::size_t total, int r) { return total * r; }) << std::endl;
	/*for (auto const res : results) {
	    std::cout << res << std::endl;
	}*/

	int time_p2 = 60808676;
	long long distance_p2 = 601116315591300;
	int max_threads = 100;
	int range_size = time_p2 / max_threads;
	std::thread threads[max_threads];
	std::cout << "Launching " << max_threads << " threads" << std::endl;
	for (int i = 0; i < max_threads; ++i) {

		int start = i * range_size;
		int end = (i == max_threads - 1) ? time_p2 : start + range_size;
		std::cout << " starting thread with range " << start << " " << end << std::endl;
		threads[i] = std::thread(calculate_distance_range, start, end, time_p2, distance_p2);
	}
	std::cout << "joining threads" << std::endl;
	for (int i = 0; i < max_threads; ++i) {
		threads[i].join();
	}
	std::cout << "part 2 " << result_p2 << std::endl;
}
