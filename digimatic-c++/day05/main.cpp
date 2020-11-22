// Advent of Code 2019
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
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

struct System
{
	function<int(void)> read;
	function<void(int)> write;
};

int run(vector<int> p, System& sys)
{
	auto pv = [&p](int param, int mode) {
		if(mode == 0)
			return p[param];
		return param;
	};

	for(int i = 0; i < p.size();)
	{
		int op = p[i] % 100;
		int m1 = (p[i] / 100) % 10;
		int m2 = (p[i] / 1000) % 10;
		int m3 = (p[i] / 10000) % 10;
		switch(op)
		{
			case 1:
				p[p[i + 3]] = pv(p[i + 1], m1) + pv(p[i + 2], m2);
				i += 4;
				break;
			case 2:
				p[p[i + 3]] = pv(p[i + 1], m1) * pv(p[i + 2], m2);
				i += 4;
				break;
			case 3:
				p[p[i + 1]] = sys.read();
				i += 2;
				break;
			case 4:
				sys.write(pv(p[i + 1], m1));
				i += 2;
				break;
			case 5:
				if(pv(p[i + 1], m1) != 0)
				{
					i = pv(p[i + 2], m2);
				} else
				{
					i += 3;
				}
				break;
			case 6:
				if(pv(p[i + 1], m1) == 0)
				{
					i = pv(p[i + 2], m2);
				} else
				{
					i += 3;
				}
				break;
			case 7:
				if(pv(p[i + 1], m1) < pv(p[i + 2], m2))
				{
					p[p[i + 3]] = 1;
				} else
				{
					p[p[i + 3]] = 0;
				}
				i += 4;
				break;
			case 8:
				if(pv(p[i + 1], m1) == pv(p[i + 2], m2))
				{
					p[p[i + 3]] = 1;
				} else
				{
					p[p[i + 3]] = 0;
				}
				i += 4;
				break;
			case 99:
				i = p.size();
				break;
			default:
				throw -1;
		}
	}
	return p[0];
}

void solve_part1()
{
	cout << dayName << " - part 1: " << endl;

	auto p = splitNumbers(readLines(string(inputFile))[0], true);
	System sys;
	sys.read = []() { return 1; };
	sys.write = [](int x) { cout << "Output: " << x << endl; };
	run(p, sys);
}

void solve_part2()
{
	cout << dayName << " - part 2: " << endl;

	auto p = splitNumbers(readLines(string(inputFile))[0], true);
	System sys;
	sys.read = []() { return 5; };
	sys.write = [](int x) { cout << "Output: " << x << endl; };
	run(p, sys);
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
