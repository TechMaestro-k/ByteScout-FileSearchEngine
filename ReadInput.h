#include<iostream>
#include <cstdio>
#include <cstdlib>
#include "Map.h"
#include "Trienode.h"
int read_sizes(int *lineCounter,int *maxLength,char *docfile);
int read_input(class Mymap *mymap,TrieNode* trie, char *docfile);