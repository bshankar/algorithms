#include <gtest/gtest.h>

#include "../lib/number/prime.hpp"
#include "../lib/number/modular.hpp"


TEST (primeTest, primesBelowNumber) {
  EXPECT_EQ(25, segmented_sieve(100).size());
  EXPECT_EQ(168, segmented_sieve(1000).size());
  EXPECT_EQ(1229, segmented_sieve(10000).size());
}


TEST (primeTest, smallPrimes) {
  vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19};
  EXPECT_EQ(p, segmented_sieve(20));
}


TEST (primeTest, MillerRabin) {
  EXPECT_EQ(true, miller_rabin(101));
  EXPECT_EQ(false, miller_rabin(100));
  EXPECT_EQ(true, miller_rabin(661));
  EXPECT_EQ(true, miller_rabin(1009));
  EXPECT_EQ(false, miller_rabin(1000001));
}


TEST (primeTest, littleFactors) {
  vector<int> f = {1, 12, 2, 6, 3, 4};
  EXPECT_EQ(f, factors(12));
  f = {1, 25, 5};
  EXPECT_EQ(f, factors(25));
}


TEST (primeTest, littlePrimeFactors) {
  vector<int> p = segmented_sieve(20);
  map<int,int> f = {{2,1}, {3,1}, {5,1}, {7,1}};
  EXPECT_EQ(f, prime_factors(210, p));
}


TEST (modTest, gcd) {
  EXPECT_EQ(1, gcd(2, 3));
  EXPECT_EQ(6, gcd(12, 30));
  EXPECT_EQ(5, gcd(30, 35));
}


TEST (modTest, modularInverses) {
  EXPECT_EQ(5, inverse(5, 6));
  EXPECT_EQ(23, inverse(17, 39));
}


TEST (modTest, modularExponentiation) {
  EXPECT_EQ(1, modpow(2, 100, 101));
  EXPECT_EQ(11, modpow(27, 45, 17));
  EXPECT_EQ(15, modpow(108, 661, 41));
}
