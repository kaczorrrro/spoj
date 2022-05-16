// Równanie kwadratowe
#include <iostream>

int main() {
  double a, b, c;
  while (std::cin >> a >> b >> c) {
    double delta = b * b - 4 * a * c;
    if (delta < 0)       std::cout << 0 << std::endl;
    else if (delta == 0) std::cout << 1 << std::endl;
    else                 std::cout << 2 << std::endl;
  }
}
