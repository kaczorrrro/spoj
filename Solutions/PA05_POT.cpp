#include <iostream>

int a_pow_b_mod_10(int a, int b) {
  a = a % 10;

  int cycle_len = 1;
  for (int tmp = a * a % 10; tmp != a;) {
    tmp = tmp * a % 10;
    ++cycle_len;
  }
  // -1, because powers are more like 1-based indexing, but we prefer 0-based indexing
  b = (b - 1) % cycle_len;

  // 1 -> 0 -> 2
  // 2 -> 1 -> 4
  // 3 -> 2 -> 8
  // 4 -> 3 -> 6 (16)
  // 5 -> 0 -> 2 (32)
  int tmp = a;
  for (int i = 0; i < b; i++)
    tmp *= a;

  return tmp % 10;
}

int main() {
  {int n; std::cin >> n;}
  int a, b;
  while (std::cin >> a >> b) {
    std::cout << a_pow_b_mod_10(a, b) << std::endl;
  }
}