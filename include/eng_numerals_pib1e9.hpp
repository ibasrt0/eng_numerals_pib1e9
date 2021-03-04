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

#ifndef ENG_NUMERALS_PIB1E9_INCLUDED
#define ENG_NUMERALS_PIB1E9_INCLUDED 1

#include <iostream>
#include <string>
#include <functional>

namespace eng_numerals_pib1e9 {

    //! Default log function for convert_to_digits(std::istream&, std::ostream&).
    /**
     Write the \p log_message and newline to std::cerr.
     */
    void default_log_function(const std::string& log_message);

    //! Converts written numbers in words to digits.
    /*! 
    Read from the \p input stream paragraphs delimited by newline,
    and then write to the \p output stream
    but with written numbers in words converted to digits.
    \param log_function log function to process message logs
    */
    void convert_to_digits(
        std::istream& input,
        std::ostream& output,
        std::function<void(const std::string&)> log_function = default_log_function
    );

    //! Converts written numbers in words to digits.
    /*!
    Convenient function that wrap convert_to_digits(std::istream&, std::ostream&, std::function<void(const std::string&))
    to use it with std::strings instead of streams.
    */
    std::string convert_to_digits(const std::string& input);
}

#endif