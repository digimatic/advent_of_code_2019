// Advent of Code 2018
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <iostream>

using namespace westerstrom;
using namespace std;

int run(vector<int> p, int noun, int verb)
{
	p[1] = noun;
	p[2] = verb;
	for(int i = 0; i < p.size();)
	{
		switch(p[i])
		{
			case 1:
				p[p[i + 3]] = p[p[i + 1]] + p[p[i + 2]];
				i += 4;
				break;
			case 2:
				p[p[i + 3]] = p[p[i + 1]] * p[p[i + 2]];
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
	auto p = splitNumbers(readLines(string(inputFile))[0]);
	cout << dayName << " - part 1: " << run(p, 12, 2) << endl;
}

void solve_part2()
{
	auto p = splitNumbers(readLines(string(inputFile))[0]);
	for(int noun = 0; noun <= 99; ++noun)
	{
		for(int verb = 0; verb <= 99; ++verb)
		{
			try
			{
				if(run(p, noun, verb) == 19690720)
				{
					int r = 100 * noun + verb;
					cout << dayName << " - part 2: " << r << endl;
					return;
				}
			} catch(int)
			{
			}
		}
	}
	cout << dayName << " - part 2: NO RESULT" << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
