#include <iostream>
#include <string>
#include <sstream>
#include <math.h> 

using namespace std;

int powers[13];

int numZerosFromFactorial(int input)
{
	int outVal = 0;

	//as long as x contains 'temp' multiples of powers, add temp
	for (int i = 0; int temp = input / powers[i]; i++) {
		outVal += temp;
	}

	return outVal;
}

int naiveZerosFromFactorial(int input)
{
	long long value = 1;
	for (int i = 1; i <= input; i++)
		value *= i;
	int count = 0;
	while(value % 10 == 0 && value > 0)
	{
		count++;
		value /= 10;
	}
	return count;
}

void test()
{
	for (int i = 0; i < 40; i++)
		if (naiveZerosFromFactorial(i) != numZerosFromFactorial(i))
			cout << "Error for " << i << " expected " << naiveZerosFromFactorial(i) << " got " << numZerosFromFactorial(i) << endl;
	exit(0);
}

int main() {
	// 0.11->0.08
	ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	//initialize powers of 5
	for (int i = 0; i < 13; i++) {
		powers[i] = (int)pow(5, i + 1);
	}

	//test();

	int cases;
	cin >> cases;

	
	for (int ii = 0; ii < cases; ii++) {
		int x;
		cin >> x;
		int result = numZerosFromFactorial(x);
		cout << result << endl;
	}


}