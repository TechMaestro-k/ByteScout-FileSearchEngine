#include "Search.h"
using namespace std;

const float k1 = 1.2;
const float b = 0.75;

void search(char* token, Trienode* trie, Mymap* map, int k){
    char warray[10][256];
    double IDF[10];
    token = strtok(NULL, " \t\n");
    Scorelist* scorelist = new Scorelist();
    int i;
    for(i=0;i<10;i++){
        if(token==NULL){
            // cout<<"Not enough arguments"<<endl;
            break;
        }
        strcpy(warray[i],token);
        IDF[i] = log10(((double)map->getsize() - (double)trie->dfsearchword(warray[i],0)+0.5)/((double)trie->dfsearchword(warray[i],0)));
        trie->search(warray[i],0,scorelist);
        token = strtok(NULL, " \t\n");

    }

    
    double avgdl=0;
    for(int m = 0; m<map->getsize(); m++){
        avgdl += (double)map->getlength(m);
    }
    avgdl = avgdl/(double)map->getsize();
    double score;
    Scorelist* tempList = scorelist;
    Maxheap* heap = new Maxheap(k);
    int ceil = 0;
    while(tempList!=NULL){
        
        for(int l=0; l<i; l++){
            score += IDF[l]*((double)trie->tfsearchword(tempList->getid(),warray[l],0)) * (k1+1.0)/((double)trie->tfsearchword(tempList->getid(),warray[l],0)+k1*(1.0-b+b*((double)map->getlength(tempList->getid())/(double)avgdl)));
        }
        heap->insert(score, tempList->getid());
        score=0;
        tempList = tempList->getnext();
        ceil++;
    }
    if(ceil>k){
        ceil = k;
    }
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for(int l=0; l<ceil; l++){
        int id = heap->getid();
        if(id==-1){
            break;
        }
        
        double score = (double)heap->remove();
        cout<<"("<<id;
        int x = 10;
        int f=1;
        //calculates how big the ids of document is
        while(id/x!=0){
            x*=10;
            f++;
        }

        //normalizes the space between id and score
        while(5-f>=0){
            cout<<" ";
            f++;
        }

        printf(")[%10.6f] ",score);
        char* line = (char*)malloc(map->getbuffersize()*sizeof(char));
        strcpy(line,map->getdocument(id));
        char* temp = strtok(line, " \t\n");
        int currlen = 0;
        int counter = 0;
        int newline =1, lineflag=0;
        int underline[2][100];
        int ucounter=0;
        while(temp!=NULL){
            
            if(newline){
                currlen+=20;
                if(counter!=0){
                    for(int co=0;co<20;co++)
                        cout<<" ";
                }
                newline = 0;
            }
        
            for(int n=0;n<i;n++){
                if(!strcmp(warray[n],temp)){
                    if(currlen+strlen(temp)+1<=w.ws_col){
                        underline[0][ucounter] = currlen;
                        underline[1][ucounter] = strlen(temp);
                        ucounter++;
                        lineflag=1;
                    }
                    break;
                }
            }

            currlen+=strlen(temp)+1;
            if(currlen-1>=w.ws_col){
                currlen = 0;
                newline = 1;
                cout<<endl;
                if(lineflag){
                    char* outputline = (char*)malloc((w.ws_col+1)*sizeof(char));
                    for(int j=0;j<w.ws_col;j++){
                        outputline[j] = ' ';
                    }
                    outputline[w.ws_col] = '\0';
                    lineflag=0;
                    for(int j=0;j<ucounter;j++){
                        for(int v=underline[0][j];v<underline[0][j]+underline[1][j];v++){
                            outputline[v] = '^';
                        }
                    }
                    ucounter=0;
                    cout<<outputline;
                    free(outputline);
                }
                continue;
                
            }
            cout<<temp<<" ";
            temp = strtok(NULL, " \t\n");
            counter++;
        }
        cout<<endl;
        free(line);
        free(temp);

    }
    delete heap;
    delete scorelist;
    cout<<endl;

}


void df(Trienode* trie){
    
    char* token = strtok(NULL, " \t\n");
    if(token!=NULL){
        cout<<token<<" "<<trie->dfsearchword(token,0)<<endl;
    }
    else{
        char* buffer = (char*)malloc(sizeof(char)*256);
        trie->dsearchall(buffer,0);
        free(buffer);
    }

    token=NULL;
    free(token);
}


int tf(char* token, Trienode* trie){
    char* token2 = strtok(NULL, " \t\n");
    if(token2==NULL){
        free(token2);
        return -1;
    }
    for(int l=0; l<strlen(token2); l++){
        if(!isdigit(token2[l])){
            token2=NULL;
            free(token2);
            return -1;
        }
    }

    int id = atoi(token2);
    token2 = strtok(NULL, " \t\n");
    if(token2==NULL){
        free(token2);
        return -1;
    }
    cout<<id<<" "<<token2<<" "<<trie->tfsearchword(id, token2,0)<<endl;
    return 1;
}