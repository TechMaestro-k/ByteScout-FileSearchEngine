#include "Search.h"
using namespace std;
const float k1=1.2;
const float b=0.75;

void search(char* token, TrieNode* trie, Mymap* map, int k) {
    cout << "Debug: Entering search function" << endl;
    char warray[10][256];
    double IDF[10];
    token = strtok(NULL, " \t\n");
    Scorelist* scorelist = new Scorelist();
    int i;
    for (i = 0; i < 10; i++) {
        if (token == NULL) {
            break;
        }
        cout << "Debug: Processing token: " << token << endl;
        strcpy(warray[i], token);
        IDF[i] = log10((double)map->getSize() - (double)trie->dsearchword(warray[i], 0) + 0.5) /
                 ((double)trie->dsearchword(warray[i], 0) + 0.5);
        trie->search(warray[i], 0, scorelist);
        token = strtok(NULL, " \t\n");
    }
    double avgdl = 0;
    for (int m = 0; m < map->getSize(); m++) {
        avgdl +=(double)map->getLength(m);
    }
    avgdl /= (double)map->getSize();
    cout << "Debug: Average document length: " << avgdl << endl;

    //correct 
    double score = 0;
    Scorelist* tempList = scorelist;
    Maxheap* heap = new Maxheap(k);
    int ceil = 0;
    while (tempList != NULL) {
        for (int l = 0; l < i; l++) {
            score = IDF[l] * ((double)trie->tfsearchword(tempList->getid(), warray[l], 0) * (k1 + 1.0)) /
                    ((double)trie->tfsearchword(tempList->getid(), warray[l], 0) +
                     k1 * (1.0 - b + b * (double)map->getLength(tempList->getid()) / (double)avgdl));
            heap->insert(score, tempList->getid());
            score = 0;
            tempList = tempList->getnext();
            ceil++;
        }
        cout << "after for loop" << endl;
        if (ceil > k) ceil = k;
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        // if (w.ws_col <= 0) {
        //     cout << "Error: Invalid window size" << endl;
        //     break;
        // }
        for (int l = 0; l < ceil; l++) {
            int id=heap->getid();
            if(id==-1) break;
            double score=(double)heap->remove();
            cout << "(" << id;
            int x=10;
            int f=1;
            cout << "enterd loop"<< endl;
            while(id/x!=0){
                x*=10;
                f++;
            }
            while(5-f>=0){
                cout << " ";
                f++;
            }
            printf(")[%10.6f]",score);
            char* line=(char*)malloc(map->getBufferSize()*sizeof(char));
            strcpy(line,map->getDocument(id));
            char* temp;
            temp=strtok(line," \t\n");
            int currlength=0;
            int counter=0;
            int newline=0;
            int lineflag=0;
            int underline[2][100];
            int ucounter=0;
            
            while (temp != NULL) {
                if (newline) {
                    currlength += 20;
                    if (counter != 0) {
                        for (int co = 0; co < 20; co++) {
                            cout << " ";
                        }
                    }
                    newline = 0;
                }
            
                for (int n = 0; n < i; n++) {
                    if (!strcmp(warray[n], temp)) {
                        if (currlength + strlen(temp) + 1 <= w.ws_col) {
                            underline[0][ucounter] = currlength;
                            underline[1][ucounter] = strlen(temp);
                            ucounter++;
                            lineflag = 1;
                        }
                        break;
                    }
                }
                cout << "after for loop" << endl;
                currlength += strlen(temp) + 1;
                cout << "Debug: temp = " << (temp ? temp : "NULL") << endl;
                cout << "Debug: currlength = " << currlength << endl;
                cout << "Debug: w.ws_col = " << w.ws_col << endl;
            
                if (currlength - 1 >= w.ws_col) {
                    cout << "enter if state" << endl;
                    currlength = 0;
                    newline = 1;
                    cout << endl;
                    if (lineflag) {
                        char* outputline = (char*)malloc((w.ws_col + 1) * sizeof(char));
                        if (outputline == NULL) {
                            cout << "Error: Failed to allocate memory for outputline" << endl;
                            return;
                        }
                        for (int j = 0; j < w.ws_col; j++) {
                            cout << "enter for loop1" << endl;
                            outputline[j] = ' ';
                        }
                        outputline[w.ws_col] = '\0';
                        lineflag = 0;
                        for (int j = 0; j < ucounter; j++) {
                            cout << "enr for loop2" << endl;
                            for (int k = underline[0][j]; k < underline[0][j] + underline[1][j]; k++) {
                                cout << "enr for loop3" << endl;
                                outputline[k] = '^';
                            }
                        }
                        ucounter = 0;
                        cout << outputline;
                        free(outputline);
                    }
                    continue;
                }
                cout << temp << " ";
                temp = strtok(NULL, " \t\n");
                counter++;
            }
            cout << endl;
            free(line);
        }
        delete(heap);
        delete(scorelist);
        cout << endl;
    }
}



void df(TrieNode* trie) {
    char* token2;
    token2 = strtok(NULL, " \t\n");
    if(token2!=NULL){
        cout << token2 << " " << trie->dsearchword(token2,0) << endl;
    }
    else{
        char* buffer= (char*)malloc(256*sizeof(char));
        trie->dsearchall(buffer,0);
        free(buffer);
    }
    token2=NULL;
}




int tf(char* token, TrieNode* trie) {
    char*token2;
    token2=strtok(NULL," \t\n");
    if(token2==NULL){
        return -1;
    }
    for(int l=0;l<strlen(token2);l++){
        if(!(isdigit(token2[l]))){
            token2=NULL;
            return -1;
        }
    }
    int id=atoi(token2);
    token2=strtok(NULL," \t\n");
    if(token2==NULL){
        return -1;
    }
    cout << id << " " << token2 << " " << trie->tfsearchword(id,token2,0) << endl;
    return 0;
}