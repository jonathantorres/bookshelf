## Chapter 2 - Notes

- Algorithms can be understood and studied in a language and machine independent manner.
- **Worst case complexity** - is the function defined by the **maximum** number of steps taken in any instance of size `n`.
- **Best case complexity** - is the function defined by the **minimum** number of steps taken in any instance of size `n`.
- **Average case complexity** - is the function defined by the **average** number of steps over all instances of size `n`.
- The **Big Oh** notation and **worst-case** analysis are tools that greatly simplify our ability to compare the efficiency of algorithms.
- Although esoteric functions arise in advanced algorithm analysis, a small variety of time complexities suffice and account for most algorithms that are widely used in practice.
- Logarithms arise whenever things are repeatedly halved or doubled.

Formal definitions of the **Big Oh**:

$f(n) = O(g(n))$ - Big Oh - Upper bound on $f(n)$

$f(n) = \Omega(g(n))$ - Big Omega - Lower bound on $f(n)$

$f(n) = \Theta(g(n))$ - Big Theta - $c1$ is a lower bound on $f(n)$ and $c2$ is an upper bound on $f(n)$

Order of dominance of functions in the **Big Oh**:

```math
n! > 2^n > n^3 > n^2 > n log n > n > log n > 1
```
