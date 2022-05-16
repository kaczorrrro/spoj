// Obżartuchy
#include <iostream>

template <typename T>
T round_up(T a, T b) {
  return (a + b - T(1)) / b * b;
}

void process_case() {
  int n_people, cookies_per_pack;
  std::cin >> n_people >> cookies_per_pack;
  int cookies_needed = 0;

  for (int i = 0; i < n_people; i++) {
    int seconds_per_cookie;
    std::cin >> seconds_per_cookie;
    cookies_needed += (24 * 3600) / seconds_per_cookie;
  }

  std::cout << round_up(cookies_needed,  cookies_per_pack) / cookies_per_pack  << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    process_case();
}