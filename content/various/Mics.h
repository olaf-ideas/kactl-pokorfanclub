/**
 * Author: none
 * License: CC0
 * Description: random things
 * Status: tested
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
__builtin_popcountll // ile jedynek w zapisie bitowym
__builtin_clzll // ile zer przed pierwsza jedynka __clz(2) = 1
__builtin_parityll() // liczba jedynek mod 2
__builtin_mul_overflow(a,b,&h) // mnozenie, ale jak sie wywali to daje true