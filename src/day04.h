#pragma once
#include "utils.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_set>

struct Card
{
  int id;
  std::vector<int> winning_numbers{};
  std::vector<int> numbers_on_card{};
  std::size_t copies{};
};

std::vector<int> extract_numbers(const std::string &s)
{
  std::cout << s << '\n';
  std::vector<int> numbers;
  std::size_t start = 0;
  std::size_t end = s.find(' ');
  for (int i = 0; i < s.size(); i += 3)
  {
    if (s[i] == ' ')
    {
      numbers.push_back(std::stoi(s.substr(i + 1, i + 2)));
    }
    else
    {
      numbers.push_back(std::stoi(s.substr(i, i + 2)));
    }
  }
  return numbers;
}

void solve_d4_part01(std::ifstream &infile)
{
  std::string line;
  int result = 0;
  while (std::getline(infile, line))
  {
    auto card = split(line, ":");
    int points = 0;
    auto nums = split(card[1], "|");
    auto winning_nums = split(nums[0], " ");
    auto my_nums = split(nums[1], " ");
    std::unordered_set<int> draw{};
    for (auto num : winning_nums)
    {
      try
      {
        draw.insert(std::stoi(num));
      }
      catch (std::invalid_argument const &ex)
      {
        std::cout << ex.what() << " " << num << '\n';
      }
    }
    for (auto num : my_nums)
    {
      try
      {
        if (draw.contains(std::stoi(num)))
        {
          if (points == 0)
          {
            points += 1;
          }
          else
          {
            points *= 2;
          }
        }
      }
      catch (std::invalid_argument const &ex)
      {
        std::cout << ex.what() << " " << num << '\n';
      }
    }
    result += points;
  }
  std::cout << "Part 01: " << result << std::endl;
}

void solve_d4_part02(std::ifstream &infile)
{
  std::string line;
  std::size_t total_points = 0;
  std::vector<Card> cards;
  while (std::getline(infile, line))
  {
    Card c;
    std::size_t start = 0;
    std::size_t end = line.find(':');
    c.id = std::stoi(line.substr(5, end - 5));
    start = end + 2;
    end = line.find('|', start);

    c.winning_numbers = extract_numbers(line.substr(start, end - start));
    c.numbers_on_card = extract_numbers(line.substr(end + 2, line.size() - end));
    c.copies = 1;
    cards.push_back(c);
  }

  for (const auto &card : cards)
  {
    int count = 0;
    for (const auto &number_on_card : card.numbers_on_card)
    {
      if (std::find(std::begin(card.winning_numbers), std::end(card.winning_numbers), number_on_card) != std::end(card.winning_numbers))
      {
        count++;
      }
    }
    for (int i = card.id + 1 - 1 /*zero index*/; i < std::min(cards.size(), std::size_t(card.id + count)); i++)
    {
      cards[i].copies += card.copies;
    }
  }
  std::cout << std::accumulate(std::begin(cards), std::end(cards), 0, [](std::size_t total, const Card &card)
                               { return total + card.copies; })
            << '\n';

  std::cout << "Part 02: " << std::endl;
}

void solve_day04(std::ifstream &infile)
{
  solve_d4_part01(infile);
  infile.clear(); // clear fail and eof bits
  infile.seekg(0, std::ios::beg);
  solve_d4_part02(infile);
}
