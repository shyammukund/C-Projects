#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include "heap.hpp"
#include "tree.hpp"
#include "trie.hpp"


using namespace std;

// Method to test for longest common prefix
void test_lcp(vector<string> &words, const string &expected)
{
    Trie trie;
    for (string &word : words)
    {
        trie.insert(word);
    }

    string result = trie.longestCommonPrefix();
    cout << "Words: ";

    for (const string &word : words) {
        cout << word << " ";
    }

    cout << "\nExpected: " << expected << "\nGot: " << result << endl;
    if (result == expected)
    {
        cout << "Test Passed!" << endl;
    }
    else
    {
        cout << "Test Failed!" << endl;
    }
    cout << "----------------------------------------" << endl;
}

// Method to test for shortest unique prefix
void test_scp(vector<string> &words, const vector<string> &expected)
{
    Trie trie2;
    for (string &word : words)
    {
        trie2.insert(word);
    }

    vector<string> result = trie2.shortestUniquePrefix();
    vector<string> sortR = result;
    vector<string> sortE = expected;
    
    cout << "Words: ";

    for (const string& word : words) {
        cout << word << " ";
    }
    sort(sortE.begin(), sortE.end());
    cout << "Expected: { ";
    for (string e: sortE){
        cout << e << " ";
    }
    cout<< "}" << endl;
    
    sort(sortR.begin(), sortR.end());
    cout << "Result: { ";
    for (string r: sortR){
        cout << r << " ";
    }
    cout << "}" << endl;
    
    if (sortR == sortE)
    {
        cout << "Test Passed!" << endl;
    }
    else
    {
        cout << "Test Failed!" << endl;
    }
    cout << "----------------------------------------" << endl;
}
void test_trie(){
    // longest common prefix test cases

    vector<string> words1 = {"flower", "flow", "flight"};
    vector<string> words2 = {"dog", "racecar", "car"};
    vector<string> words3 = {"test", "test", "test"};
    vector<string> words4 = {"interview", "interviewer", "interviewee"};
    vector<string> words5 = {"apple", "ape", "apricot"};
    vector<string> words6 = {};
    vector<string> words7 = {"singleton"};
    vector<string> words8 = {"a", "b", "c"};
    vector<string> words9 = {"common", "commute", "company"};
    vector<string> words10 = {"sp@cial", "sp@ce", "sp@rse"};
    vector<string> words11 = {"12345", "123", "123abc"};
    vector<string> words12 = {"Case", "casual", "castle"};

    vector<string> scp1 = {"apple", "apricot", "ape"};
    vector<string> scp2 = {"a", "b", "c"};
    vector<string> scp3 = {"dog", "doge", "dogs"};
    vector<string> scp4 = {"cat", "cat", "catalog"};
    vector<string> scp5 = {"bat", "bath", "batman"};
    vector<string> scp6 = {"tree", "house", "car"};
    vector<string> scp7 = {"unique"};
    vector<string> scp8 = {"prefix", "preform", "prevent"};
    vector<string> scp10 = {"identical", "identical", "identical"};
    vector<string> scp11 = {"base", "baseline", "basement"};
    vector<string> scp12 = {"xylophone", "yellow", "zebra"};
    vector<string> scp13 = {"common", "commune", "communication"};



    // lcp test
    test_lcp(words1, "fl");
    test_lcp(words2, "");
    test_lcp(words3, "test");
    test_lcp(words4, "interview");
    test_lcp(words5, "ap");
    test_lcp(words6, "");
    test_lcp(words7, "singleton");
    test_lcp(words8, "");
    test_lcp(words9, "com");
    test_lcp(words10, "sp@");
    test_lcp(words11, "123");
    test_lcp(words12, ""); // Case sensitive check

    // shortest unique prefix test cases
    test_scp(scp1, { "app", "apr", "ape"});
    test_scp(scp2, { "a", "b", "c"});
    test_scp(scp3, { "dog", "doge", "dogs"});
    test_scp(scp4, { "cat", "cata"});
    test_scp(scp5, { "bat", "bath", "batm"});
    test_scp(scp6, { "t", "h", "c"});
    test_scp(scp7, { "u"});
    test_scp(scp8, { "prefi", "prefo", "prev"});
    test_scp(scp10, { "identical"});
    test_scp(scp11, { "base", "basel", "basem"});
    test_scp(scp12, { "x", "y", "z"});
    test_scp(scp13, { "commo", "commune", "communi"});
    
}

// Find the last node in a complete tree
void test_last_node(){
    vector<int> input = {1,2,3,4,5,6,7,8,9,10};
    BinaryTree bt;
    for (int i : input){
        bt.insert(i);
    }
   bt.returnlastNode();
}
// prints an array that contains the characters used in a string sorted by frequency.
void test_letterCount(){
    string test = "she sells the sea shells by the seashore";
    LetterCount test1;
    vector<char> result = test1.countFreq(test);
     for (char r: result){
        cout << r << " ";
    }
    cout << endl;

    vector<char> resultMin = test1.minFreq(test);

    for (char r: resultMin){
        cout << r << " ";
    }
    cout << endl;

    
}

int main(){
    //test_letterCount();
    //test_last_node();
    test_trie();
    return 0;
}

