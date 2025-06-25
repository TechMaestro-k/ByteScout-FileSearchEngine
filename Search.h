#include<iostream>
#include<cstdlib>
#include<cstring>
#include "Trienode.h"
#include "Map.h"
#include<math.h>
#include "scorelist.h"
#include "Maxheap.h"
#include<sys/ioctl.h>
#include<unistd.h>


void search(char* token,TrieNode* trie, Mymap *map, int k);
void df(TrieNode* trie);
int tf(char* token,TrieNode* trie);