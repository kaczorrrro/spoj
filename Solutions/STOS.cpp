#include <iostream>
#include <vector>

int main() {
  std::vector<int> stack;
  char c;
  while (std::cin >> c) {
    if (c == '+') {
      int digit;
      std::cin >> digit;
      if (stack.size() < 10) {
        stack.push_back(digit);
        std::cout << ":)\n";
      } else {
        std::cout << ":(\n";
      }
    } else if (c == '-') {
      if (stack.empty()) {
        std::cout << ":(\n";
      } else {
        std::cout << stack.back() << '\n';
        stack.pop_back();
      }
    }
  }
}