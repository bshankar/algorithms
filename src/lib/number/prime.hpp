#ifndef PRIME_HPP
#define PRIME_HPP

/* 
This file contains functions to do calculations 
related to primes and factors
*/

#include <vector>
#include <map>
#include <random>

using std::vector;
using std::map;


template <class T>
bool miller_rabin(T n, T k = 5) {
  // The miller rabin test for primality
  // of a number

  if (n == 2 || n == 3)
    return true;

  if (n % 2 == 0 || n == 1)
    return false;

  std::default_random_engine generator;
  std::uniform_int_distribution<T> distribution(2, n-3);

  // write n-1 as 2^s*d
  T s = 0, d = n-1;
  while (d % 2 == 0) {
    d /= 2;
    ++s;
  }

  // witness loop
  for (int i = 0; i < k; ++i) {
    T a = distribution(generator);
    T x = pow(a, d, n);
    if (x == 1 || x == n-1)
      continue;
    bool b = false;
    for (int j = 0; j < s-1; ++j) {
      x = x*x % n;
      if (x == 1)
        return false;
      if (x == n-1) {
        b = true;
        break;
      }
    }
    if (!b)
      return false;
  }
  return true;
}


template <class T>
vector<T> segmented_sieve(T limit, T segment_size=32678) {
  // an efficient sieve of erathostenes implementation to
  // calculate all primes below n

  T sqrt_ = sqrt(limit);
  T s = 2;
  T n = 3;

  // vector used for sieving
  vector<char> sieve(segment_size);

  // generate small primes <= sqrt
  vector<char> is_prime(sqrt_ + 1, 1);
  for (T i = 2; i * i <= sqrt_; i++)
    if (is_prime[i])
      for (T j = i * i; j <= sqrt_; j += i)
        is_prime[j] = 0;

  vector<T> primes, primes_;
  vector<T> next;

  if (limit >= 2)
    primes_.push_back(2);

  for (T low = 0; low <= limit; low += segment_size) {
    fill(sieve.begin(), sieve.end(), 1);

    // current segment = interval [low, high]
    T high = min(low + segment_size - 1, limit);

    // store small primes needed to cross off multiples
    for (; s * s <= high; s++)
      if (is_prime[s]) {
        primes.push_back(s);
        next.push_back(s * s - low);
      }

    // sieve the current segment
    for (T i = 1; i < primes.size(); i++) {
      T j = next[i];
      for (T k = primes[i] * 2; j < segment_size; j += k)
        sieve[j] = 0;
      next[i] = j - segment_size;
    }

    for (; n <= high; n += 2)
      if (sieve[n - low])
        // n is a prime not stored in primes
        primes_.push_back(n);
  }
  return primes_;
}


template <typename T>
double approx_primes_below(T n) {
  // get approximate number of primes below n
  return double(n)/log(n);
}


template <typename T>
vector<T> factors(T n) {
  // return all distinct factors of n
  vector<T> facs = {1};
  if (n > 1) facs.push_back(n);

  for (T i = 2; i*i < n; ++i) 
    if (n % i == 0) {
      facs.push_back(i);
      facs.push_back(n/i);
      n /= i;
    }
  return facs;
}


template <typename T>
map<T, int> prime_factors(T n, vector<T>& primes) {
  // returns all the prime factors of T as a map
  // T, vector<T> primes -> (T prime -> pow)
  map<T, int> pf;
  for (T prime: primes) {
    int pow = 0;
    while (n % prime == 0) {
      n /= prime;
      ++pow;
    }
    pf[prime] = pow;
  }
  return pf;
}


template <typename T>
T euler_totient(T n, vector<T>& primes) {
  // given all primes less than n
  // find euler's totient of n
  T t = 1;
  for (T prime: primes) {
    T pow = 0;
    while (n % prime == 0) {
      n /= prime;
      ++pow;
    }
    t *= pow(prime, pow - 1)*(prime - 1);
  }
  return t;
}

#endif
