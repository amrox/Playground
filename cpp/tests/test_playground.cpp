//
// Created by Andrew Mroczkowski on 12/6/19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>

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


// Write a function template that can take any number of arguments and returns
// the minimum value of them all, using operator < for comparison. Write a
// variant of this function template that can be parameterized with a binary
// comparison function to use instead of operator <.
TEST_CASE("variadic min function")
{
    CHECK(playground::min({1}) == 1);
    CHECK(playground::min({4, 5}) == 4);
    CHECK(playground::min({10, 1, 100}) == 1);
    CHECK(playground::min({1, -5, 0}) == -5);

    // am i doing this right?
    // TODO: can we loose the <int> somehow?
    CHECK(playground::find<int>({1, 2}, [](auto i, auto j) { return i < j; }) == 1);
    CHECK(playground::find<int>({1, 2}, [](auto i, auto j) { return i > j; }) == 2);
}

// Write a set of general-purpose functions that enable checking whether any,
// all, or none of the specified arguments are present in a given container.
// These functions should make it possible to write code as follows:
//     
//    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
//    assert(contains_any(v, 0, 3, 30));
//    
//    std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
//    assert(contains_all(a, 1, 3, 5, 6));
//    
//    std::list<int> l{ 1, 2, 3, 4, 5, 6 };
//    assert(!contains_none(l, 0, 6));
//
TEST_CASE("20. Container any, all, none")
{
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    CHECK(playground::contains_any(v, 3) == true);
    CHECK(playground::contains_any(v, 7) == false);
    CHECK(playground::contains_any(v, 0, 3, 30));

    std::array<int, 6> a{1, 2, 3, 4, 5, 6};
    CHECK(playground::contains_all(a, 1, 3, 5, 6));
}

TEST_CASE("unique_paths")
{
    CHECK(playground::unique_paths(1, 1) == 1);
    CHECK(playground::unique_paths(1, 3) == 1);
    CHECK(playground::unique_paths(3, 1) == 1);
    
    CHECK(playground::unique_paths(2, 2) == 2);
    
    CHECK(playground::unique_paths(2, 3) == 3);
    
    CHECK(playground::unique_paths(3, 3) == 6);
    
    // CHECK(playground::unique_paths(3, 4) == 8);
}

void print_subset_sum_solutions(std::vector<std::vector<int>> const & solutions) {
     std::for_each(solutions.begin(), solutions.end(), [](auto &s ){
        for_each(s.begin(), s.end(), [](auto &i ){
            std::cout << i << " ";
        });
        std::cout << std::endl;
    });
}

TEST_CASE("subset_sum")
{
    std::vector<int> nums1 {2, 3, 5, 7, 1, 1};
    std::vector<int> nums2 {2, 3, 5, 7, 1, 1,
                            2, 3, 5, 7, 1, 1,
                            2, 3, 5, 7, 1, 1,
                            2, 3, 5, 7, 1, 1,
                            4, 8, 10

                            };

    // auto r1 = playground::subset_sum(nums1, 10);
    // print_subset_sum_solutions(r1);
    
    // auto r2 = playground::subset_sum_2(nums1, 10);
    // print_subset_sum_solutions(r2);
    
    // auto r3 = playground::subset_sum_3(nums1, 10);
    // print_subset_sum_solutions(r3);
    
    // auto r4 = playground::subset_sum_4(nums1, 10, 1);
    // print_subset_sum_solutions(r4);

    // auto r5 = playground::subset_sum_4(nums2, 15, 1);
    // print_subset_sum_solutions(r5);
    
    auto r6 = playground::subset_sum_4(nums2, 15, 12);
    print_subset_sum_solutions(r6);
}