// Advent of Code 2019 - Day 1
// Peter Westerström (digimatic)

#include "config.h"

#include <fstream>
#include <iostream>

using namespace std;

void solve_day1_part1()
{
	fstream f(INPUT_FILE, std::ios::in);
	int sum{};
	while(!f.eof())
	{
		int mass{};
		f >> mass;
		if(!f.good())
			break;
		auto fuel = (mass / 3) - 2;
		sum += fuel;
	}
	cout << "day1 part1:" << sum << "\n";
}

int computeFuel(int mass)
{
	auto fuel = (mass / 3) - 2;
	if(fuel <= 0)
		return 0;

	return fuel + computeFuel(fuel);
}

void solve_day1_part2()
{
	fstream f(INPUT_FILE, std::ios::in);
	int sum{};
	while(!f.eof())
	{
		int mass{};
		f >> mass;
		if(!f.good())
			break;
		auto fuel = computeFuel(mass);
		sum += fuel;
	}
	cout << "day1 part2:" << sum << "\n";
}

int main()
{
	solve_day1_part1();
	solve_day1_part2();
	return 0;
}
