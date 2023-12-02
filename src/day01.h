#pragma once
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

void replace_all(std::string &str, const std::string &from,
                 const std::string &to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing
                              // 'x' with 'yx'
  }
}

void solve_day01(std::ifstream &infile) {

  std::vector<std::string> nums{"one", "two",   "three", "four", "five",
                                "six", "seven", "eight", "nine"};
  for (int i = 1; i < 3; i++) {
    std::string line;
    int result = 0;
    infile.clear(); // clear fail and eof bits
    infile.seekg(0, std::ios::beg);
    while (std::getline(infile, line)) {
      if (i == 2) {
        std::priority_queue<std::pair<int, std::string>,
                            std::vector<std::pair<int, std::string>>,
                            std::greater<std::pair<int, std::string>>>
            q{};
        for (std::size_t i = 0; i < nums.size(); i++) {
          auto found = line.find(nums[i]);
          if (found != std::string::npos) {
            q.push({found, nums[i]});
          }
        }

        while (q.size() > 0) {
          auto num = q.top();
          q.pop();
          if (num.second == "one") {
            replace_all(line, "one", "one1one");
          }
          if (num.second == "two") {
            replace_all(line, "two", "two2two");
          }
          if (num.second == "three") {
            replace_all(line, "three", "three3three");
          }
          if (num.second == "four") {
            replace_all(line, "four", "four4four");
          }
          if (num.second == "five") {
            replace_all(line, "five", "five5five");
          }
          if (num.second == "six") {
            replace_all(line, "six", "six6six");
          }
          if (num.second == "seven") {
            replace_all(line, "seven", "seven7seven");
          }
          if (num.second == "eight") {
            replace_all(line, "eight", "eight8eight");
          }
          if (num.second == "nine") {
            replace_all(line, "nine", "nine9nine");
          }
        }
      }

      char first;
      char last;
      int count = 0;

      for (char c : line) {
        if (std::isdigit(c) && count == 0) {
          first = c;
          count++;
        } else if (std::isdigit(c) && count > 0) {
          last = c;
          count++;
        }
      }
      if (count > 1) {
        int a = first - '0';
        int b = last - '0';
        result += a * 10;
        result += b;
      } else {
        int a = first - '0';
        result += a * 10;
        result += a;
      }
    }
    std::cout << "Part " << i << " : " << result << std::endl;
  }
}
