#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day07b.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	std::string day = "01";
	if (argc > 1) {
		day = argv[1];
	}
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << "Solving Day " << day << std::endl;
	std::string file_path = cwd.string() + "/data/day" + day + ".txt";
	std::ifstream infile(file_path);
	if (day == "01") {
		solve_day01(infile);
	} else if (day == "02") {
		solve_day02(infile);
	} else if (day == "03") {
		solve_day03(infile);
	} else if (day == "04") {
		solve_day04(infile);
	} else if (day == "05") {
		solve_day05(infile);
	} else if (day == "06") {
		solve_day06(infile);
	} else if (day == "07") {
		solve_day07(infile);
		solve_day07b(infile);
	} else if (day == "08") {
		solve_day08(infile);
	} else if (day == "09") {
		solve_day09(infile);
	} else if (day == "10") {
		solve_day10(infile);
	}  else {
		std::cout << "No such day " << day << std::endl;
		return -1;
	}
	infile.close();
	return 1;
}
