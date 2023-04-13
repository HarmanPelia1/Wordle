#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool existing(const string& word, const set<string>& dict);

void combine(const std::string& pattern, 
    const string& floating, 
    std::set<std::string>& results, 
    int index, 
    const std::set<std::string>& dict);




// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	std::set<std::string> final;

	combine(in, floating, final, 0, dict);

	return final;
}

// Define any helper functions here

void combine(const std::string& pattern, const std::string& floating, std::set<std::string>& final, int index, const std::set<std::string>& dict){

    if (index == pattern.size()){

        if (existing(pattern, dict)) final.insert(pattern);

        return;
    }

    if (pattern[index] == '-'){

        for (char c : floating) {

            std::string newPattern_ = pattern;

            newPattern_[index] = c;

            std::string newfloat_ = floating;

            auto pos = newfloat_.find(c);

            if (pos != std::string::npos) newfloat_.erase(pos, 1);
    
            combine(newPattern_, newfloat_, final, index+1, dict);
        }
    }

    else{
        combine(pattern, floating, final, index+1, dict);
    }
}


bool existing(const std::string& word, const std::set<std::string>& dict){
	return dict.find(word) != dict.end();
}