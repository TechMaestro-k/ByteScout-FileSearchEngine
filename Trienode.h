#include<iostream>
#include<cstdlib>
#include<cstring>
#include "Listnode.h"
#include "scorelist.h"

#ifndef TRIENODE_H
#define TRIENODE_H
using namespace std;

class TrieNode {
    TrieNode* sibling; // Pointer to the next sibling node
    TrieNode* child;   // Pointer to the first child node
    listnode* list;
    char value;
    public:
        TrieNode();
        ~TrieNode();
        void insert(char* token ,int id);
        int tfsearchword(int id, char* token, int curr);
        int dsearchword(char* word, int curr);
        void dsearchall(char* buffer, int curr);
        void search(char* word, int curr, Scorelist* scorelist);
};



#endif // TRIENODE_H