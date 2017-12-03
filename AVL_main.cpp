#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AVL.h"

#include <iostream>

//height can vary in AVL tree by because abs(balance) <=1
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
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Looking up 5") {
			char value = avl->lookup(5);
			THEN ("The value should be 'E' ") {
				REQUIRE(value == 'E');
			}
		}
		
		WHEN("Looking up 9") {
			char value = avl->lookup(9);
			THEN ("The value should be 'I' ") {
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Looking up 1") {
			char value = avl->lookup(1);
			THEN ("The value should be 'A' ") {
				REQUIRE(value == 'A');
			}
		}
		
		WHEN("Looking up 19") {
			char value = avl->lookup(19);
			THEN ("The value should be 'S' ") {
				REQUIRE(value == 'S');
			}
		}
		
		WHEN("Looking up 18") {
			char value = avl->lookup(18);
			THEN ("The value should be 'R' ") {
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Looking up 3") {
			char value = avl->lookup(3);
			THEN ("The value should be 'C' ") {
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Looking up 8") {
			char value = avl->lookup(8);
			THEN ("The value should be 'H' ") {
				REQUIRE(value == 'H');
			}
		}
		
		delete avl;
	}
}
/*
SCENARIO("Testing removal") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Removing 1") {
			avl->remove(1);
			THEN("Looking up 18 should NOT throw an exception") {
				char value = avl->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Removing 18") {
			avl->remove(1);
			THEN("Looking up 9 should NOT throw an exception") {
				char value = avl->lookup(9);
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Removing 9") {
			avl->remove(9);
			THEN("Looking up 3 should NOT throw an exception") {
				char value = avl->lookup(3);
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Removing 18") {
			avl->remove(18);
			THEN("Looking up 8 should NOT throw an exception") {
				avl->lookup(8);
			}
		}
		
		WHEN("Removing 19") {
			avl->remove(19);
			THEN("Looking up 18 should NOT throw an exception") {
				avl->lookup(18);
			}
		}
		
		delete avl;
	}
}
*/
SCENARIO("Testing bonus methods") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Checking contains for 8") {
			bool x = avl->contains(8);
			THEN("Contains should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking contains for 22") {
			bool x = avl->contains(22);
			THEN("Contains should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking is_empty") {
			bool x = avl->is_empty();
			THEN("Is_empty should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Clearing and checking is_empty") {
			avl->clear();
			bool x = avl->is_empty();
			THEN("Is_empty should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking is_full") {
			bool x = avl->is_full();
			THEN("Is_full should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking size") {
			size_t size = avl->size();
			THEN("The size should be 7 (there are 7 items)") {
				REQUIRE(size == 7);
			}
		}
		
		WHEN("Checking height") {
			size_t height = avl->height();
			THEN("Height should be 3 or 4") {
				REQUIRE(height >= 3);
				REQUIRE(height <= 4);
			}
		}
		
		WHEN("Checking balance") {
			int balance = avl->balance();
			THEN("Balance should have absolute value <= 1") {
				REQUIRE(abs(balance) <= 1);
			}
		}
		
		delete avl;
	}
}

SCENARIO("Testing 'big five' methods") {
	GIVEN("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Testing copy constructor") {
			AVL<int, char, comparison_function, equals_function> * avl2 = avl;
			THEN("New copy should successfully lookup 18") {
				char value = avl2->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Testing copy assignment") {
			AVL<int, char, comparison_function, equals_function> * avl2 = new AVL<int, char, comparison_function, equals_function>;
			//throw in values different from other to ensure assignment works
			avl2->insert(4,'D');
			avl2->insert(2,'B');
			avl2->insert(26,'Z');
			
			avl2 = avl;
			THEN("New copy should succesfully lookup 18") {
				char value = avl2->lookup(18);
				REQUIRE(value == 'R');
			}
			
			delete avl2;
		}
		
		
		delete avl;
	}
}
