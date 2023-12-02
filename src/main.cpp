#include "day01.h"
#include "day02.h"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <filesystem>

int main(int argc, char *argv[])
{
  std::string day = "01";
  if (argc > 1)
  {
    day = argv[1];
  }
  std::filesystem::path cwd = std::filesystem::current_path();
  std::cout << "Solving Day " << day << std::endl;
  std::string file_path = cwd.string() + "/data/day" + day + ".txt";
  std::ifstream infile(file_path);
  if (day == "01")
  {
    solve_day01(infile);
  } else if (day == "02") {
    solve_day02(infile);
  }
  else
  {
    std::cout << "No such day " << day << std::endl;
    return -1;
  }
  return 1;
}
