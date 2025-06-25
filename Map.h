#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

#ifndef MAP_H   /* Ensure the header is included only once matlab ki ye class  wapis initialize na ho agar ek baar ho chuki hai to*/
#define MAP_H
class Mymap
{
    int size;    //the number of documents
    int buffersize;   //the length of the biggest document
    char** documents;  //each document
    int* lengths;   //length of each document
public:
    Mymap(int size,int buffersize);
    ~Mymap();
    int insert(char* line,int index);
    void setLength(int id, int length) { lengths[id] = length; }
    int getLength(int id) { return lengths[id]; }
    void print(int i){cout << i << ": " << documents[i] << endl; }
    char* getDocument(int i) { return documents[i]; }
    const int getSize() { return size; }  
    const int getBufferSize() { return buffersize; }
};
#endif // MAP_H