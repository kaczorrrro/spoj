#include <iostream>
#include <math.h>

bool is_prime(int input) {
  if (input == 1) return false;
  // input is <= 10000, safe to go with float
  int last_to_check = (int)std::sqrt(input);
  for (int i = 2; i <= last_to_check; i++)
    if (input % i == 0) return false;
  return true;
}

int main() {
  int n;
  std::cin >> n;

  int input;
  while (std::cin >> input) {
    std::cout << (is_prime(input) ? "TAK" : "NIE") << std::endl;
  }
}