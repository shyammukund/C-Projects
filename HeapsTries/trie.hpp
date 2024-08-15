#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

// Create Trie Node
class Node {
 public: 
    unordered_map<char,Node*> children;
    bool end;
    int count;

    Node(){

        end = false;
        count = 0;
    }
 };

// Trie Class
 class Trie{
  private: 
    Node* root;

    void cleanNodes(Node* node){
        if (node == nullptr){
            return;
        }
        // iterate through all children.
        for (auto& it: node->children){
            cleanNodes(it.second);
        }

        delete node;
    }
  public:
    // constructor
    Trie(){
       root = new Node();
    }

    // destructor
    ~ Trie(){
        cleanNodes(root);
    }

    //insert
    void insert2(string& word ){
        Node* current = root;
        for (char w : word){
            if (current->children.find(w) == current->children.end()){
                current->children[w] = new Node();
            }
            else {
                (current->children[w]->count)++;
            }
            current = current->children[w];
        }
        current->end = true;
    }

    //insert method
    void insert(const string& word ){
        if (word.empty()){
            return;
        }
        Node* current = root;
        for (char w : word){
            if (current->children.find(w) == current->children.end()){
                current->children[w] = new Node();
            }
            (current->children[w]->count)++;
            current = current->children[w];
        }
        current->end = true;
    }
    // search method to check if the insert worked
    bool search(string& word){
        Node* current = root;
        for (char w: word){
            if (current->children.find(w) == current->children.end()){
                return false;
            }
            current = current->children[w];
        }
        return current->end;
    }

    // startsWith method to check if the trie has any words starting with given prefix.
    bool startsWith(string prefix){
        Node* current = root;
        for (int p: prefix){
            if (current->children.find(p) == current->children.end()){
                return false;
            }
            current = current->children[p];
        }
        return true;
    }

    /*
    3.
    Write a function that accepts an array of words and returns the longest common prefix. Write it so that it performs efficiently.
    For example, given the array
    words = ["apple", "appetite", "apparatus", "appliance"]
    The function should return
    "app"
    */

    // method to return the longest common prefix among given words.
    string longestCommonPrefix(){
        Node* current = root;
        string result = "";

        while (current->children.size() < 2 && !current->end ){
            if(current->children.size() == 0){
                break;
            }
            unordered_map<char,Node*>::iterator it = current->children.begin();
            result.push_back(it->first) ;
            current = current->children[it->first];
        }
        return result;
    }

    /*
    4. Write a function that accepts an array of words and then returns the shortest unique
     prefix of each word. 
    */

    // Input: {"apple", "apricot", "ape"}
    //Expected Output: {"app", "apr", "ape"}

    // helper method for shortest unique prefix
    void prefixHelper(Node* node, vector<string>& result, string prefix){
        if (node == nullptr){
            return;
        }

        if (node->count == 1){
            result.push_back(prefix);
            return;
        }
        
        if (node->end){
            result.push_back(prefix);
        }
        
        for (auto child: node->children){
            prefixHelper(child.second, result, prefix + child.first);
        }
        
    }

    // method to find the shortest unique prefix among given words. 
    vector<string> shortestUniquePrefix(){ 
        vector<string> result;
        string prefix;
       
        for (auto& child: root->children){
            string prefix = "";
            prefix += child.first;
            prefixHelper(child.second, result, prefix);
        }
        return result;
        
    }

 };

    

