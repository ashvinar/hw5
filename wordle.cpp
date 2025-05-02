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
void wordleHelper(
    string& current,
    const string& in,
    string floating,
    const set<string>& dict,
    set<string>& results,
    size_t pos);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    string current = in;
    
    wordleHelper(current, in, floating, dict, results, 0);
    
    return results;
}

// Define any helper functions here
void wordleHelper(
    string& current,
    const string& in,
    string floating,
    const set<string>& dict,
    set<string>& results,
    size_t pos)
{
    if (pos == in.length()) {
        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }
    
    if (in[pos] != '-') {
        wordleHelper(current, in, floating, dict, results, pos + 1);
        return;
    }
    
    
    for (size_t i = 0; i < floating.length(); i++) {
        current[pos] = floating[i];
        string newFloating = floating.substr(0, i) + floating.substr(i+1);
        wordleHelper(current, in, newFloating, dict, results, pos + 1);
    }
    
    if (floating.length() < in.length() - pos) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (floating.find(c) != string::npos) {
                continue;
            }
            
            current[pos] = c;
            wordleHelper(current, in, floating, dict, results, pos + 1);
        }
    }
}
