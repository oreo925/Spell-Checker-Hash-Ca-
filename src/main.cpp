#include <iostream> 
#include <fstream> 
#include "HashSet.h"

#define WORD_LIST_FILE  "word_list.txt"
#define WORD_COUNT      59000

void LoadWords(HashMap<std::string, std::string> &hashmap);
bool ErrorCheckFile(const std::string &infile, HashMap<std::string, std::string> &hashmap, size_t &wordCount);
void ToLowerCase(std::string &word);

int main(int  argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <input file to check>" << std::endl;
    return 1;
  }

  HashMap<std::string, std::string> hashmap(WORD_COUNT);
  std::cout << "Created the hashmap" << std::endl;

  LoadWords(hashmap);
  std::cout << "Loaded the words " << hashmap.Size() << std::endl;

  size_t wordCount = 0;
  std::string filename = argv[1];
  ErrorCheckFile(filename, hashmap, wordCount);
  std::cout << wordCount << " words misspelled" << std::endl;
}


void LoadWords(HashMap<std::string, std::string> &hashmap) {
  std::ifstream wordList(WORD_LIST_FILE);
  std::string word;
  while (wordList >> word) {
    if (!hashmap.Insert(word, word)) {
      std::cout << "ERROR: Failed to insert " << word << std::endl;
      exit(1);
    }
  }
}

bool ErrorCheckFile(const std::string &infile, HashMap<std::string, std::string> &hashmap, size_t &wordCount) {
  std::ifstream infileStream(infile);
  std::string word;

  bool correct = true;
  while (infileStream >> word) {
    ToLowerCase(word);

    if (!hashmap.Get(word)) {
      if (correct)
        std::cout << "Misspelled word(s): " << std::endl;

      std::cout << word << std::endl;
      correct = false;
      ++wordCount;
    }
  }

  return correct;
}

void ToLowerCase(std::string &word) {
  for (size_t i = 0; i < word.length(); ++i) {
    word[i] = tolower(word[i]);
  }
}
