#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        HASH_INDEX_T w[5] {0, 0, 0, 0, 0};

        int idx = 4;
        
        int end = k.length() - 1;
        int start = (end - 5 > 0) ? end-5:0;

        HASH_INDEX_T decimal = 0;

        int next_end = start-1;

        while(start <= end) {
           decimal = decimal * 36 + letterDigitToNumber(k[start]); 
           ++start;
           // after a block of 6 chars, find the new starting index
           if(start > end) {
                if(next_end >= 5) {
                    start = next_end - 5;
                }
                else {
                    start = 0;
                }
                end = next_end;
                next_end = start - 1;

                w[idx--] = decimal;
                decimal = 0;
           }
        }

        HASH_INDEX_T result = rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4]; 

        return result;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T digit;

        if(letter >= 65 && letter <= 90) {
            letter += 32;
        }

        if(letter >= 97) {
            digit = (int)letter - 97;
        }
        else {
            digit = (int)letter - 22;
        }

        return digit; ///// is this returning a letter or an int? should be int (HASH_INDEX_T)

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
