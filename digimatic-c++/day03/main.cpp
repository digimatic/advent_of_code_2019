// Advent of Code 2019
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>

using namespace westerstrom;
using namespace std;
using namespace std::string_literals;

auto parseLine(const string& line)
{
	vector<pair<char, int>> p;

	auto remaining = line;

	while(remaining.length() > 0)
	{
		char c = remaining[0];
		remaining = remaining.substr(1);
		size_t taken = 0;
		auto n = std::stoi(remaining, &taken);
		p.emplace_back(c, n);
		if(taken >= remaining.length())
			break;
		remaining = remaining.substr(taken + 1);
	}
	return p;
}

auto parseLines(const vector<string>& lines)
{
	vector<vector<pair<char, int>>> parsedLines;
	for(auto& line : lines)
	{
		parsedLines.push_back(parseLine(line));
	}
	return parsedLines;
}

pair<int, int> step(char dir)
{
	int dx{0}, dy{0};
	switch(dir)
	{
		case 'U':
			dy = -1;
			break;
		case 'D':
			dy = 1;
			break;
		case 'L':
			dx = -1;
			break;
		case 'R':
			dx = 1;
			break;
	}
	return {dx, dy};
}

void solve_part1()
{
	map<pair<int, int>, char> grid;
	int minDist = std::numeric_limits<int>::max();

	grid[make_pair(0, 0)] = 'o';

	auto parsedInput = parseLines(readLines(string(inputFile)));
	int x = 0;
	int y = 0;
	for(auto [dir, n] : parsedInput[0])
	{
		for(int i = 0; i < n; i++)
		{
			auto [dx, dy] = step(dir);
			x += dx;
			y += dy;
			auto& c = grid[make_pair(x, y)];
			c = 'a';
		}
	}
	x = y = 0;
	for(auto [dir, n] : parsedInput[1])
	{
		for(int i = 0; i < n; i++)
		{
			auto [dx, dy] = step(dir);
			x += dx;
			y += dy;
			auto& c = grid[make_pair(x, y)];
			if(c == 'a')
			{
				minDist = min(abs(x) + abs(y), minDist);
			} else
			{
				c = 'b';
			}
		}
	}

	cout << dayName << " - part 1: " << minDist << endl;
}

void solve_part2()
{
	map<pair<int, int>, int> grid;
	int minSteps = std::numeric_limits<int>::max();

	grid[make_pair(0, 0)] = 0;

	auto parsedInput = parseLines(readLines(string(inputFile)));
	int x = 0;
	int y = 0;
	int steps{};
	for(auto [dir, n] : parsedInput[0])
	{
		for(int i = 0; i < n; i++)
		{
			auto [dx, dy] = step(dir);
			x += dx;
			y += dy;
			steps++;
			auto& c = grid[make_pair(x, y)];
			c = steps;
		}
	}
	x = y = 0;
	steps = 0;
	for(auto [dir, n] : parsedInput[1])
	{
		for(int i = 0; i < n; i++)
		{
			auto [dx, dy] = step(dir);
			x += dx;
			y += dy;
			steps++;
			if(grid.contains(make_pair(x, y)))
			{
				minSteps = min(minSteps, grid.at(make_pair(x, y)) + steps);
			}
		}
	}

	cout << dayName << " - part 2: " << minSteps << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
