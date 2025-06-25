#include<iostream>
#include<cstdlib>
#include<cstring>
#include "scorelist.h"

#ifndef LISTNODE_H
#define LISTNODE_H
using namespace std;
class listnode{
    listnode* next;   //next list items
    int id;           //id of document
    int times;        //how many times in the specific document
public:
    listnode(int did):id(did), times(0){next=NULL;}
    ~listnode();
    void add(int did); 
    int search(int did);
    int volume();
    void passdocuments(Scorelist* scorelist) ;
};
#endif
