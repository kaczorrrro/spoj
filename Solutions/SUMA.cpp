#include <iostream>

int main() {
  int acc = 0;
  int n;
  while (std::cin >> n)
    acc += n;
  std::cout << acc << std::endl;
}
