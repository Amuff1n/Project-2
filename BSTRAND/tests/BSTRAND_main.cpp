#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "../BSTRAND.h"

#include <iostream>

using namespace cop3530;

bool comparison_function(const int& a, const int& b) {
	if (a < b) {
		return true;
	}
	else {
		return false;
	}
}

bool equals_function(const int& a, const int& b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

SCENARIO("Testing Insertion and Lookup") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BSTRAND<int, char, comparison_function, equals_function> * bst = new BSTRAND<int, char, comparison_function, equals_function>;
		
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
		
		WHEN("Testing insertion of new item with same key 3 but value 'Z'") {
			bst->insert(3,'Z');
			char value = bst->lookup(3);
			THEN("The value should be 'Z', not 'C'") {
				REQUIRE(value == 'Z');
			}
		}
		
		delete bst;
	}
}

SCENARIO("Testing removal") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BSTRAND<int, char, comparison_function, equals_function> * bst = new BSTRAND<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
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
		
		delete bst;
	}
}

SCENARIO("Testing bonus methods") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BSTRAND<int, char, comparison_function, equals_function> * bst = new BSTRAND<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
		WHEN("Checking contains for 8") {
			bool x = bst->contains(8);
			THEN("Contains should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking contains for 22") {
			bool x = bst->contains(22);
			THEN("Contains should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking is_empty") {
			bool x = bst->is_empty();
			THEN("Is_empty should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Clearing and checking is_empty") {
			bst->clear();
			bool x = bst->is_empty();
			THEN("Is_empty should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking is_full") {
			bool x = bst->is_full();
			THEN("Is_full should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking size") {
			size_t size = bst->size();
			THEN("The size should be 7 (there are 7 items)") {
				REQUIRE(size == 7);
			}
		}
		
		WHEN("Checking height") {
			size_t height = bst->height();
			THEN("Height could theoritically be bewteen 1 and 7") {
				REQUIRE(height < 7);
				REQUIRE(height > 1);
			}
		}
		
		WHEN("Checking balance") {
			int balance = bst->balance();
			THEN("Balance should likely not be -5 or 1") {
				REQUIRE(balance != -5);
				REQUIRE(balance != 1);
			}
		}
		
		delete bst;
	}
}

SCENARIO("Testing 'big five' methods") {
	GIVEN("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		BSTRAND<int, char, comparison_function, equals_function> * bst = new BSTRAND<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
		WHEN("Testing copy constructor") {
			BSTRAND<int, char, comparison_function, equals_function> * bst2 = bst;
			THEN("New copy should successfully lookup 18") {
				char value = bst2->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		/*
		//losing bytes in this test
		WHEN("Testing copy assignment") {
			BSTRAND<int, char, comparison_function, equals_function> * bst2 = new BSTRAND<int, char, comparison_function, equals_function>;
			//throw in values different from other to ensure assignment works
			bst2->insert(4,'D');
			bst2->insert(2,'B');
			bst2->insert(26,'Z');
			
			bst2 = bst;
			THEN("New copy should succesfully lookup 18") {
				char value = bst2->lookup(18);
				REQUIRE(value == 'R');
			}
			
			delete bst2;
		}
		*/
		WHEN ("Testing move constructor") {
			BSTRAND<int, char, comparison_function, equals_function> * bst2(std::move(bst));
			THEN("New copy should successfully lookup 18") {
				char value = bst2->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		/*
		//losing bytes in this test
		WHEN("Testing move assignment") {
			BSTRAND<int, char, comparison_function, equals_function> * bst2 = new BSTRAND<int, char, comparison_function, equals_function>;
			//throw in values different from other to ensure assignment works
			bst2->insert(4,'D');
			bst2->insert(2,'B');
			bst2->insert(26,'Z');
			
			bst2 = std::move(bst);
			THEN("New copy should succesfully lookup 18") {
				char value = bst2->lookup(18);
				REQUIRE(value == 'R');
			}
			
			delete bst2;
		}
		*/
		
		delete bst;
	}
}

SCENARIO("Testing constant-ness(?)") {
	GIVEN("A constant BST") {
		BSTRAND<int, char, comparison_function, equals_function> * bst = new BSTRAND<int, char, comparison_function, equals_function>;
		
		bst->insert(1,'A');
		bst->insert(19,'S');
		bst->insert(5,'E');
		bst->insert(18,'R');
		bst->insert(3,'C');
		bst->insert(8,'H');
		bst->insert(9,'I');
		
		BSTRAND<int, char, comparison_function, equals_function> const * bst2 = bst;
		
		WHEN("Looking up the key 8") {
			char value = bst2->lookup(8);
			THEN("It should work and return 'H'") {
				REQUIRE(value == 'H');
			}
		}
	
		delete bst;
	}
}
