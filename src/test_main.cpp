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

TEST_CASE("without any number word") {
    REQUIRE( enp1e9::convert_to_digits("this is a test") == std::string("this is a test") );
    REQUIRE( enp1e9::convert_to_digits("prefixseven") == std::string("prefixseven") );
    REQUIRE( enp1e9::convert_to_digits("prefixten") == std::string("prefixten") );
    REQUIRE( enp1e9::convert_to_digits("sevensufix") == std::string("sevensufix") );
    REQUIRE( enp1e9::convert_to_digits("tensufix") == std::string("tensufix") );
    REQUIRE( enp1e9::convert_to_digits("tens") == std::string("tens") );
    REQUIRE( enp1e9::convert_to_digits("hundreds") == std::string("hundreds") );
    REQUIRE( enp1e9::convert_to_digits("thousands") == std::string("thousands") );
    REQUIRE( enp1e9::convert_to_digits("millions") == std::string("millions") );
    REQUIRE( enp1e9::convert_to_digits("billions") == std::string("billions") );
    REQUIRE( enp1e9::convert_to_digits("hundred") == std::string("hundred") );
    REQUIRE( enp1e9::convert_to_digits("thousand") == std::string("thousand") );
    REQUIRE( enp1e9::convert_to_digits("million") == std::string("million") );
    REQUIRE( enp1e9::convert_to_digits("billion") == std::string("billion") );
}

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

TEST_CASE("twenties to nineties") {
    REQUIRE( enp1e9::convert_to_digits("twenty") == std::string("20") );
    REQUIRE( enp1e9::convert_to_digits("twenty one") == std::string("21") );
    REQUIRE( enp1e9::convert_to_digits("twenty-nine") == std::string("29") );
    REQUIRE( enp1e9::convert_to_digits("-twenty-nine") == std::string("-29") );
    REQUIRE( enp1e9::convert_to_digits("twenty-nine-") == std::string("29-") );
    REQUIRE( enp1e9::convert_to_digits("thirty") == std::string("30") );
    REQUIRE( enp1e9::convert_to_digits("fourty one") == std::string("41") );
    REQUIRE( enp1e9::convert_to_digits("fifty three thirty five") == std::string("53 35") );
    REQUIRE( enp1e9::convert_to_digits("sixty-seven") == std::string("67") );
    REQUIRE( enp1e9::convert_to_digits("-seventy-nine") == std::string("-79") );
    REQUIRE( enp1e9::convert_to_digits("ninety-nine-") == std::string("99-") );
}

TEST_CASE("four digits hundreds") {
    REQUIRE( enp1e9::convert_to_digits("fifty hundred") == std::string("5000") );
    REQUIRE( enp1e9::convert_to_digits("fifteen hundred thirty two") == std::string("1532") );
    REQUIRE( enp1e9::convert_to_digits("fifteen hundred and thirty two") == std::string("1532") );
    REQUIRE( enp1e9::convert_to_digits("twelve fifteen hundred thirty two") == std::string("12 1532") );
}

TEST_CASE("hundreds") {
    REQUIRE( enp1e9::convert_to_digits("five hundred") == std::string("500") );
    REQUIRE( enp1e9::convert_to_digits("six hundred thirty two") == std::string("632") );
    REQUIRE( enp1e9::convert_to_digits("twelve two hundred thirty two") == std::string("12 232") );
    REQUIRE( enp1e9::convert_to_digits("a hundred thirty two") == std::string("132") );
    REQUIRE( enp1e9::convert_to_digits("one hundred thirty two") == std::string("132") );
    REQUIRE( enp1e9::convert_to_digits("one hundred, two hundred") == std::string("100, 200") );
}

TEST_CASE("thousands") {
    REQUIRE( enp1e9::convert_to_digits("a thousand") == std::string("1000") );
    REQUIRE( enp1e9::convert_to_digits("one thousand") == std::string("1000") );
    REQUIRE( enp1e9::convert_to_digits("two thousand") == std::string("2000") );
    REQUIRE( enp1e9::convert_to_digits("six hundred fifty four thousand three hundred twenty one") == std::string("654321") );
    REQUIRE( enp1e9::convert_to_digits("two thousand one hundred thirty two") == std::string("2132") );
    REQUIRE( enp1e9::convert_to_digits("two thousand, one hundred thirty two") == std::string("2132") );
    REQUIRE( enp1e9::convert_to_digits("two thousand, one hundred and thirty two") == std::string("2132") );
    REQUIRE( enp1e9::convert_to_digits("two thousand one hundred and thirty two") == std::string("2132") );
    REQUIRE( enp1e9::convert_to_digits("one hundred thirty two thousand two") == std::string("132002") );
    REQUIRE( enp1e9::convert_to_digits("a thousand thirty two") == std::string("1032") );
    REQUIRE( enp1e9::convert_to_digits("one thousand thirty two") == std::string("1032") );
}

TEST_CASE("millions") {
    REQUIRE( enp1e9::convert_to_digits("a million") == std::string("1000000") );
    REQUIRE( enp1e9::convert_to_digits("a hundred million") == std::string("100000000") );
    REQUIRE( enp1e9::convert_to_digits("a hundred million and two") == std::string("100000002") );
    REQUIRE( enp1e9::convert_to_digits("one million") == std::string("1000000") );
    REQUIRE( enp1e9::convert_to_digits("two million") == std::string("2000000") );
    REQUIRE( enp1e9::convert_to_digits("nine hundred eighty seven million six hundred fifty four thousand three hundred twenty one") == std::string("987654321") );
    REQUIRE( enp1e9::convert_to_digits("a hundred eighty seven million six hundred fifty four thousand three hundred twenty one") == std::string("187654321") );
}

TEST_CASE("billion") {
    REQUIRE( enp1e9::convert_to_digits("a billion") == std::string("1000000000") );
    REQUIRE( enp1e9::convert_to_digits("one billion") == std::string("1000000000") );
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
