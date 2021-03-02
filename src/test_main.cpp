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

std::string fail_test(const std::string& s) {
    return std::string{""};
}
TEST_CASE("one to twenty","[]") {
    REQUIRE( fail_test("one") == std::string("1") );
    REQUIRE( fail_test("two") == std::string("2") );
    REQUIRE( fail_test("three") == std::string("3") );
    REQUIRE( fail_test("four") == std::string("4") );
    REQUIRE( fail_test("five") == std::string("5") );
    REQUIRE( fail_test("six") ==  std::string("6") );
    REQUIRE( fail_test("seven") == std::string("7") );
    REQUIRE( fail_test("eight") == std::string("8") );
    REQUIRE( fail_test("nine") == std::string("9") );

    REQUIRE( fail_test("ten") == std::string("10") );
    REQUIRE( fail_test("eleven") == std::string("11") );
    REQUIRE( fail_test("twelve") ==  std::string("12") );
    REQUIRE( fail_test("thirteen") ==  std::string("13") );
    REQUIRE( fail_test("fourteen") ==  std::string("14") );
    REQUIRE( fail_test("fifteen") ==  std::string("15") );
    REQUIRE( fail_test("sixteen") ==  std::string("16") );
    REQUIRE( fail_test("seventeen") ==  std::string("17") );
    REQUIRE( fail_test("eighteen") ==  std::string("18") );
    REQUIRE( fail_test("nineteen") ==  std::string("19") );

    REQUIRE( fail_test("tweenty") ==  std::string("20") );
}