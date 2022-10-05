#include <limits>
#include <utility>
template<typename F>
double double_ternsearch_max(F f, double lo, double hi, int n_it)
/* Given a unimodal (increasing, then decreasing) function f,
* returns a value x close to, but never greater than, the one maximizing f.
* The interval shrinks with a factor 2/3 each iteration.
*/
{
while (n_it--) {
double a = (2 * lo + hi) / 3, b = (lo + 2 * hi) / 3;
if (f(a) < f(b)) lo = a;
else hi = b;
}
return lo;
}
template<typename T, typename F>
int int_ternsearch_max_first(F f, int lo, int hi, T *opt = nullptr)
/* Given a unimodal function f: [lo, hi] -> T that first attains its
* maximum at I (f(lo) < f(a + 1) < ... < f(I) >= f(I + 1) >= ... >= f(hi)),
* find I (lo <= I <= hi).
* If opt is not nullptr, put the f(I) into *opt.
* Call as int_ternsearch_max_first<T>(...) (F is deduced automatically).
*/
{
// Search in [lo, hi]
while (hi - lo >= 3) {
// Choosing a = mid, b = mid + 1 gives fast convergence.
int mid = lo + (hi - lo - 1) / 2;
if (f(mid) < f(mid + 1))
lo = mid + 1;
else
hi = mid;
}
// Linear search through last remaining elements
int best_i = -1;
T best = std::numeric_limits<T>::lowest();
for (int i = lo; i <= hi; ++i) {
T x = f(i);
if (x > best) {
best_i = i;
best = x;
}
}
if (opt != nullptr) *opt = best;
return best_i;
}
template<typename T, typename F>
int int_ternsearch_max_last(F f, int lo, int hi, T *opt = nullptr)
/* Given a unimodal function f: [lo, hi] -> T that last attains its
* maximum at I (f(lo) <= f(a + 1) <= ... <= f(I) > f(I + 1) > ... > f(hi)),
* find I (lo <= I <= hi).
* If opt is not nullptr, put the f(I) into *opt.
* Call as int_ternsearch_max_last<T>(...) (F is deduced automatically).
*/
{
// g(i) = f(j) where j = hi - (i - lo)
int best_j = int_ternsearch_max_first(
[&] (int i) { return f(hi - (i - lo)); },
lo, hi, opt);
return hi - (best_j - lo);
}
