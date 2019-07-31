#include "knapsack.hpp"

#include <iostream>
#include <cassert>
#include <vector>

void test_knapsack( std::size_t capacity,
		    const std::vector<std::size_t>& values, 
		    const std::vector<std::size_t>& weights, 
		    std::size_t answer )
{
	assert( ( Knapsack { capacity, values, weights } )() == answer );
}

int main()
{
	// Base cases
	test_knapsack( 10, { 60 }, { 10 }, 60 );
	test_knapsack( 5, { 60 }, { 10 }, 0 );

	// Simple cases
	test_knapsack( 50, { 60, 100, 120 }, { 10, 20, 30 }, 220 );
	test_knapsack( 75, { 25, 31, 15, 25, 4 }, { 43, 67, 25, 12, 36 }, 50 );

	// Medium cases
	test_knapsack( 22, { 17, 32, 33, 30, 10, 4, 21, 40, 42, 5, 29, 27, 10, 35, 
					 34, 33, 49, 47, 47, 28, 27, 5, 38, 47, 8, 9, 19,  10, 
					 6, 45, 10, 23, 31, 32, 14, 17, 31, 45, 21, 39, 19, 7,
					 36, 19, 44, 27, 20, 39, 45, 18 }, 
				   { 25, 35, 43, 33, 6, 23, 3, 5, 42, 45, 19, 21, 27,   2, 
				   	 11, 2, 6, 29, 32, 36, 21, 41, 37, 29, 15, 30, 19, 34, 
				   	 1, 12, 31, 20, 44, 37, 1, 17, 18, 34, 22, 23, 2,   3, 
				   	 30, 1, 7, 24, 39, 33, 14, 1 }, 235 );

	std::cout << "All tests passed!\n";

	return 0;
}
