// Problem Collatza
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int val;
    std::cin >> val;
    int steps = 0;
    for (; val != 1; steps++) {
      val = val % 2 == 0 ? val / 2 : val * 3 + 1;
    }
    std::cout << steps << std::endl;
  }
}