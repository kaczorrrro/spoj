#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <map>

#define DEBUG(x)
//#define DEBUG(x) x

//#define Factorize FactorizeFast
#define Factorize FactorizeNaive

#define AddNextItemToSeries AddNextItemToSeriesFast
//#define AddNextItemToSeries AddNextItemToSeriesNaive

//#define PRIVATE public
//#define TESTS 1

#define PRIVATE private
#define TESTS 0

class Primes {
 public:
  void GenerateUpTo(int val) {
    while (primes.back() < val)
      AddNextPrime();
  }

  void AddNextPrime() {
    int last = primes.back();
    for (int i = last + 1; true; i++) {
      if (IsPrime(i)) {
        primes.push_back(i);
        break;
      }
    }
  }

  static bool IsPrime(int val) {
    int max = (int)std::ceil(std::sqrt(val));
    if (val == 2 || val == 3 || val == 5)
      return true;

    if (val % 2 == 0 || val % 3 == 0 || val % 5 == 0)
      return false;

    for (int i = 3; i < max; i += 2)
      if (val % i == 0)
        return false;

    return true;
  }

  std::vector<int> primes {2};
};



using FactorsArr = std::array<int, 8>;
class Factors {
 public:
  Factors() {
    // Default ctor for vector
  }



  bool IsInitialized() const {
    return factors[0] != 0;
  }

  const int* begin() const {
    return &factors[0];
  }

  const int* end() const {
    for (int i = 0; i < 8; i++)
      if (factors[i] == 0)
        return &factors[i];
    return &factors[8];
  }

  void AddFactor(int factor) {
    for (int i = 0; i < 8; i++) {
      if (factors[i] == 0) {
        factors[i] = factor;
        return;
      }
    }
  }

  static bool AreCoprime(const Factors& f0, const Factors& f1) {
    assert(f0.IsInitialized());
    assert(f1.IsInitialized());

    int f0_i = 0;
    int f1_i = 0;
    while (true) {
      DEBUG(if (f0_i >= 8 || f1_i >= 8) throw 1);
      int f0_factor = f0.factors[f0_i];
      int f1_factor = f1.factors[f1_i];
      if (f0_factor == f1_factor)
        return false;
      if (f1_factor == 0 || f0_factor == 0)
        return true;

      if (f0_factor < f1_factor)
        ++f0_i;
      if (f1_factor < f0_factor)
        ++f1_i;

      if (f0_i == 8 || f1_i == 8)
        return true;
    }
  }

  void Initialize(int number) {
    Factorize(number);
  }

PRIVATE:
  Factors(int number) {
    Factorize(number);
  }


  void FactorizeNaive(int number) {
    int factor_pos = 0;
    int test_val = 2;
    bool seen_it = false;

    while (number > 1) {
      DEBUG(if (factor_pos >= 8) throw std::runtime_error("Range exceeded");)
      if (number % test_val == 0) {
        number /= test_val;
        if (!seen_it)
          factors[factor_pos++] = test_val;
        seen_it = true;
      } else {
        test_val++;
        seen_it = false;
      }
    }
  }

  void FactorizeFast(int number) {
    static Primes primes;
    int factor_pos = 0;


    primes.GenerateUpTo(number); // maybe number / 2 ?

    int prime_idx = 0;
    bool seen_it = false;
    while (number > 1) {
      assert(prime_idx < primes.primes.size());
      int test_val = primes.primes[prime_idx];
      DEBUG(if (factor_pos >= 8) throw std::runtime_error("Range exceeded");)

      if (number % test_val == 0) {
        number /= test_val;
        if (!seen_it)
          factors[factor_pos++] = test_val;
        seen_it = true;
      } else {
        prime_idx++;
        seen_it = false;
      }
    }
    std::cout << factors[factor_pos - 1] << std::endl;
  }

  // Could be int16
  FactorsArr factors = {};
};

constexpr bool FactorsRegPrecompiled = true;
class FactorsReg {
 public:
  const Factors& GetFactors(int val) {
    if (FactorsRegPrecompiled) {
      assert(val < factors.size());
      assert(factors[val].IsInitialized());
      return factors[val];
    } else {
      if (val >= factors.size())
        factors.resize(val + 1);
      Factors& val_factors = factors[val];
      if (!val_factors.IsInitialized())
        val_factors.Initialize(val);
      return val_factors;
    }
  }

  void SieveBuild(int max) {
    assert(factors.empty());
    factors.resize(max);
    int prime = 2;
    while (prime < max) {
      for (int prime_mul = prime; prime_mul < max; prime_mul += prime) {
        factors[prime_mul].AddFactor(prime);
      }

      // Find next prime (regular num >= max that will stop the loop)
      while (prime < max && factors[prime].IsInitialized())
        prime++;
    }
  }

 PRIVATE:
  std::vector<Factors> factors;
} factors_registry;




class Series {
 public:
  bool IsAlreadyPresent(int val) {
    if (val >= in_content.size())
      in_content.resize(val + 1);
    return in_content[val] != 0;
  }

  void AddItem(int val) {
    if (val >= in_content.size())
      in_content.resize(val + 1);
    content.push_back(val);
    in_content[val] = content.size();
  }

  int StartTestVal() {
    while (IsAlreadyPresent(current_start_test_value))
      current_start_test_value++;
    return current_start_test_value;
  }

  int GetValuePosition(int val) {
    return in_content[val] - 1;
  }

  int Back() const {
    return content.back();
  }

 private:

  int current_start_test_value = 3;

  std::vector<int> content {1,2};
  // in_content is 1 based! (0 means not here)
  std::vector<int> in_content {0, 1, 2};
};


class FactorCache {
 public:
  void Add(int val) {
    const Factors& factors = factors_registry.GetFactors(val);
    for (int factor : factors) {
      factor_to_vals[factor].push_back(val);
    }
  }

  std::map<int, std::deque<int>> factor_to_vals;

 private:
  static void vec_delete(std::vector<int>& vec, int value) {
    vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
  }

} factors_cache;

int last_processed_val = 2;
int AddNextItemToSeriesFast(Series& series) {
  int last_val = series.Back();
  Factors last_val_factors = factors_registry.GetFactors(last_val);

  int smallest_val = INT_MAX;
  for (int factor : last_val_factors) {
    std::deque<int>& vals_for_factor = factors_cache.factor_to_vals[factor];

    // Cleanup junk on front
    while(!vals_for_factor.empty()) {
      int maybe_val = vals_for_factor.front();
      if (series.IsAlreadyPresent(maybe_val))
        vals_for_factor.pop_front();
      else
        break;
    }
    if (!vals_for_factor.empty() && vals_for_factor.front() < smallest_val)
      smallest_val = vals_for_factor.front();
  }

  if (smallest_val != INT_MAX) {  // Cache hit
    series.AddItem(smallest_val);
    return smallest_val;
  } else {  // Cache miss
    while (true) {
      int new_val = ++last_processed_val;
      Factors next_one_factors = factors_registry.GetFactors(new_val);
      if (!Factors::AreCoprime(last_val_factors, next_one_factors)) {
        series.AddItem(new_val);
        return new_val;
      } else {
        factors_cache.Add(new_val);
      }
    }
  }
}


int AddNextItemToSeriesNaive(Series& series) {
  int last_val = series.Back();
  const Factors last_val_factors = factors_registry.GetFactors(last_val);

  // Possible optimization: start later
  for (int test = series.StartTestVal(); true; test++) {
    if (series.IsAlreadyPresent(test))
      continue;
    const Factors& test_factors = factors_registry.GetFactors(test);
    if (!Factors::AreCoprime(last_val_factors, test_factors)) {
      series.AddItem(test);
      return test;
    }
  }
}

int GetPositionInSeries(Series& series, int value) {
  if (series.IsAlreadyPresent(value))
    return series.GetValuePosition(value);

  while (true) {
    int added_value = AddNextItemToSeries(series);
    if (added_value == value)
      return series.GetValuePosition(value);
  }
}


void RunTests();

int main() {
  std::iostream::sync_with_stdio(false);
//  int query = 300'000;
//  int limit = query * 3;
//  factors_registry.SieveBuild(limit);
//  Series series;
//  int val = GetPositionInSeries(series, query);
//  std::cout << val << std::endl;

  int elems;
  std::cin >> elems;

  int max_query = 0;
  std::vector<int> queries (elems);
  for (int i = 0; i < elems; i++) {
    std::cin >> queries[i];
    max_query = std::max(max_query, queries[i]);
  }
  int limit = max_query * 3;
  factors_registry.SieveBuild(limit);

  Series series;
  for (int val : queries) {
    int pos = GetPositionInSeries(series, val);
    std::cout << pos + 1 << std::endl;
  }

//  RunTests();
}



#if TESTS
#define assert_equal(a, b) { \
  if (!(a==b)) { \
    throw std::runtime_error(#a " != " #b); \
  } \
}

//void TestSeriesCreation() {
//  Series s;
//  AddNextItemToSeries(s); assert_equal(s.Back(), 4);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 6);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 3);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 9);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 12);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 8);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 10);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 5);
//  AddNextItemToSeries(s); assert_equal(s.Back(), 15);
//}


//void TestSeries() {
//  {  // GetFactors test
//    assert_equal(factors_registry.GetFactors(2).factors, Factors(2).factors);
//    assert_equal(factors_registry.GetFactors(4).factors, Factors(4).factors);
//    assert_equal(factors_registry.GetFactors(3).factors, Factors(3).factors);
//  }
//
//  {  // Back Test
//    Series s;
//    assert_equal(s.Back(), 2);
//    s.AddItem(4);
//    assert_equal(s.Back(), 4);
//    s.AddItem(6);
//    assert_equal(s.Back(), 6);
//  }
//
//  {  // StartTestVal Test
//    Series s;
//    assert_equal(s.StartTestVal(), 3);
//    s.AddItem(3);
//    assert_equal(s.StartTestVal(), 4);
//    s.AddItem(5);
//    assert_equal(s.StartTestVal(), 4);
//    s.AddItem(4);
//    assert_equal(s.StartTestVal(), 6);
//  }
//
//  { // Adding values
//    Series s;
//    assert_equal(s.GetValuePosition(1), 0);
//    assert_equal(s.GetValuePosition(2), 1);
//    assert_equal(s.IsAlreadyPresent(1), true);
//    assert_equal(s.IsAlreadyPresent(2), true);
//    assert_equal(s.IsAlreadyPresent(3), false);
//    assert_equal(s.IsAlreadyPresent(4), false);
//    s.AddItem(4);
//    assert_equal(s.IsAlreadyPresent(4), true);
//    assert_equal(s.GetValuePosition(4), 2);
//
//    s.AddItem(6);
//    assert_equal(s.GetValuePosition(4), 2);
//    assert_equal(s.GetValuePosition(6), 3);
//  }
//}



//#define assert_factors_equal(number, expected) { \
//  Factors f (number); \
//  if (!(f.factors==expected)) { \
//    throw std::runtime_error(#number " != " #expected); \
//  } \
//}
//
//void TestFactors() {
//  assert_factors_equal(2, (FactorsArr{2,0,0,0, 0,0,0,0}));
//  assert_factors_equal(4, (FactorsArr{2,0,0,0, 0,0,0,0}));
//  assert_factors_equal(5, (FactorsArr{5,0,0,0, 0,0,0,0}));
//  assert_factors_equal(6, (FactorsArr{2,3,0,0, 0,0,0,0}));
//  assert_factors_equal(2*3*5, (FactorsArr{2,3,5,0, 0,0,0,0}));
//  assert_factors_equal(2*2*3, (FactorsArr{2,3,0,0, 0,0,0,0}));
//  assert_factors_equal(2 * 3 * 5 * 7 * 11 * 13 * 17 * 19,
//      (FactorsArr{2,3,5,7, 11,13,17,19}));
////  assert_factors_equal(2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23,
////      (FactorsArr{2,3,5,7, 11,13,17,19}));
//}
//
//#define assert_coprime(a, b, expected) { \
//  Factors a_f (a); \
//  Factors b_f (b); \
//  if (Factors::AreCoprime(a_f, b_f) != expected) { \
//    throw std::runtime_error(#a " and " #b " failed to be coprime == " #expected); \
//  } \
//}
//
//void TestCoprime() {
//  assert_coprime(2, 2, false);
//  assert_coprime(2, 3, true);
//  assert_coprime(17, 2 * 3 * 4 * 17, false);
//  assert_coprime(2 * 3 * 5 * 17, 17, false);
//  assert_coprime(2 * 5 * 11, 3 * 7 * 13 * 17, true);
//  assert_coprime(2 * 3 * 5 * 7, 11 * 13 * 17, true);
//  assert_coprime(2 * 3 * 5 * 7 * 11 * 13 * 17 * 19, 23, true);
//}


void TestFactorsSieve() {
  {  // Smoke test
    FactorsReg fr;
    fr.SieveBuild(3);
    assert_equal(fr.factors.size(), 3);
    assert_equal(fr.factors[2].factors, Factors(2).factors);
  }

  {  // Test all
    int testsize = 10000;
    FactorsReg fr;
    fr.SieveBuild(testsize);
    for (int i = 2; i < testsize; i++)
      assert_equal(fr.factors[i].factors, Factors(i).factors);
  }
}


void RunTests() {
  TestFactorsSieve();
//  TestFactors();
//  TestCoprime();
//  TestSeries();
//  TestSeriesCreation();
}
#endif