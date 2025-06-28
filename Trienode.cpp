#include "Trienode.h"

Trienode::Trienode():letter(-1){
    sibling=NULL;
    child=NULL;
    list=NULL;

}

Trienode::~Trienode(){
    if(sibling!=NULL)
        delete(sibling);
    if(child!=NULL)
        delete(child);
    if(list!=NULL)
       delete(list);
}

void Trienode::insert(char* token, int id){
    if(letter==-1 || letter==token[0]){
        letter = token[0];

        //if we have reached the end of the word we make list containing the location of the word
        if(strlen(token)==1){
            //initialise list
            if(list==NULL)
                list = new Listnode(id);
            list->add(id);
            
        }
        else{
            //adds child node to the existing parent
            if(child==NULL)
                child = new Trienode();
            child->insert(token+1,id);
        }
    }
    else{
        //If parent node already exists, then we add a sibling node
        if(sibling==NULL)
            sibling = new Trienode();
        sibling->insert(token,id);
    }
}

void Trienode::dsearchall(char* buffer, int curr){
    buffer[curr]=letter;
    if(list!=NULL)
        cout<<buffer<<" "<<list->volume()<<endl;
    if(child!=NULL)
        child->dsearchall(buffer,curr+1);
    if(sibling!=NULL)
        sibling->dsearchall(buffer,curr);
    
    buffer[curr]='\0';
}

int Trienode::dfsearchword(char* word, int curr){
    if(word[curr]==letter){
        if(curr==strlen(word)-1){
            if(list!=NULL)
                return list->volume();
            else
                return 0;
        }
        else{
            if(child==NULL)
                return 0;
            return child->dfsearchword(word,curr+1);
        }
    }
    else{
        if(sibling==NULL)
            return 0;
        return sibling->dfsearchword(word,curr);
    }
}

int Trienode::tfsearchword(int id, char* word, int curr){
    if(word[curr]==letter){
        if(curr==strlen(word)-1){
            if(list!=NULL)
                return list->search(id);
            else
                return 0;
        }
        else{
            if(child==NULL)
                return 0;
            return child->tfsearchword(id,word,curr+1);
        }
    }
    else{
        if(sibling==NULL)
            return 0;
        return sibling->tfsearchword(id,word,curr);
    }
}

void Trienode::search(char* word, int curr, Scorelist* scorelist){
    if(word[curr]==letter){
        if(curr==strlen(word)-1){
            if(list!=NULL)
                list->passdocument(scorelist);
            else
                return;
        }
        else{
            if(child!=NULL)
                child->search(word,curr+1,scorelist);
        }
    }
    if(sibling!=NULL)
        sibling->search(word,curr,scorelist);
}