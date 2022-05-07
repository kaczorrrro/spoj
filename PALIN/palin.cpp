#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class BigInt {
 public:
  BigInt(string number) {
    for (auto it = number.rbegin(); it != number.rend(); ++it) {
      char& c = *it;
      data.push_back(c - '0');
    }
  }

  BigInt& operator++() {
    bool carry = true;
    for (char& c : data) {
      if (c == 9) {
        c = 0;
      } else {
        c++;
        carry = false;
        break;
      }
    }
    if (carry) data.push_back(1);

    return *this;
  }

  string str() const {
    std::stringstream ss;
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
      char c = *it;
      ss << static_cast<char>(c + '0');
    }
    return ss.str();
  }

  bool isPalindrome() const {
    bool pal = true;
    for (int i = 0; pal && i < data.size() / 2; i++)
      if (data[i] != data[data.size() - i - 1]) pal = false;
    return pal;
  }

  bool operator==(const BigInt& b) {
    if (b.data.size() != this->data.size()) return false;
    for (int i = 0; i < data.size(); i++)
      if (this->data[i] != b.data[i]) return false;
    return true;
  }

  bool operator!=(const BigInt& b) { return !(*this == b); }

  void turnIntoPalindrome() {
    bool incremented = false;
    int numElems = data.size();
    if (numElems % 2 == 0) {
      // data | data
      int middleMoreSignificant =
          numElems / 2;  // no real middle element exists here
      bool findingMode = true;
      for (int i = 0; i < middleMoreSignificant;
           i++)  // middleMoreSignificant = half elemnets
      {
        int leftPos = moreSignificantBit(middleMoreSignificant, i);
        // here left and right are like with hand written digith MSB---LSB
        char& left = data[leftPos];
        char& right = data[symmetric(leftPos)];
        if (findingMode) {
          if (left != right) {
            if (right > left) incrementMiddle(middleMoreSignificant);

            right = left;
            findingMode = false;
          }
        } else  // copymode
        {
          right = left;
        }
      }
    } else {
      // data middle data
      int middle = numElems / 2;
      bool findingMode = true;
      for (int i = 1; i <= middle; i++) {
        int leftPos = moreSignificantBit(middle, i);

        // here left and right are like with hand written digith MSB---LSB
        char& left = data[leftPos];
        char& right = data[symmetric(leftPos)];
        if (findingMode) {
          if (left != right) {
            if (right > left) incrementMiddle(middle);

            right = left;
            findingMode = false;
          }
        } else  // copymode
        {
          right = left;
        }
      }
    }
  }

 private:
  std::vector<char> data;  // LSB---MSB

  int symmetric(int pos) const { return data.size() - 1 - pos; }

  /*
   * Here middle can be real middle or middle more significant
   */
  void incrementMiddle(int middle) {
    int middleMoreSignificant = middle;
    int middleLess;

    while (true) {
      middleLess = symmetric(middleMoreSignificant);

      if (data[middleMoreSignificant] != 9) {
        // simple increment would doubly increment our value in case middleMore
        // = middleLess
        char newValue = data[middleMoreSignificant] + 1;
        data[middleMoreSignificant] = newValue;
        data[middleLess] = newValue;
        break;
      }
      data[middleMoreSignificant] = 0;
      data[middleLess] = 0;
      middleMoreSignificant = moreSignificantBit(middleMoreSignificant, 1);
    }
  }

  static int moreSignificantBit(int pos, int shift) { return pos + shift; }
};

std::ostream& operator<<(std::ostream& ostr, const BigInt& b) {
  cout << b.str();
  return ostr;
}

void test(int count) {
  std::random_device rd;
  std::mt19937 r_engine(rd());
  std::uniform_int_distribution<int> int_distribution(0, (int)1e8);
  for (int i = 0; i < count; i++) {
    int randomInt = int_distribution(r_engine);
    BigInt fast(std::to_string(randomInt));
    ++fast;
    BigInt naive = fast;

    fast.turnIntoPalindrome();
    while (!naive.isPalindrome()) ++naive;

    if (fast != naive)
      cout << endl
           << "For " << randomInt << " expected " << naive << " but got "
           << fast << endl;

    if (i % (count / 100) == 0) cout << i / (double)count * 100 << "\r";
  }
  cout << endl;
  exit(0);
}

int main() {
  // 0.06 -> 0.02
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // test(100000);

  int iters;
  cin >> iters;

  for (int i = 0; i < iters; i++) {
    string line;
    cin >> line;
    BigInt b(line);
    ++b;
    b.turnIntoPalindrome();
    cout << b << endl;
  }

  return 0;
}
