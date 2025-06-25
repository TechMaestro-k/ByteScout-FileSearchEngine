#include "scorelist.h"
using namespace std;

Scorelist::~Scorelist() {
    if (next != NULL) {
        delete next;
    }
}

void Scorelist::insert(int did) {
    if (id == did) {
        return; // Document already exists, do nothing
    } 
    if(id==-1){
        id=did;
    }
    else{
        if(next==NULL){
            next=new Scorelist(did);
        }
        else{
            next->insert(did); // Recursively insert into the next node
        }
    }
}