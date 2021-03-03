// Copyright 2021  Israel Basurto
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

#include "eng_numerals_pib1e9.hpp"

namespace enp1e9 = eng_numerals_pib1e9;

TEST_CASE("one to twenty") {
    REQUIRE( enp1e9::convert_to_digits("one") == std::string("1") );
    REQUIRE( enp1e9::convert_to_digits("two") == std::string("2") );
    REQUIRE( enp1e9::convert_to_digits("three") == std::string("3") );
    REQUIRE( enp1e9::convert_to_digits("four") == std::string("4") );
    REQUIRE( enp1e9::convert_to_digits("five") == std::string("5") );
    REQUIRE( enp1e9::convert_to_digits("six") ==  std::string("6") );
    REQUIRE( enp1e9::convert_to_digits("seven") == std::string("7") );
    REQUIRE( enp1e9::convert_to_digits("eight") == std::string("8") );
    REQUIRE( enp1e9::convert_to_digits("nine") == std::string("9") );

    REQUIRE( enp1e9::convert_to_digits("ten") == std::string("10") );
    REQUIRE( enp1e9::convert_to_digits("eleven") == std::string("11") );
    REQUIRE( enp1e9::convert_to_digits("twelve") == std::string("12") );
    REQUIRE( enp1e9::convert_to_digits("thirteen") == std::string("13") );
    REQUIRE( enp1e9::convert_to_digits("fourteen") == std::string("14") );
    REQUIRE( enp1e9::convert_to_digits("fifteen") == std::string("15") );
    REQUIRE( enp1e9::convert_to_digits("sixteen") == std::string("16") );
    REQUIRE( enp1e9::convert_to_digits("seventeen") == std::string("17") );
    REQUIRE( enp1e9::convert_to_digits("eighteen") == std::string("18") );
    REQUIRE( enp1e9::convert_to_digits("nineteen") == std::string("19") );

    REQUIRE( enp1e9::convert_to_digits("twenty") == std::string("20") );
}

TEST_CASE("one test two lines") {
    const auto input = "this is one test\nwith two lines\n";
    const auto output = "this is 1 test\nwith 2 lines\n";

    REQUIRE( enp1e9::convert_to_digits(input) == std::string(output) );
}

TEST_CASE("upper and lower case") {
    const auto input = "this is One test\nwith tWO lines\n";
    const auto output = "this is 1 test\nwith 2 lines\n";
    
    REQUIRE( enp1e9::convert_to_digits(input) == std::string(output) );
}

TEST_CASE("three lines") {
    const auto input =
        "this are some numbers: one, two, three,\n"
        "(continuation) four, five,\n"
        "and ten (the end)";
    const auto output =
        "this are some numbers: 1, 2, 3,\n"
        "(continuation) 4, 5,\n"
        "and 10 (the end)";
    
    REQUIRE( enp1e9::convert_to_digits(input) == std::string(output) );
}
