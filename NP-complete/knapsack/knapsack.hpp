#include <iostream>	// cin, cout
#include <vector>	// vector


// @Problem
// Given a set of items, each with a weight and a value, 
// determine the number of each item to include in a collection 
// so that the total weight is less than or equal to a given limit 
// and the total value is as large as possible. 
//
// @Example
//
// ╔════════╦════╦═════╦═════╗
// ║ value  ║ 60 ║ 100 ║ 120 ║
// ╠════════╬════╬═════╬═════╣
// ║ weight ║ 10 ║  20 ║  30 ║
// ╚════════╩════╩═════╩═════╝
// MAXW = 50
// 
// Weight = 10; Value = 60;
// Weight = 20; Value = 100;
// Weight = 30; Value = 120;
// Weight = 10 + 20; Value = 160;
// Weight = 10 + 30; Value = 180;
// Weight = 20 + 30; Value = 220;
// Weight = 30 + 20 + 10 > 50
//
// Answer: 220;
//
// @Input format
// 50 
// 3
// 60 10 100 20 120 30
//
// @Output format
// 220

#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP


/**
 * 0-1 knapsack solution class
 */
class Knapsack
{
	using size_t = std::size_t;

	size_t capacity;
	std::vector<size_t> values ;
	std::vector<size_t> weights;

	bool calculated { false };
	size_t result;

public:

	Knapsack() = default;
	Knapsack( size_t capacity, const std::vector<size_t>& values, const std::vector<size_t>& weights)
	: capacity{ capacity }, values{ values }, weights{ weights } { } 

	size_t get_capacity() { return capacity; }
	std::vector<size_t> get_values () { return values ; }
	std::vector<size_t> get_weights() { return weights; }

	/**
	 * Solved only first time, for others just use saved value
	 */
	size_t operator()() 
	{
		return calculated ? result : calculated = true, solve();
	}

	friend std::ostream& operator<<( std::ostream& os, Knapsack& knp );
	friend std::istream& operator>>( std::istream& is, Knapsack& knp );	

private:

	/**
	 * Algorithm implementation
	 */
	size_t solve();
};


#endif	// KNAPSACK_HPP