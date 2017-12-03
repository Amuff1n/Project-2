#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTLEAF.h"
//#include "BSTROOT.h"
//#include "BSTRAND.h"
//#include "AVL.h"

#include <iostream>

using namespace cop3530;

bool comparison_function(const int a, const int b) {
	if (a < b) {
		return true;
	}
	else {
		return false;
	}
}

bool equals_function(const int a, const int b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

SCENARIO("Testing Insertion and Lookup") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BST_Leaf<int, char, comparison_function, equals_function> * bst = new BST_Leaf<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
		WHEN("Looking up 5") {
			char value = bst->lookup(5);
			THEN ("The value should be 'E' ") {
				REQUIRE(value == 'E');
			}
		}
		
		WHEN("Looking up 9") {
			char value = bst->lookup(9);
			THEN ("The value should be 'I' ") {
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Looking up 1") {
			char value = bst->lookup(1);
			THEN ("The value should be 'A' ") {
				REQUIRE(value == 'A');
			}
		}
		
		WHEN("Looking up 19") {
			char value = bst->lookup(19);
			THEN ("The value should be 'S' ") {
				REQUIRE(value == 'S');
			}
		}
		
		WHEN("Looking up 18") {
			char value = bst->lookup(18);
			THEN ("The value should be 'R' ") {
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Looking up 3") {
			char value = bst->lookup(3);
			THEN ("The value should be 'C' ") {
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Looking up 8") {
			char value = bst->lookup(8);
			THEN ("The value should be 'H' ") {
				REQUIRE(value == 'H');
			}
		}
		
		delete bst;
	}
}

SCENARIO("Testing removal") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BST_Leaf<int, char, comparison_function, equals_function> * bst = new BST_Leaf<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
		WHEN("Removing 1") {
			bst->remove(1);
			THEN("Looking up 1 should throw an exception") {
				bst->lookup(1);
			}
		}
		
		WHEN("Removing 1") {
			bst->remove(1);
			THEN("Looking up 18 should NOT throw an exception") {
				char value = bst->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Removing 18") {
			bst->remove(1);
			THEN("Looking up 9 should NOT throw an exception") {
				char value = bst->lookup(9);
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Removing 9") {
			bst->remove(9);
			THEN("Looking up 9 should throw an exception") {
				char value = bst->lookup(9);
			}
		}
		 
		WHEN("Removing 9") {
			bst->remove(9);
			THEN("Looking up 3 should NOT throw an exception") {
				char value = bst->lookup(3);
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Removing 18") {
			bst->remove(18);
			THEN("Looking up 8 should NOT throw an exception") {
				bst->lookup(8);
			}
		}
		
		WHEN("Removing 19") {
			bst->remove(19);
			THEN("Looking up 18 should NOT throw an exception") {
				bst->lookup(18);
			}
		}
		
		WHEN("Removing all values") {
			bst->remove(1);
			bst->remove(19);
			bst->remove(5);
			bst->remove(18);
			bst->remove(3);
			bst->remove(8);
			bst->remove(9);
			THEN("Looking up anything should throw an exception") {
				bst->lookup(18);
			}
		}
		
		delete bst;
	}
}