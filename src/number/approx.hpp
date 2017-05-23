#ifndef APPROX_H
#define APPROX_H

#include <array>
using std::array;

template <typename T>
array<T, 2> bisect(T (*fun)(T), T left,
         T right, T error = 1e-12, T min_window = 1e-10, int max_iter = 1000) {
    // find a root of a function by using bisection method
    T fl = fun(left),
      fr = fun(right);

    int iter = 0;
    while (abs(fun(left)) > error && iter < max_iter
            && abs(abs(left) - abs(right)) > min_window) {
        T new_guess = (left + right) / 2;
        if (fun(new_guess) > 0)
            right = new_guess;
        else
            left = new_guess;
        ++iter;
    }
    array<T, 2> sol;
    sol[0] = left;
    sol[1] = fun(left);
    return sol;
}


#endif
