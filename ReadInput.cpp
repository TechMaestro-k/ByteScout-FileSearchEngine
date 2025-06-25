#include "ReadInput.h"
using namespace std;

int read_sizes(int *lineCounter, int *maxLength, char *docfile) {
    FILE* file = fopen(docfile, "r");
    if (file == NULL) {
        cout << "error opening the file" << endl;
        return -1;
    }

    char *line = NULL;
    size_t falsebuffer = 0;
    int currLength;
    while ((currLength = getline(&line, &falsebuffer, file)) != -1) {
        // Remove the newline character from the length if present
        if (line[currLength - 1] == '\n') {
            currLength--;
        }

        if (*maxLength < currLength)
            *maxLength = currLength;
        (*lineCounter)++;

        free(line); // Free the memory allocated by getline
        line = NULL; // Reset the pointer for the next iteration
        falsebuffer = 0;
    }

    fclose(file);

    cout << "lineCounter = " << *lineCounter << ", maxLength = " << *maxLength << endl;
    if (*lineCounter == 0 || *maxLength < 3) {
        cout << "document is empty or does not meet the requirements" << endl;
        return -1;
    }
    return 1;
}

void split(char *temp, int id, TrieNode* trie, Mymap *mymap) {
    char *token = strtok(temp, " \t");
    int i=0; 
    while(token!=NULL){
        i++;
        trie->insert(token, id);
        token = strtok(NULL, " \t");
    }
    mymap->setLength(id,i);
    free(token); // Free the memory allocated by strtok

}

int read_input(Mymap *mymap,TrieNode* trie, char *docfile) {
    FILE* file = fopen(docfile, "r");
    if (file == NULL) {
        cout << "error opening the file" << endl;
        return -1;
    }

    char* line = NULL;
    size_t falsebuffer = 0;
    char *temp=(char*)malloc(mymap->getBufferSize() * sizeof(char));
    for (int i = 0; i < mymap->getSize(); i++) {
        getline(&line,&falsebuffer, file);
        if(mymap->insert(line,i)==-1){
            cout << "document does not meet the requirement" << endl;
            fclose(file);
            free(line);
            free(temp);
            return -1;
        }
        strcpy(temp,mymap->getDocument(i));
        split(temp,i,trie,mymap);
        free(line);
        line = NULL; 
        falsebuffer = 0;
    }

    fclose(file);
    free(temp);
    return 1;
}