## Functional Commands
Cmds - Usage - Explain

/tf [line_NO] [word] - /tf 0 hi - Tells the frequency of occurence for given word in the given line
/df [word] - /df hello - tells in how many articles the word occurs in the dataset.
/df - /df  - Tells the frequency of occurance of every word in all th documents.
/search [query string] - /search hello world - searches the given string and returns the [ document ] [logarithmic score] and line(along with underlined word in given order)

/exit - exits the program


## Running Commands
1) ./searchengine -d sampledataset.txt -k 2
2) valgrind --leak-check=yes ./searchengine -d sampledataset.txt -k 2
