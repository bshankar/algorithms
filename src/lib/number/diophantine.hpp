#ifndef DIOPHANTINE_HPP
#define DIOPHANTINE_HPP

#include "modular.hpp"


template <typename T>
array<T, 2> simple_diophantine(T a, T b, T c) {
  // solves the equation ax + by = c
  array<T, 2> sol;
  T gcd_ = gcd(a, b);
  if (c % gcd_ != 0) {
    // this is equation has no solution
    sol[0] = 0;
    sol[1] = 0;
    return sol;
  }
  // solve the equation ax + by = gcd(a, b)
  auto eu = extended_euclid(a, b);
  sol[0] = eu[0]*c/gcd_;
  sol[1] = eu[1]*c/gcd_;
  return sol;
}

#endif
