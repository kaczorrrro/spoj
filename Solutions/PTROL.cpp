// PTROL - ROL
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

void process_case() {
  int n;
  std::cin >> n;

  int first;
  std::cin >> first;
  for (int i = 1; i < n; i++) {
    int val;
    std::cin >> val;
    std::cout << val << " ";
  }
  std::cout << first << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    process_case();
}