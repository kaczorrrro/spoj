import sys
def f(x):
	from math import factorial
	i = 0
	x = factorial(x)
	while x%10 == 0:
		i+=1
		x/=10
	return i
print f(int(sys.argv[1]))