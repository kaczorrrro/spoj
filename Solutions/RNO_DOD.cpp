#include <iostream>

int main() {
  int cases;
  std::cin >> cases;

  for (int c = 0; c < cases; c++) {
    int n;
    std::cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      int val;
      std::cin >> val;
      sum += val;
    }
    std::cout << sum << std::endl;
  }
}