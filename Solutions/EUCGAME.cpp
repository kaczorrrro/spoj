// Gra Euklidesa
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

int euclid(int a, int b) {
  if (b % a == 0) return a * 2;
  return euclid(b % a, a);
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    std::cin >> a >> b;
    std::cout << euclid(a, b) << std::endl;
  }
}
