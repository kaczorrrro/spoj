#include <iostream>

using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;

  switch (n) {
    case 0:
      cout << 0;
      return 0;
    case 1:
      cout << "NIE";
      return 0;
    case 2:
      cout << "NIE";
      return 0;
  }

  if (n % 2 != 0) {         // 3
    int halfIters = n / 2;  // 2
    int halfValue = n / 2;  // 1

    for (int i = 1; i <= halfIters; i++) {
      cout << halfValue + i << " " << halfValue - i << " ";
    }
    cout << n << " " << halfValue << endl;
  } else {
    int halfIters, halfValue;
    halfIters = halfValue = n / 2;

    for (int i = 1; i <= halfIters; i++) {
      cout << halfValue - i << " " << halfValue + i << " ";
    }
    cout << halfValue << endl;
  }
}