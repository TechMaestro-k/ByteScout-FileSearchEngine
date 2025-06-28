#include "Listnode.h"

Listnode::~Listnode(){
    if(next!=NULL){
        delete next;
    }
}

void Listnode::add(int d_id){
    if(d_id==id){
        times++;
    }
    else {
        if(next==NULL)
            next = new Listnode(d_id);
        next->add(d_id);
    
    }
}

int Listnode::search(int d_id){
    if(d_id==id)
        return times;
    else{
        if(next==NULL)
            return 0;
        return next->search(d_id);
    }
} 

int Listnode::volume(){
    if(next==NULL)
        return 1;
    else
        return 1 + next->volume();
}

void Listnode::passdocument(Scorelist* scorelist){
    
    scorelist->insert(id);
    if(next!=NULL)
        next->passdocument(scorelist);
}