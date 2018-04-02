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

const std::string compress(const std::string &input)
{

    if (input.empty()) {
        throw "Input is empty!";
    }

    size_t len = input.size();
    std::ostringstream sstream;

    char prev = input[0];
    size_t charCount = 0;
    size_t count = 0;

    for (const auto ch:input) {

        if (!std::isalpha(ch)) {
            throw "Invalid input, allowed character range [a-zA-Z]";
        }

        // Keep track of repeated char count untill a different char is seen.
        // If different char is encontered push the previous char along with its count to stream.
        // Else block has stream statement to handle single char cases and to make sure repeated chars at the end are not left out.
        if(prev != ch) {
            sstream << prev << charCount;
            charCount = 1;
            prev = ch;
        } else {
            charCount++;
            if (count == len - 1) {
                sstream << prev << charCount;
            }
        }

        count++;
    }

    const std::string compOutput = sstream.str();

    if (len < compOutput.size()) {
        throw "Too large after compression";
    }

    return compOutput;
}

int main()
{
    const std::string input = "aabccdaaaaa";

    try
    {
        const std::string compOutput = compress(input);
        std::cout << "Compressed output: " << compOutput << "\n";
    }
    catch(const char* errorMsg)
    {
        std::cout << "Error: " << errorMsg << "\n";
    }
}