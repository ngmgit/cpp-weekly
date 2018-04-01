/**
Problem for week 1: String Compression

Implement a method to perform string compression using counts of repeated characters. String "aabccdaaaaa" becomes "a2b1c2d1a5". The function needs to check for errors and raise an error in case -
1. resultant compressed string is larger
2. invalid character is found.

The only valid characters fall into [a-zA-Z] range.
**/

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

std::string compress(std::string &input)
{

    size_t len = input.size();
    std::ostringstream sstream;

    char prev = input[0];
    int charCount = 0;
    size_t count = len;

    for (const auto ch:input) {

        if (!std::isalpha(ch)) {
            throw "Invalid input, allowed character range [a-zA-Z]";
        }

        if(prev != ch || count == 1) {
            sstream << prev << charCount;
            charCount = 1;
            prev = ch;
        } else {
            charCount++;
        }

        count --;
    }

    std::string compInput = sstream.str();

    if (len < compInput.size()) {
        throw "Too large after compression";
    }

    return compInput;
}

int main(int argc, char *argv[])
{

    std::string input = "aabccdaaaaa";

    try
    {
        std::string compInput = compress(input);
        std::cout << "Compressed output: " << compInput << std::endl;
    }
    catch(const char* errorMsg)
    {
        std::cout << "Error: " << errorMsg << std::endl;
    }
    return 0;
}