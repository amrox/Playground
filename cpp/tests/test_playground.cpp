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

// The Modern C++ Challenge 1
TEST_CASE("Write a program that calculates and prints the sum of all the natural numbers divisible by either 3 or 5, up to a given limit entered by the user.")
{
    CHECK( playground::sum_div_by_3_or_5(3) == 3 );
    CHECK( playground::sum_div_by_3_or_5(5) == 8 );
    CHECK( playground::sum_div_by_3_or_5(10) == 33 );
    
    CHECK( playground::sum_div_by_3_or_5_stl(3) == 3 );
    CHECK( playground::sum_div_by_3_or_5_stl(5) == 8 );
    CHECK( playground::sum_div_by_3_or_5_stl(10) == 33 );
}


// The Modern C++ Challenge 2
TEST_CASE("Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two.")
{
    CHECK( playground::gcd(105, 50) == 5 );
}

// The Modern C++ Challenge 14
TEST_CASE("Write a program that validates that 10-digit values entered by the user, as a string, represent valid ISBN-10 numbers.")
{
    // TODO:
}

// Write a class that represents an IPv4 address. Implement the functions
// required to be able to read and write such addresses from or to the console.
// The user should be able to input values in dotted form, such as 127.0.0.1 or
// 168.192.0.100. This is also the form in which IPv4 addresses should be
// formatted to an output stream.
TEST_CASE("IPv4 data type")
{
    CHECK((playground::IPV4(127, 0, 0, 1)).to_string() == "127.0.0.1");

    playground::IPV4 ip1 { 192, 168, 10, 5 };
    playground::IPV4 ip2 { ip1 };
    CHECK(ip2.to_string() == "192.168.10.5");

    CHECK(playground::IPV4::from_string("pizza!") == std::nullopt);
    
    CHECK(playground::IPV4::from_string("1.1.1.1.1") == std::nullopt);
    CHECK(playground::IPV4::from_string("1000.1.1.1") == std::nullopt);
    CHECK(playground::IPV4::from_string("1.1.1") == std::nullopt);
    
    CHECK(playground::IPV4::from_string("10.254.3.100") == playground::IPV4 { 10, 254, 3, 100 });
}
