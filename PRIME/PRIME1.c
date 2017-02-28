/*
 *Something wasn't working here so there is lots od debug code that I'll have to clean one day
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

int isPrime(int n);
int nonPrime(int n, int tests);
int gcd(int a, int b);
int moduloExponent(int base, int exp, int mod);
int test();
void timer_start();
void timer_end();
void timer_print(char* info);
int min(int a, int b);
int max(int a, int b);
int naiveIsPrime(int n);
int nonPrimeMiller(int a, int b);

//int counter = 0;
int main(int argc, char* argv[]){
	srand(100);
	test(argc);
	return 0;
	int rounds;
	scanf("%d",&rounds);
	int min, max;
	//int* failPointer = 3248239;
	for (int ii=0;ii<rounds;ii++){
		scanf("%d %d", &min, &max);
		for (int i=min; i<=max; i++){
			// if (i< 100 &&nonPrimeMiller(i,5) == naiveIsPrime(i)){
			// 	*failPointer = 110;
			// 	//counter=counter;
			// }
			if (!nonPrimeMiller(i,5)){
				printf("%d\n",i);
			}
		}
		printf("\n");	
		//printf("%d\n",counter);	
	}
}
int TESTS = 30;
int isPrime(int n){
	if (n==1)
		return 0;
	if (n == 2)
		return 1;
	if (nonPrime(n,TESTS))
		return 0;

	int nSqrt = (int)sqrt(n);
	
	for (int i=2;i<=nSqrt+1;i++)
		if (n%i == 0){
			//counter++;
			//printf("%d ", n);
			return 0;
		}
	return 1;
}

int nonPrime(int n, int tests){
	if (n<4)
		return 0;
	for (int i=0;i<tests;i++){
		
		int a = (rand()%min((n-2),1000000)+2);

		if (gcd(n,a) != 1) 
			continue;
		if (moduloExponent(a,n-1, n) != 1){
			return 1;
		}	
	}
	return 0;
}

int list [] = {36, 37, 5, 4459, 10, 179228, 34, 15, 181, 6, 2682, 268199, 8, 5300, 20, 3955971, 13, 128, 3456, 406568, 2624731, 2318218, 3622, 9446, 383, 96, 4993, 1220192, 108, 4, 937, 6482, 26105, 108, 3857, 7, 31, 890438, 1600, 4003, 1199771, 82, 872252, 3305, 916431, 49844, 442609, 326646, 7037, 98, 134299, 8295, 36520, 292, 18496, 6683, 528011, 28191, 425591, 5, 108, 73, 99, 6700, 117001, 19, 10, 224462, 3058, 15, 2912434, 86301, 5, 699051, 315899, 110, 405492, 253, 14943, 243511, 337022, 311, 113, 2393048, 218, 555521, 30, 469912, 12, 62, 14, 454915, 85, 445, 90070, 319, 1098385, 45, 181, 1252585};

int nonPrimeMiller(int n, int tests){
	if (n<1000)
		return !naiveIsPrime(n);

	for (int i=0;i<tests;i++){
		int a = min(list[i],n-i);
		//printf("%d\n",a);
		int tempN = n-1;
		int s = 0;
		while (~tempN & 1){
			tempN /=2;
			s++;
		}
		int d = tempN;
		//printf("a: %d\n",d);
		if (n==46411 && a == 5)
			printf("%d %d %d\n", a, d,n);

		if (moduloExponent(a,d,n) == 1)
			continue;
		if (n==46411 && a == 5)
			printf("tego nie ma\n");
		int failure = 0;
		for (int r=0;r<s;r++){
			//printf("mod exp: %d\n", moduloExponent(a,pow(2,r)*d, n));
			if (moduloExponent(a,pow(2,r)*d, n) == n-1){
				failure = 1;
				break;
			}
		}
		if (!failure)
			return 1;
	}

	return 0;
}

int max(int a, int b){
	return a>b?a:b;
}

int min(int a, int b){
	return a>b?b:a;
}


int gcd(int a, int b){
	if (a == 0 || b ==0)
		return -1;
	if (max(a,b)%min(a,b) == 0)
		return min(a,b);
	double proportion = max(a,b)/(double)min(a,b);
	if (proportion>2){
		if (a>b)
			a = a-b*(int)proportion;
		else
			b = b-a*(int)proportion; 
	}
	while (a!=b){
		if (a>b)
			a-=b;
		else
			b-=a;
	}
}

int maxPower(unsigned int n){
	unsigned int ui = 0x80000000;
	int maxPower = -1;
	for (int i=31;i>=0;i--){
		if ( ui & n ){
			maxPower = i;
			break;
		}
		ui >>=1;
	}
	return maxPower;
}

int moduloExponent(int base, int exp, int mod){
	base = base>=mod?base%mod:base;
	int maxPow = maxPower(exp);


	long values [maxPow+1];
	values[0] = base;
	//printf("values %d: %d\n",0, values[0] );
	for (int i=0;i<maxPow;i++){
		values[i+1] = (values[i]*(long)values[i])%mod;
		//printf("values %d: %d\n",i+1, values[i+1] );
		if (base == 5 && exp == 23205 && mod == 46411)
			printf("value %d: %d\n", i+1, values[i+1]);
	}


	long result = 1;
	for (int i=0;i<=maxPow;i++)
	{
		if (exp & 1<<i)
			result =  (result*values[i])%mod;
	}


	return (int)result;
}

int test(int argc){
	// for (int i=0;i<1000000000;i++)
	// 	if (!nonPrimeMiller(i,3) && !naiveIsPrime(i))
	// 		printf("Fail on %d!\n",i);
	// printf("miller composite:%d, naive prime: %d\n",nonPrimeMiller(999999937,5),naiveIsPrime(999999937));
	//non prime miller tests
	printf("%d from miller, %d from naive for 46411\n",nonPrimeMiller(46411,5),naiveIsPrime(46411) );

	//powers test:
	int powered [] = {36, 36, 10, 4459, 10, 179228, 34, 15, 181, 6, 2682, 268199, 8, 5300, 20, 3955971, 13, 128, 3456, 406568, 2624731, 2318218, 3622, 9446, 383, 96, 4993, 1220192, 108, 4, 937, 6482, 26105, 108, 3857, 7, 31, 890438, 1600, 4003, 1199771, 82, 872252, 3305, 916431, 49844, 442609, 326646, 7037, 98, 134299, 8295, 36520, 292, 18496, 6683, 528011, 28191, 425591, 5, 108, 73, 99, 6700, 117001, 19, 10, 224462, 3058, 15, 2912434, 86301, 5, 699051, 315899, 110, 405492, 253, 14943, 243511, 337022, 311, 113, 2393048, 218, 555521, 30, 469912, 12, 62, 14, 454915, 85, 445, 90070, 319, 1098385, 45, 181, 1252585};
	int maxPowers [] = {5, 5, 3, 12, 3, 17, 5, 3, 7, 2, 11, 18, 3, 12, 4, 21, 3, 7, 11, 18, 21, 21, 11, 13, 8, 6, 12, 20, 6, 2, 9, 12, 14, 6, 11, 2, 4, 19, 10, 11, 20, 6, 19, 11, 19, 15, 18, 18, 12, 6, 17, 13, 15, 8, 14, 12, 19, 14, 18, 2, 6, 6, 6, 12, 16, 4, 3, 17, 11, 3, 21, 16, 2, 19, 18, 6, 18, 7, 13, 17, 18, 8, 6, 21, 7, 19, 4, 18, 3, 5, 3, 18, 6, 8, 16, 8, 20, 5, 7, 20};
	for (int i=0;i<100;i++)
		if (maxPower(powered[i]) != maxPowers[i] )
			printf("Error, value: %d, got %d, expected %d\n", powered[i],maxPower(powered[i]), maxPowers[i]);
	
	
	int bases [] = {488, 185, 101, 67, 280, 66, 603, 983, 864, 527, 346, 491, 923, 214, 315, 720, 248, 287, 904, 854, 421, 478, 682, 735, 556, 159, 328, 688, 209, 25, 87, 135, 197, 431, 28, 524, 108, 264, 66, 955, 259, 455, 168, 96, 10, 842, 122, 253, 168, 27, 229, 340, 78, 915, 322, 400, 318, 86, 445, 902, 575, 787, 707, 706, 122, 358, 784, 471, 682, 653, 180, 314, 472, 229, 114, 523, 95, 271, 364, 181, 321, 821, 736, 310, 328, 918, 206, 996, 690, 869, 279, 899, 428, 293, 294, 164, 402, 558, 400, 121};
	int pows [] = {149, 800, 772, 190, 426, 365, 745, 800, 209, 414, 835, 190, 766, 566, 304, 370, 81, 837, 601, 238, 115, 511, 689, 215, 561, 550, 233, 581, 206, 330, 887, 895, 488, 979, 380, 892, 694, 707, 523, 503, 91, 555, 734, 88, 931, 920, 466, 169, 98, 546, 456, 449, 684, 436, 782, 597, 408, 451, 49, 339, 602, 915, 70, 238, 331, 99, 585, 874, 211, 231, 561, 465, 170, 192, 308, 390, 395, 351, 77, 65, 742, 670, 184, 611, 352, 505, 375, 227, 789, 104, 561, 545, 735, 414, 946, 761, 516, 857, 31, 424};
	int mods [] = {206253, 688179, 272713, 885054, 182370, 304415, 21106, 252334, 333477, 335160, 897764, 219105, 560288, 345942, 171798, 516329, 978986, 573912, 324287, 351865, 934375, 49041, 968341, 636043, 582105, 907816, 417106, 438535, 158082, 387691, 374371, 347056, 558392, 956281, 138400, 718973, 989361, 575908, 633951, 884154, 228334, 705833, 829479, 90133, 13644, 307281, 885634, 505731, 27224, 574551, 826053, 733594, 869981, 15137, 154025, 123053, 892112, 168291, 68924, 123078, 708082, 146521, 864220, 755968, 204947, 819505, 476073, 505609, 349925, 961666, 331349, 658126, 386013, 493404, 955048, 6869, 398954, 933540, 944859, 689068, 890826, 586070, 150794, 554857, 685289, 244886, 911136, 120633, 885386, 437057, 954060, 691884, 497599, 100108, 999472, 642055, 55510, 891117, 508942, 979231};
	int res [] = {129254, 62710, 152758, 730627, 67270, 101096, 11733, 64363, 249804, 124489, 300856, 167746, 275977, 51484, 168237, 141428, 494212, 356399, 192277, 65801, 459051, 17353, 788568, 77021, 522856, 558665, 226868, 400293, 20809, 358137, 351308, 63159, 357025, 369602, 74176, 423944, 526014, 525692, 383121, 546685, 119179, 326342, 690375, 35512, 6364, 268147, 132948, 456133, 11088, 53631, 676930, 230262, 293707, 5614, 6084, 33524, 327328, 124475, 28521, 67970, 39151, 21031, 144109, 679168, 140195, 123402, 415063, 375976, 230268, 5093, 16373, 186780, 231043, 164029, 213728, 3108, 322101, 765751, 236674, 473965, 170823, 308461, 21722, 458049, 169822, 139340, 292928, 90885, 701200, 390744, 708039, 585827, 196470, 39201, 657680, 54804, 13196, 313803, 1044, 697081};
	for (int i=0;i<100;i++){
		int me = moduloExponent(bases[i],pows[i],mods[i]);
		if ( me != res[i]){
			printf("ModExp error: %d **%d mod %d, got %d expected %d\n",bases[i],pows[i],mods[i],me, res[i] );
		}
	}

	for (int i=0; i<1000;i++){
		int value;
		//scanf("%d",&value);
		value=rand();
		if (value<=0)
			continue;
		if (nonPrime(value, 20) && naiveIsPrime(value) != 0)
			printf("nonPrime error %d: non prime said %d, naiveIsPrime %d",value,nonPrime(value, 20),naiveIsPrime(value) );
	}
	printf("Koniec\n");
}

int naiveIsPrime(int n){
	if (n==1)
		return 0;
	if (n == 2)
		return 1;

	int nSqrt = (int)sqrt(n);
	
	for (int i=2;i<=nSqrt+1;i++)
		if (n%i == 0)
			return 0;
	return 1;
}



// struct timeval tval_before, tval_after;
// void timer_start(){
// 	gettimeofday(&tval_before, NULL);
// }

// void timer_end(){
// 	gettimeofday(&tval_after, NULL);
// }

// void timer_print(char* info){
// 	struct timeval tval_result;
// 	timersub(&tval_after, &tval_before, &tval_result);
// 	printf("%s: Time elapsed: %ld.%06ld\n",info,(long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
// }
