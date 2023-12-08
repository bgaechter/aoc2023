#include "utils.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Hand {
	Hand(std::string input) {
		in = input;
		for (auto const card : input) {
			// A, K, Q, J, T,
			// A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2.
			if (card == 'T') {
				cards.push_back(10);
			} else if (card == 'J') {
				cards.push_back(11);
			} else if (card == 'Q') {
				cards.push_back(12);
			} else if (card == 'K') {
				cards.push_back(13);
			} else if (card == 'A') {
				cards.push_back(14);
			} else {
				cards.push_back(std::atoi(&card));
			}
		}
		std::vector<int> counts;
		for (auto const &c : cards) {
			const int num_items = std::count(cards.cbegin(), cards.cend(), c);
			// std::cout << "number: " << c << ", count: " << num_items << '\n';
			counts.push_back(num_items);
		}
		if (std::find(counts.begin(), counts.end(), 5) != counts.end()) {
			value = 20;
			classification = "five of a kind";
			// five of a kind 19
		} else if (std::find(counts.begin(), counts.end(), 4) != counts.end()) {
			value = 19;
			classification = "four of a kind";
			// four of a kind 18
		} else if (std::find(counts.begin(), counts.end(), 3) != counts.end()) {
			if (std::find(counts.begin(), counts.end(), 2) != counts.end()) {
				// full house
				classification = "fullhouse";
				value = 18;
			} else {
				value = 17;
				classification = "three of a kind";
				// three of a kind 17
			}
		} else if (std::find(counts.begin(), counts.end(), 2) != counts.end()) {
			int pairs = 0;
			for (auto const &c : counts) {
				if (c == 2) {
					pairs++;
				}
			}
			if (pairs == 4) {
				value = 16;
				classification = "two pairs";
				// two pairs 16
			} else if (pairs == 2) {
				classification = "one pair";
				// one pair 15
				value = 15;
			} else {
				std::cout << "should never reach this point" << std::endl;
			}
		} else {
			// highest card 14
			classification = "highest card";
			//			value = *std::max_element(cards.begin(), cards.end());
			value = 14;
		}
	}

	void debug() {

		std::cout << classification;
		std::cout << " cards: ";
		for (auto const &c : cards) {
			std::cout << c << " ";
		}
		std::cout << "(" << in << ")"
		          << " value " << value;
		std::cout << " bid " << bid << std::endl;
	}
	std::string in;
	std::string classification;
	std::vector<int> cards;
	int value;
	int bid;
};

bool compareHands(const Hand &l, const Hand &r) {
	if (l.value == r.value) {
		for (size_t i = 0; i < l.cards.size(); i++) {
			if (l.cards[i] != r.cards[i]) {
				return l.cards[i] < r.cards[i];
			}
		}
	}
	return l.value < r.value;
}

int calculateRank(const Hand &hand, size_t index) {
	return hand.bid * (index + 1);
}

void solve_day07(std::ifstream &infile) {
	std::string line;
	std::vector<Hand> hands{};
	std::unordered_set<std::string> debug;

	while (getline(infile, line)) {
		auto hand = split(line, " ");
		debug.insert(hand[0]);
		Hand h{hand[0]};
		h.bid = std::stoi(hand[1]);
		hands.push_back(h);
	}
	std::sort(hands.begin(), hands.end(), compareHands);

	int totalWinnings = 0;
	for (size_t i = 0; i < hands.size(); i++) {
		totalWinnings += calculateRank(hands[i], i);
		std::cout << "rank: " << (i + 1) << " score " << calculateRank(hands[i], i) << " ";
		hands[i].debug();
	}
	std::cout << "unique hands: " << debug.size() << std::endl;
	std::cout << "Part 01: " << totalWinnings << std::endl;
}
