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

    const std::string SPACES = "\\s+";
    const std::string HYPHEN = "-";
    const std::string SPACES_OR_HYPHEN = "(?:"+SPACES+"|"+HYPHEN+")";

    const std::string ONE = "one";
    const std::string TWO = "two";
    const std::string THREE = "three";
    const std::string FOUR = "four";
    const std::string FIVE = "five";
    const std::string SIX = "six";
    const std::string SEVEN = "seven";
    const std::string EIGHT = "eight";
    const std::string NINE = "nine";
    const std::string TEN = "ten";
    const std::string ELEVEN = "eleven";
    const std::string TWELVE = "twelve";
    const std::string THIRTEEN = "thirteen";
    const std::string FOURTEEN = "fourteen";
    const std::string FIFTEEN = "fifteen";
    const std::string SIXTEEN = "sixteen";
    const std::string SEVENTEEN = "seventeen";
    const std::string EIGHTEEN = "eighteen";
    const std::string NINETEEN = "nineteen";
    const std::string TWENTY = "twenty";

    const std::string BELOW_TEN = 
        ONE+"|"+TWO+"|"+THREE+"|"+FOUR+"|"+FIVE+"|"+SIX+"|"+SEVEN+"|"+EIGHT+"|"+NINE;

    const std::string TENS = 
        TEN+"|"+ELEVEN+"|"+TWELVE+"|"+THIRTEEN+"|"+FOURTEEN+"|"+FIFTEEN+"|"+
        SIXTEEN+"|"+SEVENTEEN+"|"+EIGHTEEN+"|"+NINETEEN;

    const std::string TWENTIES = 
        TWENTY + HYPHEN + "(?:" + BELOW_TEN + ")|" +
        TWENTY + SPACES + "(?:" + BELOW_TEN + ")|" +
        TWENTY;

    std::uint_fast32_t parse_pib1e9(const std::string& input_str) {
        const std::unordered_map<std::string, uint_fast32_t> value_map{
            { ONE, 1 },
            { TWO, 2 },
            { THREE, 3 },
            { FOUR, 4 },
            { FIVE, 5 },
            { SIX, 6 },
            { SEVEN, 7 },
            { EIGHT, 8 },
            { NINE, 9 },
            { TEN, 10 },
            { ELEVEN, 11 },
            { TWELVE, 12 },
            { THIRTEEN, 13 },
            { FOURTEEN, 14 },
            { FIFTEEN, 15 },
            { SIXTEEN, 16 },
            { SEVENTEEN, 17 },
            { EIGHTEEN, 18 },
            { NINETEEN, 19 },
            { TWENTY, 20 },
        };

        uint_fast32_t value = 0;

        std::string s = string_ascii_tolower(input_str);
        std::regex negative_regex(SPACES_OR_HYPHEN);
        std::for_each(std::sregex_token_iterator(s.begin(), s.end(), negative_regex, -1), std::sregex_token_iterator(), 
            [&](std::sregex_token_iterator::reference match){
                value += value_map.at(match.str());
            }
        );

        return value;
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

        const std::regex numeral_regex(
            // NOTE: order is important, preceding disjuntions have priority
            // and there some with the same prefix
            TWENTIES+"|"+TENS+"|"+BELOW_TEN,
            std::regex::icase|std::regex::optimize
        );
        for (std::string p; std::getline(input, p);) {

            std::string suffix;
            std::for_each(std::sregex_iterator(p.begin(), p.end(), numeral_regex), std::sregex_iterator(), 
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
