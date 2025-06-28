#include "Maxheap.h"
using namespace std;

Maxheap::Maxheap(int k):maxnumofscores(k),curnumofscores(0){
    heap = (double*)malloc(sizeof(double)*maxnumofscores);
    ids = (int*)malloc(sizeof(int)*maxnumofscores);
}

int Maxheap::minindex(int low, int high){
    int minindex = -1;
    double minscore = 100000000.0;
    for(int i = low; i<high; i++){
        if(heap[i]<minscore){
            minindex = i;
            minscore = heap[i];
        }
    }
    return minindex;
}

void Maxheap::swapscores(int num1, int num2){
    double temp = heap[num1];
    heap[num1] = heap[num2];
    heap[num2] = temp;
    int tempid = ids[num1];
    ids[num1] = ids[num2];
    ids[num2] = tempid;
}

void Maxheap::insert(double score, int id){
    int index;
    if(curnumofscores!=maxnumofscores){
        index = curnumofscores;
        curnumofscores++;
    }
    else{
        int tempindex = minindex(maxnumofscores/2,maxnumofscores);
        if(score>heap[tempindex]){
            index = tempindex;
        }
        else{
            return;
        }
    }
    heap[index] = score;
    ids[index] = id;
    while(heap[index]>heap[(index-1)/2]){
        swapscores(index,(index-1)/2);
        index = (index-1)/2;
    }

}

int Maxheap::Maxchild(int num1, int num2){
    if(num1<curnumofscores and num2<curnumofscores){
        if(heap[num1]>heap[num2]){
            return num1;
        }
        else{
            return num2;
        }
    }
    else if(num1<curnumofscores){
        return num1;
    }
    else if(num2<curnumofscores){
        return num2;
    }
    else{
        return -1;
    }
}

double Maxheap::remove()
{
    int index = 0, child;
    double retValue = 0.0;
    if(curnumofscores>0){
        retValue = heap[0];
        curnumofscores--;
        heap[0] = heap[curnumofscores];
        ids[0] = ids[curnumofscores];
        while(1){
            child = Maxchild(2*index+1,2*index+2);
            if(child==-1 and heap[index]<heap[child]){
                swapscores(index,child);
                index = child;
            }
            else{
                break;
            }
        }
    }
    return retValue;
}