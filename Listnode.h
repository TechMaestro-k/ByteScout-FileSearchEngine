#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Scorelist.h"

#ifndef LISTNODE_H
#define LISTNODE_H
class Listnode{
    Listnode* next; //next list item
    int id; // document id
    int times=0; //times the word appears in the document
public:
    Listnode(int d_id):id(d_id),times(0){next=NULL;}
    ~Listnode();

    void add(int d_id);
    int search(int d_id);
    int volume();
    void passdocument(Scorelist* scorelist);
};
#endif