eng_numerals_pib1e9
===================
eng_numerals_pib1e9: english numerals, positive integer below 1e9

A C++ 14 program that convert a text with english numerals words to a text with numbers, i.e.: from 'one hundred and one bottles on the wall' to '101 bottles on the wall'.

The expected valid range of number are positive integer up to 1 000 000 000 (1e9, thousand million or a billion in short scale).

The approach is to, reading a newline separated paragraphs, searching and validating any number written in words, using a regex. Not matching parts are written to the output stream; matches are parsed getting a numeric value for each word and shifting according the magnitude; then numeric values are written to the output stream as digits. See `convert_to_digits()` and `parse_pib1e9()` in the `eng_numerals_pib1e9.cpp` file.

Build from source
-----------------
You will need:
- [CMake](cmake.org) version 3.14 or newer
- a C++ compiler that support C++ 14
- http access to github.com to download `Dash2` dependency

Download or clone the source code repository and then, to compile the source code, run the next commands in the root directory:

```
cmake -H. -B _build; cmake --build _build
``` 

(see [CMake doc](https://cmake.org/cmake/help/v3.14/) for details)

A command line program (`eng_numerals_pib1e9_cli`) and a test program to run various test (`tests`) will be generated.

Example
-------
```
> echo this is a test with one number | eng_numerals_pib1e9_cli
this is a test with 1 number
```

License
-------
[AGPLv3](http://www.gnu.org/licenses/agpl-3.0.html)
