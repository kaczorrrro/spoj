// Wiatraczki

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

struct Matrix {
  Matrix(int n = 0): n(n), data(n*n) {}
  char& operator()(int y, int x) { return data[y * n + x]; }
  const char& operator()(int y, int x) const { return data[y * n + x]; }
  int n;
  std::vector<char> data;
};
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  for (int y = 0; y < m.n; y++) {
    for (int x = 0; x < m.n; x++)
      out << m(y, x);
    out << '\n';
  }
  return out;
}

Matrix GetFan(bool left, const int n) {
  if (n == 0) {
    return Matrix(0);
  }
  static std::unordered_map<int, Matrix> fans_cache;
  Matrix& r = fans_cache[left * 201 + n];
  if (!r.data.empty())
    return r;

  const Matrix m = GetFan(left, n - 1);
  const int z = 2 * n - 1; // z - last pos
  r = Matrix(2 * n);
  r(0, 0) = '*';
  r(0, z) = '*';
  r(z, 0) = '*';
  r(z, z) = '*';

  for (int i = 1; i < 2 * n - 1; i++) {
    bool half = i < n;
    char c = (left ^ half) ? '.' : '*';
    r(  0,   i) = c;
    r(  i,   z) = c;
    r(  z, z-i) = c;
    r(z-i,   0) = c;
  }

  for (int y = 1; y < z; y++)
    for (int x = 1; x < z; x++)
      r(y, x) = m(y - 1, x - 1);

  return r;
}

char GetFanAt(bool left, int n, int y, int x) {
  int z = n * 2 - 1;
  bool filp = x>=n ^ y>=n ^ left;
  x = x >= n ? z - x : x;
  y = y >= n ? z - y : y;
  bool y_farther = std::abs(n - y) > std::abs(n - x);
  bool star = (y_farther ^ filp) || (x == y);
  return star ? '*' : '.';
}


Matrix GetFan2(bool left, const int n) {
  Matrix r (2 * n);

  for (int y = 0; y < 2 * n; y++)
    for (int x = 0; x < 2 * n; x++)
      r(y, x) = GetFanAt(left, n, y, x);

  return r;
}


int main() {
  int n;
  while (std::cin >> n) {
    if (n == 0)
      return 0;
    std::cout << GetFan2(n > 0, std::abs(n)) << std::endl;
  }
}

