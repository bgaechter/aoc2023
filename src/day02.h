#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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

void solve_day02(std::ifstream &infile) {
  std::string line;
  int red_cubes = 12;
  int green_cubes = 13;
  int blue_cubes = 14;
  int result = 0;
  int result_p2 = 0;
  std::map<std::string, int> cubes{};
  while (std::getline(infile, line)) {
    auto game_id = split(split(line, ":")[0], " ")[1];
    auto revealed_cubes = split(split(line, ":")[1], ";");
    std::map<std::string, int> cubes_min{};
    for (auto reveal : revealed_cubes) {
      auto round = split(reveal, ",");
      for (auto c : round) {
        auto val = split(c, " ");
        cubes[val[2]] = std::max(cubes[val[2]], std::stoi(val[1]));

        cubes_min[val[2]] = std::min(cubes[val[2]], std::stoi(val[1]));
      }
    }
    if (cubes["red"] <= red_cubes && cubes["green"] <= green_cubes &&
        cubes["blue"] <= blue_cubes) {
      result += std::stoi(game_id);
    }
    result_p2 += cubes["red"] * cubes["green"] * cubes["blue"];
    cubes["red"] = 0;
    cubes["green"] = 0;
    cubes["blue"] = 0;
  }
  std::cout << "Part 1: " << result << std::endl;
  std::cout << "Part 2: " << result_p2 << std::endl;
}
