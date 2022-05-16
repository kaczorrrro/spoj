#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <sstream>

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::stringstream ss (line);
    std::string word;
    bool capitalize = false;
    while (ss >> word) {
      if (capitalize)
        word[0] = toupper(word[0]);
      capitalize = true;
      std::cout << word;
    }
    std::cout << "\n";
  }
}