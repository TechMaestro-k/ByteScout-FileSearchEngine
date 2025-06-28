#include "SearchEngine.h"
using namespace std;

int inputmanager(char* input, TrieNode* trie, Mymap* map, int k) {
    char* token = strtok(input, " \t\n");
    if (token == NULL) {
        cout << "Error: Invalid input" << endl;
        return -1;
    }
    if (!strcmp(token, "/search"))
        search(token, trie, map, k);
    else if (!strcmp(token, "/df"))
        df(trie);
    else if (!strcmp(token, "/tf")) {
        if (tf(token, trie) == -1)
            return -1;
    } else if (!strcmp(token, "/exit")) {
        cout << "Exiting.." << endl;
        return 2;
    } else {
        return -1;
    }
    return 1;
}

int main(int argc, char** argv) {
    if (argc != 5 || strcmp(argv[1], "-d") || strcmp(argv[3], "-k")) {
        cout << "wrong arguments" << endl;
        return -1;
    }

    int lineCounter = 0;
    int maxLength = -1;
    int k = atoi(argv[4]);

    if (read_sizes(&lineCounter, &maxLength, argv[2]) == -1) {
        cout << "read_sizes failed" << endl;
        return -1;
    }

    Mymap* mymap = new Mymap(lineCounter, maxLength);
    TrieNode* trie = new TrieNode();

    if (read_input(mymap, trie, argv[2]) == -1) {
        cout << "read_input failed" << endl;
        delete mymap;
        delete trie;
        return -1;
    }

    cout << "database ready" << endl;
    char* input = NULL;
    size_t inputLength = 0;
    while (1) {
        getline(&input, &inputLength, stdin);
        int ret = inputmanager(input, trie, mymap, k);
        if (ret == -1) {
            cout << "wrong input" << endl;
        } else if (ret == 2) {
            free(input);
            break;
        }
        free(input);
        input = NULL;
        inputLength = 0;
    }

    delete mymap;
    delete trie;
    return 1;
}