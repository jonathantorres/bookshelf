## Chapter 2 - Algorithm Analysis

#### 2-1

If you call `mystery(3)` the value returned should be `5`. Which runs in $O(n^3)$

#### 2-2

If you call `pesky(3)` the value returned should be `17`. Which runs in $O(n^3)$

#### 2-3

If you call `prestiferous(3)` the value returned should be `28`. Which runs in $O(n^3)$

#### 2-4

If you call `conundrum(3)` the value returned should be `3`. Which runs in $O(n^2)$

#### 2-5

- $2n$ multiplications and $n$ additions
- I'm guessing the same amount $2n$
- I don't see a way that it could be improved.

#### 2-6

TODO

#### 2-7

a. True  
b. False

#### 2-8

a. $f(n) = \Theta(g(n))$  
b. $f(n) = \Omega(g(n))$  
c. $f(n) = \Omega(g(n))$  
d. $f(n) = \Omega(g(n))$  
e. $f(n) = \Omega(g(n))$  
f. $f(n) = \Theta(g(n))$  
g. $f(n) = \Omega(g(n))$  
h. $f(n) = O(g(n))$

#### 2-9

a. $g(n) = O(f(n))$  
b. $f(n) = O(g(n))$  
c. $f(n) = O(g(n))$  
d. $g(n) = O(f(n))$  
e. $g(n) = O(f(n))$  
f. $f(n) = O(g(n))$

#### 2-10

TODO

#### 2-11

TODO

#### 2-12

a. 2  
b. 2  
c. 2

#### 2-13

TODO

#### 2-14

TODO

#### 2-15

TODO

#### 2-16

TODO

#### 2-17

TODO

#### 2-18

- $\sqrt{n}$
- $log n$
- $ln n$
- $n$
- $lg lg n$
- $n lg n$
- $(lg n)^2$
- $2^{n-1}$
- $2^n$
- $n^2$
- $n^{1+\epsilon}$
- $n^2 + lg n$
- $n^3$
- $n-n^3+7n^5$
- $e^n$
- $n!$

#### 2-19

- $6$
- $\sqrt{n}$
- $\frac{n}{log n}$
- $lg n$
- $log log n$
- $log n$
- $n$
- $n^{1/3} + log n$
- $(log n)^2$
- $2^n$
- $n^2$
- $n^2 + log n$
- $n^3$
- $(1/3)^n$
- $(3/2)^n$
- $n-n^3+7n^5$
- $n!$

#### 2-20

a. $f(n) = log log n$ and $g(n) = (log n)^2$  
b. $f(n) = n^2$ and $g(n) = n^2 + log n$  
c. None  
d. $f(n) = n!$ and $g(n) = 2n$

#### 2-21

a. True  
b. False  
c. True  
d. False  
e. True  
f. True  
g. True

#### 2-22

a. $f(n) = \Theta(g(n))$  
b. $f(n) = O(g(n))$  
c. $f(n) = O(g(n))$

#### 2-23

a. Yes, it could be possible on insertion, or selection sort.  
b. Yes  
c. Yes, it could be possible on insertion, or selection sort.  
d. No, not on all inputs. Since it's already `O(n^2)` in the worst case.  
e. Yes

#### 2-24

a. Yes, as long as $c >= 4$  
b. Yes, as long as $c >= 2$  
c. Yes.  
d. Yes.

#### 2-25

a. $g(n) = log n$  
b. $g(n) = n$  
c. $g(n) = n log n$  
d. $g(n) = n log n$

#### 2-26

- $f4(n)$
- $f2(n)$
- $f1(n)$
- $f3(n)$

#### 2-27

- $f2(n)$
- $f1(n)$
- $f3(n)$
- $f4(n)$

#### 2-28

a. $g(n) = n^{n+3}$  
b. $g(n) = n^{19+n}$  
c. $g(n) = n^{20+n}$

#### 2-29

a. True  
b. True  
c. True

#### 2-30

a. $g(n) = 2^n+n$  
b. $g(n) = n^n/2$  
c. $g(n) = (n log n )^2$  
d. $g(n) = n^{103}$

#### 2-31

a. $A = \Omega(B)$  
b. $A = \Theta(B)$  
c. $A = O(B)$  
d. $A = O(B)$  
e. $A = O(B)$  
f. $A = \Omega(B)$

#### 2-32

TODO

#### 2-33

The sum of any row is just $3^n-1$, this is the sum for the series.

#### 2-34

TODO

#### 2-35

```math
\sum_{i=1}^n \sum_{j=i}^{2*1}
```

#### 2-36

```math
\sum_{i=1}^{n/2} \sum_{j=i}^{n-1} \sum_{k=1}^j
```

#### 2-37

$O(n^b)$

#### 2-38

$O(n^2)$

#### 2-39

TODO

#### 2-40

TODO

#### 2-41

TODO

#### 2-42

TODO

#### 2-43

Iterate over the elements in `S` from `i=0` until `S[i]` is empty. If `i < k`, `S'[i] = S[i]`. After that, for each `i`, replace a random element in `S'` with `S[i]`

#### 2-44

9 data entries are lost in the worst case.

#### 2-45

`n-1` times in the worst case or $O(n)$

#### 2-46

- With an infinite supply of marbles, maybe starting from the top, and working my way down `100,99,98,97,...`.
- With only 2 marbles, I'll start on floor 50, and then up to 75 if it doesn't break on the 50th floor. I'll go down on the 35th floor if it does break in the 50th floor.

#### 2-47

1. Find an empty bag (labeled "E")
2. Place 1 coin from bag 1 into E
3. Place 2 coins from bag 2 into E  
   ...
4. Place 9 coins from bag 9 into E
5. Place 10 coins from bag 10 into E
6. Weigh bag E on your digital scale

If all coins were 10 grams, the bag would weigh 550 grams. Thus, 550−weight will tell you how many coins are too light. Since this number of coins correlates to the bag from which the coins came, you now know which bag contains the light coins.

#### 2-48

Weight one half of the balls first and then the other half. Repeat the same process for the lighter half. This would result in 4 weighins in the worst case.

#### 2-49

- Merge all companies at the same time.
- Another option would be to merge `n+1` company with `n` company until all companies have been merged.

#### 2-50

TODO

#### 2-51

If the senior pirate divides the money equally `$50 each`, then everyone survives. If every following senior pirate is greedy, then the most junior pirate gets all the money, since every other pirate was killed.

#### 2-52

The senior pirate gets it all. If `3+` pirates, the least senior pirate gets it.
