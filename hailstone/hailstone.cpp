// Hailstone sequence is a sequence of numbers that is created by following steps:
//		1. If the number is 1 then your are done
//		2. If the number is even divide by 2
//		3. If the number is odd then multuply by 3 and add 1
//		Go back to step 1
// For example	: starting at 1 you will get Sequence - [1 ], Steps = 0
//				: starting at 2 you will get Sequence - [2 1], Steps = 1
//				: starting at 3 you will get Sequence - [3 10 5 16 8 4 2 1], Steps = 7
//				: starting at 4 you will get Sequence - [4 2 1], Steps = 2
//				: starting at 5 you will get Sequence - [5 16 8 4 2 1], Steps = 5
//				: starting at 6 you will get Sequence - [6 3 10 5 16 8 4 2 1], Steps = 8
// The program has two functions; first function given a number computes number of steps required to reach 1
// second function given a collections of numbers computes the max steps of a number in the set

#include <iostream>
#include <map>
#include <vector>
#include <chrono>

// Global cache of computed hailstone steps
std::map<int, int> gcSteps;

// Function given a number computes number of steps required to reach 1
int hailstoneSteps(int n, std::ostream &out) {
	int steps = 0;
	if (n < 2) {
		return 0;
	}

	auto newN = (n % 2) ? (n*3 + 1) : (n/2);
	out << " " << newN;
	return hailstoneSteps(newN, out) + 1;
}

// Optimized Function given a number computes number of steps required to reach 1
// caches the steps of each number in the hailstone sequence 
int optHailstoneSteps(int n) {
	int steps = 0;
	if (n < 2) {
		return 0;
	}

	auto itr = gcSteps.find(n);
	if (itr != gcSteps.end()) {
		return itr->second;
	}

	auto nextN = (n % 2) ? (n * 3 + 1) : (n / 2);
	steps = optHailstoneSteps(nextN) + 1;
	gcSteps[n] = steps;
	return steps;
}

// Function given an array of numbers computes max hailstone steps 
int maxStepsHailstone(std::vector<int> numbers) {
	int maxSteps = 0;
	for (auto &&number : numbers) {
		int steps = optHailstoneSteps(number);
		if (steps > maxSteps) {
			maxSteps = steps;
		}
	}
	return maxSteps;
}

int main()
{
	std::cout << "Steps for hailstone sequence" << std::endl;
	std::chrono::duration<double> simpleDuration, optDuration;
	const int limit = 10000;
	if( true)
	{
		std::cout << "Standard Algorithm" << std::endl;
		auto start = std::chrono::system_clock::now();
		for (int i = 1; i <= limit; ++i) {
			std::cout << "Input number = " << i << ", Sequence = [";
			int steps = hailstoneSteps(i, std::cout);
			std::cout << " ], Steps =  " << steps << std::endl;
		}
		auto end = std::chrono::system_clock::now();

		simpleDuration = end - start;
	}

	{
		std::cout << "Optimized Algorithm" << std::endl;
		auto start = std::chrono::system_clock::now();
		std::vector<int> numbers(limit);
		for (int i = 1; i <= limit; ++i) {
			std::cout << "Input number = " << i;
			int steps = optHailstoneSteps(i);
			std::cout << ", Steps =  " << steps << std::endl;
			numbers.emplace_back(i);
		}
		auto end = std::chrono::system_clock::now();

		optDuration = end - start;
		std::cout << "Max Steps in previous sequence is  = " << maxStepsHailstone(numbers) << std::endl;
	}
	std::cout << "Total time simple algorithm = " << static_cast<int>(simpleDuration.count()) << " seconds" << std::endl;
	std::cout << "Total time opt algorithm = " << static_cast<int>(optDuration.count()) << " seconds" << std::endl;

	char c; std::cin >> c;
	return 0;
}