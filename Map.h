#include<iostream>
#include <cstdlib>
#include<cstring>

using namespace std;

#ifndef MAP_H
#define MAP_H
class Mymap{
    int size; //no of docs
    int buffersize; //length of largest doc
    char** documents; //each doc
    int* lengths; //length of each doc
    public:
        Mymap(int size, int buffersize);
        ~Mymap();
        int insert(char* line, int i);
        void setlength(int id, int length){lengths[id]=length;}
        int getlength(int id){return lengths[id];}
        void print(int i){cout<<i<< " "<<documents[i]<<endl;}
        char *getdocument(int i){return documents[i];}
        const int getsize(){return size;}
        const int getbuffersize(){return buffersize;}
};
#endif