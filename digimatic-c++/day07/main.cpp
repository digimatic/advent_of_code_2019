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

// -- Part 1 ---------------------------------------------------------------------------------------

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
	int bestSignal{};
	vector<int> bestPhases;

	auto p = splitNumbers(readLines(string(inputFile))[0], true);
	System sys;
	vector<int> phases = {0, 1, 2, 3, 4};
	do
	{
		int booster = 0;
		int signal = 0;
		sys.read = [&booster, &signal, &phases]() {
			static bool first = false;
			first = !first;
			if(first)
			{
				return phases[booster];
			} else
			{
				return signal;
			}
		};
		sys.write = [&signal](int x) {
			// output signal
			signal = x;
		};

		for(int i = 0; i < 5; ++i)
		{
			booster = i;
			run(p, sys);
		}

		if(signal > bestSignal)
		{
			bestSignal = signal;
			bestPhases = phases;
		}
	} while(next_permutation(begin(phases), end(phases)));

	cout << dayName << " - part 1: " << endl;
	cout << "Max thruster signal: " << bestSignal << endl;
	cout << "Phase setting sequence: ";
	for(auto ph : bestPhases)
	{
		cout << ph << " ";
	}
	cout << endl;
}

// -- Part 2 ---------------------------------------------------------------------------------------

enum class RunState
{
	Suspended,
	Halted,
	Failed
};

enum class SuspendReason
{
	Nothing,
	Read,
	Write
};

struct Machine
{
	vector<int> p;
	int i{};
	int read{};
	int write{};
	RunState state{RunState::Suspended};
	SuspendReason suspendReason{SuspendReason::Nothing};
	void run();
};

void Machine::run()
{
	auto pv = [this](int param, int mode) {
		if(mode == 0)
			return p[param];
		return param;
	};

	if(state == RunState::Suspended && suspendReason == SuspendReason::Read)
	{
		p[p[i + 1]] = read;
		i += 2;
	} else if(state == RunState::Suspended && suspendReason == SuspendReason::Write)
	{
		i += 2;
	} else if(state == RunState::Suspended && suspendReason == SuspendReason::Nothing)
	{

	} else if(state == RunState::Halted || state == RunState::Failed)
	{
		return;
	}

	while(true)
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
				state = RunState::Suspended;
				suspendReason = SuspendReason::Read;
				return;
			case 4:
				write = pv(p[i + 1], m1);
				state = RunState::Suspended;
				suspendReason = SuspendReason::Write;
				return;
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
				state = RunState::Halted;
				return;
			default:
				state = RunState::Failed;
				return;
		}
	}
}

void solve_part2()
{
	int bestSignal{};
	vector<int> bestPhases;

	auto src = splitNumbers(readLines(string(inputFile))[0], true);
	vector<int> phases = {5, 6, 7, 8, 9};
	do
	{
		Machine machines[5];
		machines[0].p = src;
		machines[1].p = src;
		machines[2].p = src;
		machines[3].p = src;
		machines[4].p = src;
		int readCount[5] = {0, 0, 0, 0, 0};

		int booster = 0;
		do
		{
			auto& machine = machines[booster];
			machine.run();
			if(machine.state == RunState::Failed)
				throw -1;
			else if(machine.state == RunState::Halted)
			{
				if(machines[4].write > bestSignal)
				{
					bestSignal = machines[4].write;
					bestPhases = phases;
				}
				break;
			} else if(machine.state == RunState::Suspended)
			{
				if(machine.suspendReason == SuspendReason::Read)
				{
					int prevBooster = (booster + 4) % 5;
					if(readCount[booster] == 0)
						machine.read = phases[booster];
					else
						machine.read = machines[prevBooster].write;
					readCount[booster]++;
					// continue with same booster
				} else if(machine.suspendReason == SuspendReason::Write)
				{
					int nextBooster = (booster + 1) % 5;
					booster = nextBooster;
				} else
				{
					throw -1;
				}
			} else
			{
				throw -1;
			}
		} while(true);

	} while(next_permutation(begin(phases), end(phases)));

	cout << dayName << " - part 2: " << endl;
	cout << "Max thruster signal: " << bestSignal << endl;
	cout << "Phase setting sequence: ";
	for(auto ph : bestPhases)
	{
		cout << ph << " ";
	}
	cout << endl;
}

int main()
{
	solve_part1();
	solve_part2();
	return 0;
}
