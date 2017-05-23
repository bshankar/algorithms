#ifndef MODULAR_HPP
#define MODULAR_HPP

#include <vector>
#include <array>

using std::vector;
using std::array;


template<typename T>
T gcd(T a, T b) {
  // calculate gcd using euclid's algorithm
  if (a == 1) return b;
  return gcd(b, a % b);
}


template <typename T>
array<T, 5> extended_euclid(T a, T b) {
  array<T, 5> v;
  T s = 0, t = 1, r = b;
  T s_ = 1, t_ = 0, r_ = a;

  while (r != 0) {
    T q = r_/r;
    T r_tmp = r_, s_tmp = s_, t_tmp = t_;
    r_ = r; s_ = s; t_ = t;
    r = r_tmp - q*r;
    s = s_tmp - q*s;
    t = t_tmp - q*t;
  }

  v[0] = s_; v[1] = t_;  // bezout coefficients
  v[2] = r_;  // gcd
  v[3] = t; v[4] = s;  // t is modular inverse
  return v;
}


template <class T>
T inverse(T a, T n) {
    // calculate the multiplicative inverse
    // in modular structures
    T t = 1, r = a, q;
    T t_ = 0, r_ = n;
    T t_tmp, r_tmp;

    while (r) {
        q = r_/r;
        r_tmp = r_; t_tmp = t_;
        t_ = t; r_ = r;
        t = t_tmp - q*t;
        r = r_tmp - q*r;
    }
    if (r_ > 1)
        // not invertible
        return 0;
    if (t_ < 0)
        t_ += n;
    return t_;
}


template <typename T>
T modpow(T x, T n, T m) {
  // calculate x^n mod m
  if (n == 0) return 1 % m;
  T u = modpow(x, n/2, m);
  u = (u*u) % m;
  if (n % 2 == 1)
    u = (u*x) % m;

  return u;
}

#endif
