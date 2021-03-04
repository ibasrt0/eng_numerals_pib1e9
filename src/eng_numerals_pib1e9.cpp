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

    // ancilliary function to mark a whole word in regex
    inline std::string wholeword(std::string s) {
        return "\\b"+s+"\\b"; 
    }

    ///////////////////////////////////////////////////////////////

    // scaffolding to define a regex expresion to search and validate number in words

    const std::string SPACES = "\\s+";
    const std::string HYPHEN = "-"; // only one hyphen
    const std::string SPACES_OR_HYPHEN = "(?:"+SPACES+"|"+HYPHEN+")";
    const std::string SPACES_OR_AND = "(?:"+SPACES+"|"+SPACES+"and"+SPACES+")";
    const std::string SPACES_OR_COMMA_OR_AND = "(?:"+SPACES+"|,"+SPACES+"|"+SPACES+"and"+SPACES+")";

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
    const std::string THIRTY = "thirty";
    const std::string FOURTY = "fourty";
    const std::string FIFTY = "fifty";
    const std::string SIXTY = "sixty";
    const std::string SEVENTY = "seventy";
    const std::string EIGHTY = "eighty";
    const std::string NINETY = "ninety";
    const std::string HUNDRED = "hundred";
    const std::string THOUSAND = "thousand";
    const std::string MILLION = "million";
    const std::string BILLION = "billion"; // short scale

    const std::string BELOW_TEN = 
        "(?:"+wholeword(ONE)+"|"+wholeword(TWO)+"|"+wholeword(THREE)+"|"+
        wholeword(FOUR)+"|"+wholeword(FIVE)+"|"+wholeword(SIX)+"|"+
        wholeword(SEVEN)+"\\b|"+wholeword(EIGHT)+"|"+wholeword(NINE)+")";

    const std::string TENS = 
        "(?:"+wholeword(TEN)+"|"+wholeword(ELEVEN)+"|"+wholeword(TWELVE)+"|"+
        wholeword(THIRTEEN)+"|"+wholeword(FOURTEEN)+"|"+wholeword(FIFTEEN)+"|"+
        wholeword(SIXTEEN)+"|"+wholeword(SEVENTEEN)+"|"+wholeword(EIGHTEEN)+"|"+
        wholeword(NINETEEN)+")";

    const std::string TWENTIES_TO_NINETY =
        "(?:" + wholeword(TWENTY) +"|"+ wholeword(THIRTY) +"|"+
        wholeword(FOURTY) +"|"+ wholeword(FIFTY) +"|"+
        wholeword(SIXTY) +"|"+ wholeword(SEVENTY) +"|"+
        wholeword(EIGHTY) +"|"+ wholeword(NINETY) +")";

    const std::string TWENTIES_TO_NINETIES =
        "(?:" + TWENTIES_TO_NINETY + 
            "(?:" + HYPHEN + BELOW_TEN + "|" + SPACES + BELOW_TEN + ")?"
        ")";

    const std::string BELOW_HUNDRED =
        "(?:"+TWENTIES_TO_NINETIES+"|"+TENS+"|"+BELOW_TEN+")";

    // fifteen hundred -> 1500
    // NOTE: this is only for final numbers, not part of a thousand or million
    const std::string FOUR_DIGITS_HUNDREDS =
        "(?:" + BELOW_HUNDRED + SPACES + HUNDRED + "(?:" + SPACES_OR_AND + BELOW_HUNDRED + ")?)";

    const std::string REGULAR_HUNDREDS =
        "(?:" + BELOW_TEN + SPACES + HUNDRED + "(?:" + SPACES_OR_AND + BELOW_HUNDRED + ")?)";

    // a hundred eleven -> 1511
    // NOTE: this is only for final numbers, not prefix of a thousand or million
    const std::string A_HUNDREDS =
        "(?:a" + SPACES + HUNDRED + "(?:" + SPACES_OR_AND + BELOW_HUNDRED + ")?)";

    // NOTE: only REGULAR_HUNDREDS
    const std::string BELOW_THOUSAND =
        "(?:"+REGULAR_HUNDREDS+"|"+BELOW_HUNDRED+")";

    const std::string REGULAR_THOUSANDS =
        "(?:"+BELOW_THOUSAND + SPACES + THOUSAND + "(?:" + SPACES_OR_COMMA_OR_AND + BELOW_THOUSAND +")?)";

    // a thounsand eleven -> 1011
    // NOTE: this is only for final numbers, not prefix of million
    const std::string A_THOUSANDS =
        "(?:a" + SPACES + THOUSAND + "(?:" + SPACES_OR_COMMA_OR_AND + BELOW_THOUSAND +")?)";

    // NOTE: only REGULAR_THOUSANDS
    const std::string BELOW_MILLION =
        "(?:"+REGULAR_THOUSANDS+"|"+BELOW_THOUSAND+")";

    const std::string REGULAR_MILLIONS =
        "(?:"+BELOW_THOUSAND + SPACES + MILLION + "(?:" + SPACES_OR_COMMA_OR_AND + BELOW_MILLION +")?)";

    const std::string A_MILLIONS =
        "(?:a"+ SPACES + MILLION + "(?:" + SPACES_OR_COMMA_OR_AND + BELOW_MILLION +")?)";

    const std::string A_HUNDRED_MILLIONS =
        "(?:"+ A_HUNDREDS + SPACES + MILLION + "(?:" + SPACES_OR_COMMA_OR_AND + BELOW_MILLION +")?)";

    const std::string BILLIONS =
        "(?:(?:a|" + ONE + ")" + SPACES + BILLION +")";

    ///////////////////////////////////////////////////////////////

    // parse a string validate as number as words
    std::uint_fast32_t parse_pib1e9(const std::string& input_str) {
        // there is any validation with in this function
        // becase input_str is validated as a number as words by using the regex

        // map a value for each token
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
            { THIRTY, 30 },
            { FOURTY, 40 },
            { FIFTY, 50 },
            { SIXTY, 60 },
            { SEVENTY, 70 },
            { EIGHTY, 80 },
            { NINETY, 90 },
            { HUNDRED, 100 },
            { THOUSAND, 1'000 },
            { MILLION, 1'000'000 },
            { BILLION, 1'000'000'000 }, // short scale
        };

        bool billion_flag = false;
        uint_fast32_t value = 0, value100=0, value1000=0, value1e6=0;

        std::string s = string_ascii_tolower(input_str);

        // iterator over tokens that are not '-', ',' or spaces
        std::regex negative_regex("-|,|\\s+");
        std::for_each(std::sregex_token_iterator(s.begin(), s.end(), negative_regex, -1), std::sregex_token_iterator(), 
            [&](std::sregex_token_iterator::reference match) {
                // ignore tokens without value
                if (!billion_flag && value_map.count(match.str())) {
                    auto match_value = value_map.at(match.str());
                    switch(match_value) {
                    case 100:
                        // shift to hundreds
                        value100 = value; 
                        value100 = value100? value100 : 1;
                        value = 0;
                        break;
                    case 1'000:
                        // shift to thousands
                        value1000 = value + 100*value100; 
                        value1000 = value1000? value1000 : 1;
                        value = 0;
                        value100 = 0;
                        break;
                    case 1'000'000:
                        // shift to millions
                        value1e6 = value + 100*value100 + 1000*value1000;; 
                        value1e6 = value1e6? value1e6 : 1;
                        value = 0;
                        value100 = 0;
                        value1000 = 0;
                        break;
                    case 1'000'000'000:
                        // billion, special case because it is the upper limit
                        billion_flag = true;
                        break;
                    default:
                        value += match_value;
                        break;
                    }
                }
            }
        );

        if (billion_flag) {
            value = 1'000'000'000;
        }
        else {
            value = value + 100*value100 + 1000*value1000 + 1'000'000*value1e6;
        }
        return value;
    }
}

namespace eng_numerals_pib1e9 {

    void default_log_function(const std::string& log_message) {
        std::cerr << log_message << std::endl;
    }

    std::string convert_to_digits(const std::string& input_string) {
        std::istringstream input(input_string);
        std::ostringstream output;
        convert_to_digits(input,output);
        return output.str();
    }

    void clear_ostringstrem(std::ostringstream& os) {
        os.str("");
        os.clear();
    }

    void convert_to_digits(
        std::istream& input,
        std::ostream& output,
        std::function<void(const std::string&)> logf
    ) {
        // build a big regex to search & validate any number written in words        
        const std::regex numeral_regex(
            // NOTE: order is important, preceding disjuntions have priority
            // and there some with the same prefix
            BILLIONS  + "|" +

            A_HUNDRED_MILLIONS  + "|" +
            A_MILLIONS  + "|" +
            REGULAR_MILLIONS  + "|" +

            A_THOUSANDS + "|" +
            REGULAR_THOUSANDS + "|" +

            A_HUNDREDS + "|" +
            FOUR_DIGITS_HUNDREDS + "|" +
            REGULAR_HUNDREDS + "|" +

            TWENTIES_TO_NINETIES + "|" +
            TENS + "|" +
            BELOW_TEN,
            std::regex::icase|std::regex::optimize
        );

        std::ostringstream logs;

        logs << "begin iteration over paragraph";
        logf(logs.str());
        clear_ostringstrem(logs);

        // iterate over each paragraph (separated by newline)
        for (std::string p; std::getline(input, p);) {

            logs << "new paragraph of size " << p.size();
            logf(logs.str());
            clear_ostringstrem(logs);

            // keep the current paragraph to write to the output
            // in case there aren't any match
            std::string suffix=p;

            logs << "begin iteration over matches";
            logf(logs.str());
            clear_ostringstrem(logs);


            // iterate over each match
            std::for_each(std::sregex_iterator(p.begin(), p.end(), numeral_regex), std::sregex_iterator(), 
                [&](std::sregex_iterator::reference match) {

                    logs << "new match: " << match.str();
                    logf(logs.str());
                    clear_ostringstrem(logs);

                    // output the prefix, non matching parts
                    output << match.prefix();

                    // parse and output the match
                    output << parse_pib1e9(match.str());

                    // keep the still not processed part of the paragraph 
                    suffix = match.suffix().str();
                }
            );

            logs << "end iteration over matches";
            logf(logs.str());
            clear_ostringstrem(logs);

            // output the rest of the paragraph, non matching parts
            output << suffix;

            // newline if isn't the end of the stream
            if (!input.eof()) {
                output << std::endl;
            }
            else {
                logs << "end of input stream";
                clear_ostringstrem(logs);
            }
        }

        logs << "end iteration over paragraph";
        logf(logs.str());
        clear_ostringstrem(logs);
    }
}
