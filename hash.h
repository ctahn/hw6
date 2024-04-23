#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

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
        if(k.length() == 0){
          return 0;
        }
        std::vector<HASH_INDEX_T> hash_index;
        for(size_t i=0; i < k.length(); i++){
          hash_index.push_back(letterDigitToNumber(k[i]));
        }
        unsigned long long w[5];
        for(int i=0; i < 5; i++){
          w[i] = 0;
        }

        for(int j=4; j >= 0; j--){
          unsigned long long temp = 0;
          
            if(hash_index.size() > 6){
              for(int i=0; i < 5; i++){
                temp = (hash_index[hash_index.size()-6+i]+temp)*36;
              }
              temp += hash_index[hash_index.size()-1];
              w[j] = temp;
              hash_index.resize(hash_index.size()-6);
            }
            else{
              for(size_t i=0; i < hash_index.size()-1; i++){
                temp = (hash_index[i]+temp)*36;
              }
              temp += hash_index[hash_index.size()-1];
              w[j] = temp;
              break;
            }
        }


        HASH_INDEX_T answer = 0;
        for(int i=0; i < 5; i++){
          answer += rValues[i]*w[i];
        }
        return answer;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if(isalpha(letter)){
          return tolower(letter) - 'a';
        }
        else{
          return letter - '0' + 26;
        }
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
