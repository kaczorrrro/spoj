#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int invert(string& s);
string invert(int x);


int main() {
	stringstream ss;
	int cases;
	cin >> cases;

	string xS, yS;
	int x, y;
	for (int tempI = 0; tempI < cases; tempI++) {
		cin >> xS >> yS;
		x = invert(xS);
		y = invert(yS);
		ss << invert(x + y)<< endl;
	}
	cout << ss.str();
	return 0;
}

int invert(string& s) {
	return stoi(string(s.rbegin(), s.rend()));
}

string invert(int x) {
	while (x % 10 == 0 && x != 0)
		x /= 10;
	string temp = to_string(x);
	return string(temp.rbegin(), temp.rend());
}
