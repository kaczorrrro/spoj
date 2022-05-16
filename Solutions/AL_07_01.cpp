#include <iostream>
#include <vector>

char buffer [500 * 20];
void process_case() {
  std::cin.getline(buffer, 500*20);
  int sum = 0;
  int tmp = 0;
  bool mul_next = false;

  for (int i = 0; buffer[i]; i++) {
    char c = buffer[i];
    if (c == '+' || c == '-' || c == '*' || c == '=') {
      int digit = buffer[i - 2] - '0';
      tmp = digit * (mul_next ? tmp : 1);
      sum += tmp * (c != '*');
      if (c == '=')
        std::cout << (sum % 2 == 0 ? "TAK" : "NIE") << std::endl;
      mul_next = c == '*';
    }
  }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string line;
  std::getline(std::cin, line);
  int n = std::stoi(line);
  for (int i = 0; i < n; i++)
    process_case();
}

// 1 =
// 1 + 2 =
// 1 - 2 =
// 1 * 2 =
// 1 + 2 + 3 =
// 1 + 2 - 3 =
// 1 + 2 * 3 =
// 1 - 2 * 3 =
// 1 - 2 - 3 =
// 1 - 2 * 3 =
// 1 * 2 + 3 =
// 1 * 2 - 3 =
// 1 * 2 * 3 =
// 1 + 2 + 3 + 4 =
// 1 + 2 + 3 - 4 =
// 1 + 2 + 3 * 4 =
// 1 + 2 - 3 + 4 =
// 1 + 2 - 3 - 4 =
// 1 + 2 - 3 * 4 =
// 1 + 2 * 3 + 4 =
// 1 + 2 * 3 - 4 =
// 1 + 2 * 3 * 4 =
// 1 - 2 + 3 + 4 =
// 1 - 2 + 3 - 4 =
// 1 - 2 + 3 * 4 =
// 1 - 2 - 3 + 4 =
// 1 - 2 - 3 - 4 =
// 1 - 2 - 3 * 4 =
// 1 - 2 * 3 + 4 =
// 1 - 2 * 3 - 4 =
// 1 - 2 * 3 * 4 =
// 1 * 2 + 3 + 4 =
// 1 * 2 + 3 - 4 =
// 1 * 2 + 3 * 4 =
// 1 * 2 - 3 + 4 =
// 1 * 2 - 3 - 4 =
// 1 * 2 - 3 * 4 =
// 1 * 2 * 3 + 4 =
// 1 * 2 * 3 - 4 =
// 1 * 2 * 3 * 4 =

