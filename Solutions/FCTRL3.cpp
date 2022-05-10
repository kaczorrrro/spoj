#include <iostream>

int factorial_n_mod100(int n) {
  // 10! = 2 * 5 * 10 * ... = 100 * ...
  if (n >= 10)
   return 0;

  int acc = 1;
  for (int i = 2; i <= n; i++)
    acc *= i;
  return acc % 100;
}

int main() {
  int n;
  std::cin >> n;

  int input;
  while (std::cin >> input) {
    int res = factorial_n_mod100(input);
    std::cout << res / 10 % 10 << " " << res % 10 << std::endl;
  }
}