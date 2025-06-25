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
        IDF[i] = log10((double)map->getSize() - (double)trie->dsearchword(token, 0) + 0.5) /
                 ((double)trie->dsearchword(token, 0) + 0.5);
        trie->search(warray[i], 0, scorelist);
        token = strtok(NULL, " \t\n");
    }
    double avgdl = 0;
    for (int m = 0; m < map->getSize(); m++) {
        avgdl += map->getLength(m);
    }
    avgdl /= (double)map->getSize();
    cout << "Debug: Average document length: " << avgdl << endl;
    double score = 0;
    Scorelist* tempList = scorelist;
    Maxheap* heap = new Maxheap(k);
    int ceil = 0;
    while (tempList != NULL) {
        for (int l = 0; l < i; l++) {
            score = IDF[l] * ((double)trie->tfsearchword(tempList->getid(), warray[l], 0) * (k1 + 1.0)) /
                    ((double)trie->tfsearchword(tempList->getid(), warray[l], 0) +
                     k1 * (1.0 - b + b * ((double)map->getLength(tempList->getid()) / (double)avgdl)));
            heap->insert(score, tempList->getid());
            score = 0;
            tempList = tempList->getnext();
            ceil++;
        }
        if (ceil > k) ceil = k;
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if (w.ws_col <= 0) {
            cout << "Error: Invalid window size" << endl;
            break;
        }
        for (int l = 0; l < ceil; l++) {
            int id = heap->getid();
            if (id == -1) break;
            double score = (double)heap->remove();
            cout << "Debug: Processing document ID: " << id << ", score: " << score << endl;
            char* line = (char*)malloc(map->getBufferSize() * sizeof(char));
            char* document = map->getDocument(id);
            if (document == NULL) {
                cout << "Error: Document not found for ID " << id << endl;
                free(line);
                continue;
            }
            strcpy(line, document);
            char* temp;
            temp = strtok(line, " \t\n");
            if (temp == NULL) {
                cout << "Error: Failed to tokenize document" << endl;
                free(line);
                continue;
            }
            int currlength = 0;
            int counter = 0;
            int newline = 0;
            int lineflag = 0;
            int** underline = (int**)malloc(2 * sizeof(int*));
            underline[0] = (int*)malloc(100 * sizeof(int));
            underline[1] = (int*)malloc(100 * sizeof(int));
            int ucounter = 0;
            while (temp != NULL) {
                cout << "Debug: Processing word: " << temp << endl;
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
                        underline[0][ucounter] = currlength; // Start position
                        underline[1][ucounter] = strlen(temp); // Length
                        ucounter++;
                        lineflag = 1;
                        break;
                    }
                }
                currlength += strlen(temp) + 1;
                if (currlength - 1 >= w.ws_col) {
                    currlength = 0;
                    newline = 1;
                    cout << endl;
                    if (lineflag) {
                        char* outputline = (char*)malloc((w.ws_col + 1) * sizeof(char));
                        for (int j = 0; j < w.ws_col; j++) {
                            outputline[j] = ' ';
                        }
                        outputline[w.ws_col] = '\0';
                        for (int j = 0; j < ucounter; j++) {
                            for (int v = underline[0][j]; v < underline[0][j] + underline[1][j]; v++) {
                                outputline[v] = '^';
                            }
                        }
                        cout << outputline << endl;
                        free(outputline);
                        ucounter = 0;
                        lineflag = 0;
                    }
                    continue;
                }
                cout << temp << " ";
                temp = strtok(NULL, " \t\n");
                counter++;
            }
            cout << endl;
            free(line);
            free(underline[0]);
            free(underline[1]);
            free(underline);
        }
        delete heap;
        delete scorelist;
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