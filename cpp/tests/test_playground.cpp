//
// Created by Andrew Mroczkowski on 12/6/19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "playground.h"

TEST_CASE( "Find the kth smallest value in a list", "[]" ) {

    // Empty vector should always fail
    CHECK_FALSE( playground::kth(std::vector<int>{}, 1).has_value() );

    // kth above range
    CHECK_FALSE( playground::kth(std::vector{ 1 }, 5).has_value() );

    // kth less than 1 
    CHECK_FALSE( playground::kth(std::vector{ 1 }, -1).has_value() );
    
    CHECK( playground::kth(std::vector{ 5, 6 }, 1) == 5 );
    CHECK( playground::kth(std::vector{ 10.5, 12.5 }, 1) == 10.5 );

    CHECK( playground::kth(std::vector{ 9, 6, 12, 3 }, 1).value() == 3 );
    CHECK( playground::kth(std::vector{ 9, 6, 12, 3 }, 2).value() == 6 );
    CHECK( playground::kth(std::vector{ 9, 6, 12, 3 }, 3).value() == 9 );
    CHECK( playground::kth(std::vector{ 9, 6, 12, 3 }, 4).value() == 12 );
}