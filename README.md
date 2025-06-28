# ByteScout - File Search Engine
A file search engine in C++ using Tries, List Node and Priority Queue

## 💻 Installation

`!!! Having a GCC compiler is a must. !!!` <br>

### Initializing

```console
$ git clone https://github.com/TechMaestro-k/ByteScout-FileSearchEngine.git
$ cd ByteScout-FileSearchEngine./
$ make
```

## Running Commands

Before running the commands, it's important to understand the following options:

- `-d [document location]`: Specifies the location of the document or dataset to be used for searching. Replace `[document location]` with the actual path to your document or dataset.

- `-k [number]`: Determines how many of the top results (e.g., documents) should be displayed in the output. Replace `[number]` with the desired value of `k`.

### Starting the Engine

To start the engine, one can choose any of the following commands

1) To run the search engine with a sample dataset and display the top `k` results (e.g., `k = 2`):
```bash
./searchengine -d sampledataset.txt -k 2
```

2) To run the search engine with memory leak checking using Valgrind(if installed):
```bash
valgrind --leak-check=yes ./searchengine -d sampledataset.txt -k 2
```

## Functional Commands

| Command                | Usage              | Explanation                                       |
|------------------------|--------------------|---------------------------------------------------|
| `/tf [line_NO] [word]` | `/tf 0 hi`         | Tells the frequency of occurrence for the given word in the specified line. |
| `/df [word]`           | `/df hello`        | Indicates in how many articles the word occurs in the dataset. |
| `/df`                  | `/df`              | Provides the frequency of occurrence for every word in all the documents. |
| `/search [query string]` | `/search hello world` | Searches the specified string and returns the document, logarithmic score, and line (with the underlined word) in the given order. |
| `/exit`                |                    | Exits the program. |


