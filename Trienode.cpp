#include "Trienode.h"

TrieNode::TrieNode():value(-1){
    sibling=NULL;
    child=NULL;
}

TrieNode::~TrieNode()
{
    //if(list!=NULL){
    //    delete list;}
    if(child!=NULL)
        delete child; // Recursively delete the child nodes
    if (sibling != NULL)
        delete sibling; // Recursively delete the sibling nodes
}

void TrieNode::insert(char* token, int id) {
    
    if(value==-1 || value==token[0]){
        value=token[0];
        if(strlen(token)==1){
            //initialize list
            if(list==NULL)
                list=new listnode(id);
            list->add(id);
        }
        else{
            if(child==NULL){
                child=new TrieNode();
            }
            child->insert(token+1, id);
        }
    }
    else{
        if(sibling==NULL){
            sibling=new TrieNode();
        }
        sibling->insert(token, id);
    }
    return ;
}
int TrieNode::tfsearchword(int id, char* word, int curr) {
    if (word[curr] == value) {
        if (curr == strlen(word) - 1) {
            if (list != NULL) {
                int freq = list->search(id);
                return freq;
            } else {
            
                return 0;
            }
        } else {
            if (child != NULL)
                return child->tfsearchword(id, word, curr + 1);
            else {
                return 0;
            }
        }
    } else {
        if (sibling != NULL)
            return sibling->tfsearchword(id, word, curr);
        else {    
            return 0;
        }
    }
}


int TrieNode::dsearchword(char* word, int curr) {
    if(word[curr]==value){
        if(curr==strlen(word)-1){
            if(list!=NULL){
                return list->volume(); // Return the count of documents containing this word
            }
            else{
                return 0; // No documents found 
            }
        }
        else{
            if(child!=NULL)
                return child->dsearchword(word, curr+1);
            else{
                return 0; // No further nodes to search
            }
        }
    }
    else{
        if(sibling!=NULL)
            return sibling->dsearchword(word, curr);
        else{
            return 0; // Word not found
        }
    }

    return 0;
}


void TrieNode::dsearchall(char* buffer, int curr) {
    if (value != -1) { // Ensure the node has a valid value
        buffer[curr] = value; // Add the current character to the buffer
        buffer[curr + 1] = '\0'; // Null-terminate the buffer
    }
    if(list!=NULL){
        cout << buffer << " " << list->volume() << endl;
    }
    if(child!=NULL){
        child->dsearchall(buffer, curr+1);
    }
    if(sibling!=NULL){
        sibling->dsearchall(buffer, curr);
    }
    buffer[curr]='\0'; // Reset the current character before returning
}


void TrieNode::search(char* word, int curr, Scorelist* scorelist) {
    if(word[curr]==value){
        if(curr==strlen(word)-1){
            if(list!=NULL){
                return list->passdocuments(scorelist); // Pass the documents to the scorelist
            }
            else{
                return ; // No documents found
            }
        }
        else{
            if(child!=NULL)
                child->search(word, curr+1, scorelist);
            else{
                return ; // No further nodes to search
            }
            
        }
    }
    else{
        if(sibling!=NULL)
            sibling->search(word, curr, scorelist);
        else{
            return ; // Word not found
        }
    }
}