#include <iostream>

int GCD(int a, int b) {
  if (b == 0) return a;
  else return GCD(b, a % b);
}

int main() {
  { int n; std::cin >> n; }
  int a, b;
  while (std::cin >> a >> b) {
    std::cout << a * b / GCD(a, b) << std::endl;
  }
}