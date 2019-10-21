/*
    0-1 Knapsack Problem
    --------------------
    Given weights and values of n items, put these items in a knapsack
    of a fixed capacity to get the maximum total value in the knapsack.

    Time complexity
    ---------------
    O(N*W), where N is the number of items and W is the capacity of the knapsack.

    Space complexity
    ----------------
    O(N*W), the variables same as time complexity.

    Author
    ------
    Fedurko Nikolaus (@B1Z0N)
*/


#include "knapsack.hpp"

#include <iostream>	// cin, cout
#include <vector>	// vector


std::ostream& operator<<( std::ostream& os, Knapsack& knp )
{
	return os << knp();
}


std::istream& operator>>( std::istream& is, Knapsack& knp )
{
	is >> knp.capacity;

	std::size_t n, value, weight;
	is >> n;

	while( n-- )
	{
		is >> value >> weight;

		knp.values.push_back(value);
		knp.weights.push_back(weight);
	}

	return is;
}	


/**
 * Algorithm implementation
 */
std::size_t Knapsack::solve()
{
	std::size_t size { values.size( ) };
	std::size_t remember[ size + 1 ][ capacity + 1 ];
	/**
	 * A row number i represents the set of all the items 
	 * from rows 1 to i. For instance, the values in row 3 assumes 
	 * that we only have items 1, 2, and 3.
	 *
	 * A column number j represents the weight capacity of our knapsack. 
	 * Therefore, the values in column 5, for example, assumes that our 
	 * knapsack can hold 5 weight units.
	 *
	 * Putting everything together, an entry in row i, column j represents 
	 * the maximum value that can be obtained with items 1, 2, 3 … i, in a 
	 * knapsack that can hold j weight units.
	 */

	for( int i = 0; i <= size; ++i )
	{
		for( int w = 0; w <= capacity; ++w )
		{
			if( i == 0 || w == 0 )
				// base case 
				remember[ i ][ w ] = 0;
			else if( weights[ i - 1 ] <= w )
				remember[ i ][ w ] = std::max( 
					values[ i - 1 ] + remember[ i - 1 ][ w - weights[ i - 1 ] ],	
					// include this item
					remember[ i - 1 ][ w ]	// or
					// don't include
				);
			else
				remember[ i ][ w ] = remember[ i - 1 ][ w ];
		}
	}

	return remember[ size ][ capacity ];
}