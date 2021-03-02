eng_numerals_pib1e9
===================
eng_numerals_pib1e9: english numerals, positive integer below 1e9

Work in progress C++ 14 program that convert a text with english numerals words to a text with numbers, i.e.: from 'one hundred and one bottles on the wall' to '101 bottles on the wall'.

The expected valid range of number are positive integer up to 1 000 000 000 (thousand million or a billion in short scale).

Build from source
-----------------
You will need:
- [CMake](cmake.org) version 3.14 or newer
- a C++ compiler that support C++ 14

Download or clone the source code repository and then, to compile the source code, run the next commands in the root directory:

```
cmake -H. -B _build; cmake --build _build
``` 

(see [CMake doc](https://cmake.org/cmake/help/v3.14/) for details)

A command line program (`eng_numerals_pib1e9_cli`) and a test program to run various test (`tests`) will be generated.

License
-------
[AGPLv3](http://www.gnu.org/licenses/agpl-3.0.html)
