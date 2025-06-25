#include "Map.h"
using namespace std;

Mymap::Mymap(int size,int buffersize):size(size),buffersize(buffersize)  //member initializer list
{
    documents=(char**)malloc(size*sizeof(char*));
    lengths=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++){
        documents[i]=(char*)malloc(buffersize*sizeof(char));
    }
}

Mymap::~Mymap()
{
    for(int i=0;i<size;i++){
        free(documents[i]);
    }
    free(documents);
    free(lengths);
}


int Mymap::insert(char* line, int i) {

    int curr;
    char* token = strtok(line, " \t");
    curr=atoi(token); // Convert the first token to an integer
    if(curr!=i){
        token=NULL;
        free(token);
        return -1;
    }
    token = strtok(NULL, "\n");
    while (token[0] == ' ') {
        token++; // Skip leading spaces
    }
    int end=0;
    while(token[end]!='\0'){
        end++;
    }
    end--;
    while(end!=0 && token[end]==' '){
        end--; // Remove trailing spaces
    }
    token[end+1]='\0'; // Null-terminate the string after removing trailing spaces
    strcpy(documents[i], token); // Copy the cleaned line into the documents array
    token=NULL;
    free(token);

    return 1;
}