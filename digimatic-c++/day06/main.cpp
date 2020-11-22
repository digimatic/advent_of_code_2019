// Advent of Code 2019
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using namespace westerstrom;
using namespace std;
using namespace std::string_literals;

pair<string, string> parseLine(const string& line)
{
	regex re("(\\w+)\\)(\\w+)");
	smatch m;
	regex_match(line, m, re);
	return {m[1].str(), m[2].str()};
}

auto parseLines(const vector<string>& lines)
{
	vector<pair<string, string>> parsedLines;
	for(auto& line : lines)
	{
		parsedLines.push_back(parseLine(line));
	}
	return parsedLines;
}

void solve_part1()
{
	auto parsedInput = parseLines(readLines(string(inputFile)));
	unordered_map<string, string> t;
	int cs{};
	for(auto [x, y] : parsedInput)
	{
		t.insert({y, x});
	}
	for(auto [o, p] : t)
	{
		while(p != "COM")
		{
			p = t[p];
			cs++;
		}
		cs++;
	}

	cout << dayName << " - part 1: " << cs << endl;
}

void solve_part2()
{
	auto parsedInput = parseLines(readLines(string(inputFile)));
	unordered_map<string, vector<string>> g;
	for(auto [x, y] : parsedInput)
	{
		g[x].push_back(y);
		g[y].push_back(x);
	}

	unordered_set<string> visited;
	string c = g["YOU"][0];
	string d = g["SAN"][0];
	int n = 0;
	deque<pair<string, int>> q;
	q.push_front({c, 0});
	while(!q.empty())
	{
		auto [c, n] = q.front();
		q.pop_front();

		if(!visited.contains(c))
		{
			if(c == d)
			{
				cout << dayName << " - part 2: " << n << endl;
				return;
			}
			visited.insert(c);

			for(auto next : g[c])
			{
				if(next != "YOU" && next != "SAN")
					q.push_front({next, n + 1});
			}
		}
	}
	cout << dayName << " - part 2: " << n << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
