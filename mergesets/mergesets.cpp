// This program takes two two arrays of the form [(1, 3), (40, 70), (100, 200) ...] and [(5, 15), (21, 31), (83, 92) ...]
// and merges them into one array.
// It assumes that there are no overlapping entries in the array, for example; (1, 4) (2, 8).
// It also assumes that the entries in the array are in order
//
#include <string>
#include <iostream>
#include <deque>
#include <algorithm>

// Main function to merge the two arrays of ranges
typedef std::deque<std::pair<int, int>> RangeSet;
void printRangeSet(const std::string &name, const RangeSet &set) {
	std::cout << "-------------- Range Set " << name << "----------------" << std::endl;
	std::cout << "[";
	for (auto &&range : set) {
		std::cout << "(" << range.first << ", " << range.second << "), ";
	}
	std::cout << "]" << std::endl;
}
RangeSet
mergeRanges(const RangeSet &s1, const RangeSet &s2)
{
	std::cout << std::endl;
	printRangeSet("Input S1", s1);
	printRangeSet("Input S2", s2);

	if (s1.empty()) {
		return s2;
	}

	if (s2.empty()) {
		return s1;
	}

	RangeSet result;
	auto itrS1 = s1.begin();
	auto itrS2 = s2.begin();
	for (; itrS1 != s1.end();) {

		// Nothing left to compare, copy rest of S1 elements at the end of result
		if (itrS2 == s2.end()) {
			std::copy(itrS1, s1.end(), std::back_inserter(result));
			break;
		}

		auto r1 = *itrS1;
		auto r2 = *itrS2;

		// Comparison of the ranges from the two input sets
		//
		if (r1.second < r2.first) {
			// copy r1 into result
			result.emplace_back(r1);
			itrS1++;
		}
		else if (r2.second < r1.first) {
			// Copy r2 into result
			result.emplace_back(r2);
			itrS2++;
		}
		else {
			// Merge both r1 and r2 into one Range and copy that into result
			auto newRange = std::make_pair(std::min(r1.first, r2.first), std::max(r1.second, r2.second));
			result.emplace_back(newRange);
			itrS1++;
			itrS2++;
		}
	}

	// If any left in the second set, copy them into result
	if (itrS2 != s2.end()) {
		std::copy(itrS2, s2.end(), std::back_inserter(result));
	}

	return result;
}

int main()
{
	// Test Ranget Merge

	// Case 1 [(1, 3), (40, 70), (100, 200) ...] and [(5, 15), (21, 31), (83, 92) ...]
	{
		RangeSet s1 = { std::make_pair(1, 3), std::make_pair(40, 70), std::make_pair(100, 200) };
		RangeSet s2 = { std::make_pair(5, 15), std::make_pair(21, 31), std::make_pair(83, 92) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 2 [(1, 3), (4, 7), (8, 20) ...] and [(50, 150), (210, 310), (830, 920) ...]
	{
		RangeSet s1 = { std::make_pair(1, 3), std::make_pair(4, 7), std::make_pair(8, 20) };
		RangeSet s2 = { std::make_pair(50, 150), std::make_pair(210, 310), std::make_pair(830, 920) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 3 [(10, 30), (40, 70), (80, 200) ...] and [(2, 3), (4, 6), (7, 9) ...]
	{
		RangeSet s1 = { std::make_pair(10, 30), std::make_pair(40, 70), std::make_pair(80, 200) };
		RangeSet s2 = { std::make_pair(2, 3), std::make_pair(4, 6), std::make_pair(7, 9) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 4 [(1, 3), (4000, 7000), (8000, 20000) ...] and [(50, 150), (210, 310), (830, 920) ...]
	{
		RangeSet s1 = { std::make_pair(1, 3), std::make_pair(4000, 7000), std::make_pair(800, 20000) };
		RangeSet s2 = { std::make_pair(50, 150), std::make_pair(210, 310), std::make_pair(830, 920) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 5 [(10, 30), (40, 70), (80, 200) ...] and [(2, 3), (400, 600), (700, 900) ...]
	{
		RangeSet s1 = { std::make_pair(10, 30), std::make_pair(40, 70), std::make_pair(80, 200) };
		RangeSet s2 = { std::make_pair(2, 3), std::make_pair(400, 600), std::make_pair(7, 900) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 6 [(1, 7), (18, 70), (78, 200) ...] and [(5, 15), (21, 31), (83, 92) ...]
	{
		RangeSet s1 = { std::make_pair(1, 7), std::make_pair(18, 70), std::make_pair(78, 200) };
		RangeSet s2 = { std::make_pair(5, 15), std::make_pair(21, 31), std::make_pair(83, 92) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 7 [(1, 3), (40, 70), (80, 200) ...] and [(5, 15), (45, 75), (50, 250) ...]
	{
		RangeSet s1 = { std::make_pair(1, 3), std::make_pair(40, 70), std::make_pair(80, 200) };
		RangeSet s2 = { std::make_pair(5, 15), std::make_pair(45, 75), std::make_pair(50, 250) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 8 [(10, 30), (40, 70), (80, 200) ...] and [(2, 3), (8, 35), (38, 75) ...]
	{
		RangeSet s1 = { std::make_pair(10, 30), std::make_pair(40, 70), std::make_pair(80, 200) };
		RangeSet s2 = { std::make_pair(2, 3), std::make_pair(8, 35), std::make_pair(38, 75) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 9 [(1, 3), (40, 100), (220, 300) ...] and [(50, 150), (210, 310), (830, 920) ...]
	{
		RangeSet s1 = { std::make_pair(1, 3), std::make_pair(40, 100), std::make_pair(220, 300) };
		RangeSet s2 = { std::make_pair(50, 150), std::make_pair(210, 310), std::make_pair(830, 920) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	// Case 10 [(10, 30), (40, 70), (80, 200) ...] and [(11, 28), (38, 72), (88, 198) ...]
	{
		RangeSet s1 = { std::make_pair(10, 30), std::make_pair(40, 70), std::make_pair(80, 200) };
		RangeSet s2 = { std::make_pair(11, 28), std::make_pair(38, 72), std::make_pair(88, 198) };
		auto result = mergeRanges(s1, s2);
		printRangeSet("Merged Set from S1 and S2", result);
	}

	char c;
	std::cin >> c;
}
