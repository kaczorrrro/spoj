#include <iostream>
#include <string>

using namespace std;

int main() {
  int a;
  while (true) {
    scanf_s("%d", &a);
    if (a == 42)
      break;
    else
      cout << a << endl;
  }

  for (auto i = 1; i < 10; i++) i = i;

  system("pause");
  return 0;
}