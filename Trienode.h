#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Listnode.h"
#include "Scorelist.h"

#ifndef TRIENODE_H
#define TRIENODE_H

using namespace std;
class Trienode{
    Trienode* sibling;
    Trienode* child;
    Listnode* list;
    char letter;
public:
    Trienode();
    ~Trienode();
    void insert(char* token, int id);
    int tfsearchword(int id, char* word, int curr);
    int dfsearchword(char* word, int curr);
    void dsearchall(char* buffer, int curr);
    void search(char* word, int curr, Scorelist* scorelist);
};

#endif