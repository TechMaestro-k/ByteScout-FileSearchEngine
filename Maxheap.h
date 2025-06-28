#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef MAXHEAP_H
#define MAXHEAP_H
class Maxheap{
    double* heap;
    int* ids;
    int curnumofscores;
    int maxnumofscores;
    void swapscores(int num1, int num2);
    int minindex(int low, int high);

public:
    Maxheap(int k);
    ~Maxheap(){free(heap);free(ids);};
    void insert(double score, int id);
    int Maxchild(int num1, int num2);
    double remove();
    int getid(){return ids[0];};


};
#endif