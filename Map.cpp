#include "Map.h"
using namespace std;
Mymap::Mymap(int size,int buffersize):size(size),buffersize(buffersize){
    documents=(char**)malloc(size*sizeof(char*));
    lengths=(int*)malloc(size*sizeof(int));
    // allocating memory for each part of document
    for(int i=0;i<size;i++){
        documents[i]=(char*)malloc(buffersize*sizeof(char));
    }
}

//dealocation after useage for security purposes
Mymap::~Mymap(){
    for(int i=0;i<size;i++){
        free(documents[i]);
    }
    free(documents);
    free(lengths);
}

// formats our input dataset
int Mymap::insert(char* line, int i){
    char* token;
    token=strtok(line, " \t");
    int curr = atoi(token);
    if(curr!=i){
        token=NULL;
        free(token);
        return -1;
    }
    token = strtok(NULL,"\n");
    while(token[0]==' ')
        token++;
    int end=0;
    while(token[end]!='\0')
        end++;
    end--;
    while(end!=0 and token[end]==' ')
        token[end--]='\0';
    strcpy(documents[i],token);
    token=NULL;
    free(token);
    return 1;
}
