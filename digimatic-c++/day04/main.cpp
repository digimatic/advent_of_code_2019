// Advent of Code 2019
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <cassert>
#include <iostream>
#include <tuple>

using namespace westerstrom;
using namespace std;

auto inputRange = pair(138241, 674034);

// ------- Part 1 -------

pair<bool, bool> isNonDecreasingDigitsWithPair(int x)
{
	if(x < 10)
		return {true, false};

	int lastDigit = x % 10;
	int nextDigit = (x / 10) % 10;
	if(nextDigit > lastDigit)
		return {false, false};

	auto [isDecreasing, hasPair] = isNonDecreasingDigitsWithPair(x / 10);
	return make_pair(isDecreasing, hasPair || (nextDigit == lastDigit));
}

bool isValid(int x)
{
	auto [isDecreasing, hasPair] = isNonDecreasingDigitsWithPair(x);
	return isDecreasing && hasPair;
}

void solve_part1()
{
	// unit test code
	assert(isValid(111111));
	assert(!isValid(223450));
	assert(!isValid(123789));

	// solution
	int numValid{};
	for(int x = inputRange.first; x <= inputRange.second; ++x)
	{
		if(isValid(x))
			numValid++;
	}

	cout << dayName << " - part 1: " << numValid << endl;
}

// ------- Part 2 -------

bool isIncreasing(int x)
{
	if(x < 10)
		return true;

	int d1 = (x / 10) % 10;
	int d2 = x % 10;

	return (d1 <= d2) && isIncreasing(x / 10);
}

bool hasExactly2EqualDigits(int x, int prevDigit)
{
	if(x < 10)
		return false;
	int d2 = (x / 10) % 10;
	int d3 = x % 10;
	if(x < 100)
	{
		return d2 == d3 && d3 != prevDigit;
	}

	int d1 = (x / 100) % 10;

	bool valid = (d2 == d3 && d1 != d2 && d3 != prevDigit);
	if(valid)
		return true;

	return hasExactly2EqualDigits(x / 10, d3);
}

bool isValid2(int x)
{
	bool a = isIncreasing(x);
	bool b = hasExactly2EqualDigits(x, -1);
	return a && b;
}

void solve_part2()
{
	// unit test code
	assert(isValid2(112233));
	assert(!isValid2(123444));
	assert(isValid2(111122));
	assert(isValid2(122222334));
	assert(isValid2(122233445));

	// solution
	int numValid{};
	for(int x = inputRange.first; x <= inputRange.second; ++x)
	{
		if(isValid2(x))
			numValid++;
	}

	cout << dayName << " - part 2: " << numValid << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
