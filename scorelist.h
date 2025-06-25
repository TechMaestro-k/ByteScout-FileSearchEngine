#include<iostream>
#include<cstdlib>
#include<cstring>

#ifndef SCORELIST_H
#define SCORELIST_H
class Scorelist {
public:
    int id;
    Scorelist* next;
    Scorelist(int did=-1) : id(did){next=NULL;}
    ~Scorelist();
    void insert(int did);
    int getid(){return id;}
    Scorelist* getnext() { return next; }
};
#endif // SCORELIST_H