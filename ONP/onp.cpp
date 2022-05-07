#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool parseLine(string &data);
pair<int, int> findCorespodingParAndOper(string &data, int parInd);

int main() {
  int tests;
  cin >> tests;
  stringstream ss;

  for (int ii = 0; ii < tests; ii++) {
    string data;
    cin >> data;
    while (parseLine(data))
      ;  // ; is intended here
    data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
    ss << data << endl;
  }

  cout << ss.str();
}

bool parseLine(string &data) {
  int firstPar = data.find('(');
  if (firstPar == string::npos) return false;

  pair<int, int> parAndOper = findCorespodingParAndOper(data, firstPar);
  int &secondPar = parAndOper.first;
  int &oper = parAndOper.second;

  data[firstPar] = ' ';
  data[secondPar] = data[oper];
  data[oper] = ' ';
  return true;
}

pair<int, int> findCorespodingParAndOper(string &data, int parInd) {
  int openedParCount = 0;
  pair<int, int> outPair = {-1, -1};

  for (int i = parInd + 1, n = data.length(); i < n; i++) {
    char c = data[i];
    switch (c) {
      case ')':
        if (openedParCount == 0) {
          outPair.first = i;
          return outPair;
        } else
          openedParCount--;
        break;
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        if (openedParCount == 0) outPair.second = i;
        break;
      case '(':
        openedParCount++;
        break;
    }
  }

  return outPair;
}