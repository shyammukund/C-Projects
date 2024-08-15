#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

struct charCount
{
    int count;
    char c;

    charCount(char c, int count){
        this->c = c;
        this->count = count;
    }
    
    // comparator used for max heap 
    bool operator<(const charCount& other) const {
        return this->count < other.count;
    }
    
    // comparator used for min heap
    bool operator>(const charCount& other) const {
        return this->count > other.count;
    }
};


class LetterCount{
private: 
    
    priority_queue<charCount, vector<charCount>, less<charCount>> pq; //max heap
    priority_queue<charCount, vector<charCount>, greater<charCount>> minPq; //min heap
    

public:
    /*
    Write a function that accepts a string and returns an array of the characters in the string sorted by frequency
     (from most frequent to least frequent)You must use a heap to sort the characters. 
     You can use the heap in the dsa package, Python's heapq package or write your own. 
    */
    vector<char> countFreq(const string& s){
        unordered_map<char,int> table;
        vector<char> result;
        for (const char c: s){
            table[c] += 1;
        }

        for (const pair<char,int> item : table){
            pq.push(charCount(item.first, item.second));
        }

        while (!pq.empty()){
            charCount item = pq.top();
            result.push_back(item.c);
            pq.pop();
        }

        return result;

    }

    vector<char> minFreq(const string& s){
        unordered_map<char,int> table;
        vector<char> result;
        for (const char c: s){
            table[c] += 1;
        }

        for (const pair<char,int> item : table){
            minPq.push(charCount(item.first, item.second));
        }

        while (!minPq.empty()){
            charCount item = minPq.top();
            result.push_back(item.c);
            minPq.pop();
        }

        return result;

    }

};









