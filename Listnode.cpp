#include "Listnode.h"

listnode::~listnode() {
    // Destructor to clean up the linked list
    if (next != NULL) {
        delete(next);
    }
}

void listnode::add(int did) {
    if(did == id){
        times++;
    }
    else{
        if(next==NULL){
            next=new listnode(did);
        }
        else{
            next->add(did);
        }
    }
}

int listnode::search(int did) {
    if (id == did) {
        return times;
    } 
    else{
        if (next == NULL) {
            return 0;
        } 
        else {
            return next->search(did);
        }
    }
}


int listnode::volume() {
    if (next != NULL) {
        return 1 + next->volume();; // Count this node and recurse
    } else {
        return 1; //count this node
    }
}

void listnode::passdocuments(Scorelist* scorelist) {
    scorelist->insert(id);
    if(next!=NULL)
        next->passdocuments(scorelist);
}
