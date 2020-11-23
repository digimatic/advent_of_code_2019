// Advent of Code 2019
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>
#include <common/graph.h>

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
	Graph<string> g;
	for(auto [x, y] : parsedInput)
	{
		g.edges[x].push_back(y);
		g.edges[y].push_back(x);
	}

	string c = g.edges["YOU"][0];
	string d = g.edges["SAN"][0];

	auto visit = [d](string c, int n) { return (c == d); };
	auto next = [&g](string c, int n) {
		auto neighbors = g.edges[c];
		neighbors.erase(remove_if(begin(neighbors), end(neighbors),
		                          [](string n) { return n == "YOU" || n == "SAN"; }),
		                end(neighbors));
		return neighbors;
	};

	auto [_, n] = bfs(g, c, visit, next);

	cout << dayName << " - part 2: " << n << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
