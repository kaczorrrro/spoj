#include <iostream>

int main() {
  std::string val;
  std::cin >> val;
  for (char c : val) {
    int digit = c - '0';
    if (digit % 2 == 0) {
      std::cout << "Tak" << std::endl;
      return 0;
    }
  }
  std::cout << "Nie" << std::endl;
  return 0;
}