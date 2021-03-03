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


#include "eng_numerals_pib1e9.hpp"

#include <sstream>
#include <regex>
#include <cstdint>
#include <unordered_map>

namespace {

    std::string string_ascii_tolower(std::string s) {
        // Generally, in C++, we can't assume a sane text codec (UTF-8, ASCII compatible)
        // but we assume so in this case, as we are dealing with english only.
        // I think, in this case, it is better not to use tolower() to avoid 
        // locale hell.
        std::transform(s.begin(), s.end(), s.begin(), [](char c)->char { 
            if (c <= 'Z' && c >= 'A') {
                return c - ('Z' - 'z');
            }
            else {
                return c;
            }
        });
        return s;
    }

    std::uint_fast32_t parse_pib1e9(const std::string& s) {
        const std::unordered_map<std::string, uint_fast32_t> value_map{
            { "one", 1 },
            { "two", 2 },
            { "three", 3 },
            { "four", 4 },
            { "five", 5 },
            { "six", 6 },
            { "seven", 7 },
            { "eight", 8 },
            { "nine", 9 },
            { "ten", 10 },
            { "eleven", 11 },
            { "twelve", 12 },
            { "thirteen", 13 },
            { "fourteen", 14 },
            { "fifteen", 15 },
            { "sixteen", 16 },
            { "seventeen", 17 },
            { "eighteen", 18 },
            { "nineteen", 19 },
            { "twenty", 20 },
        };
        return value_map.at(string_ascii_tolower(s));
    }
}

namespace eng_numerals_pib1e9 {

    std::string convert_to_digits(const std::string& input_string) {
        std::istringstream input(input_string);
        std::ostringstream output;
        convert_to_digits(input,output);
        return output.str();
    }

    void convert_to_digits(std::istream& input, std::ostream& output) {
        const std::regex units_regex(
            // NOTE: order is important, preceding disjuntions have priority
            // and there some with the same prefix
            "ten|eleven|twelve|thirteen|fourteen|fifteen"
            "|sixteen|seventeen|eighteen|nineteen|twenty"
            "|one|two|three|four|five|six|seven|eight|nine",
            std::regex::icase|std::regex::optimize
        );
        for (std::string p; std::getline(input, p);) {

            std::string suffix;
            std::for_each(std::sregex_iterator(p.begin(), p.end(), units_regex), std::sregex_iterator(), 
                [&](std::sregex_iterator::reference match){
                    output << match.prefix();
                    output << parse_pib1e9(match.str());
                    suffix = match.suffix().str();
                }
            );

            output << suffix;
            if (!input.eof()) {
                output << std::endl;
            }
        }
    }
}
