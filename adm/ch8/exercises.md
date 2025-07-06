## Chapter 8 - Dynamic Programming

#### 8-1

- This would require an extra swap operation for this specific case
- This would apply on our dynamic programming table when:

```
M[i,j] = M[i-2, j-2] + 1
if A[i] == B[j-1] and A[i-1] == B[j] where i,j > 1
```

#### 8-2

- If you try each letter in order, `chocolate` and `chips` merge in the right order to form `cchocohilaptesis`. In the case of `chocochilatspe` you take the last letter from `chocolate`, the next letter could be `s` or `t` but it is `p` so it isn't a shuffle. In other words, `chocolate` and `chips` are not in the right order.
- First check that `len(x)` + `len(y)` is equal to the length of `z`.
- The subproblem would be `S[i,j] = True` if and only if $X_1\dots X_i + Y_1\dots Y_i$ can be shuffled into $Z_1\dots Z_{i+j}$
- The recurrence relation is: $S[i,j] = ((Z_{i+j} == X_i) and (S[i-1,j)) or ((Z_{i+j} == Y_j) and (S[i,j-1))$
- This runs in $O(nm)$

#### 8-3

Dynamic Programming:

- The subproblem is: `LCS(i,j) =` The longest common subsequence between $X_1\dots X_i$ and $Y_1\dots Y_j$
- Recurrence relation: $LCS(i,j) = max(LCS(i-1,j),LCS(i,j-1))$
- This runs in $\Theta(nm)$

Not Relying on Dinamic Programming:

- Loop through each letter on every string and compare each letter in place
- If the letters are the same, add the letter to an array `A` if not, clear the array, and continue to the next letter.
- Make sure to maintain another array of the consecutive substrings found, and return then longest one once the loop is finished.

#### 8-4

a. LCS: Let `M[i,j]` denote the number of characters in the longest common substring of `S[1]...S[i]` and `T[1]...T[j]`. When `S[i] != T[j]`, there is no way the last pair of characters could match, so `M[i,j] = max(M[i,j-1], M[i-1, j])`. But if `S[i] = T[j]` we have the option to select this character for our substring, so `M[i,j] = max(M[i-1, j-1]+1, M[i-1,j], M[i, j-1])`. This computes the length of the longest common subsequence in `O(nm)` time.  
b. SCS: This can be easily reduced to TSP. Create an overlap graph `G` where vertex `v` represents string `S[i]`. Assign edge `(v[i], v[j])` weight equal to the length of `S[i]` minus the overlap of `S[j]` with `S[i]`. Thus, `w(v[i]. v[j]) = 1` for `S[i] = abc` and `S[j] = bed`. The minimum weight path visiting all the vertices defines the shortest common substring.

#### 8-5

a. Not neccesarily, since it picks all the programs with the bigger disk space first, so a very little amount of programs with a large size will be picked up first.  
b. Yes, since it will keep picking programs until the capacity is reached. So, the biggest program won't be selected.

#### 8-6

- For example 12, the greedy algorithm will pick up 10, 1, 1 while the shortest possible can be 6, 6
- Subproblem: $DP(n,k) =$ minimum number of coins to make change for `n-1` using $d_1\dots d_{k-1}$ denominations
- Recurrence: $DP(n,k) = min(DP(n-1,k-1)-1)$
- Running time of $O(nk)$. `n` being the number of coins and `k` the different denominations of coins.

#### 8-7

- Six times - `C(20) = 6`, see the following table:

|                                         |
| --------------------------------------- |
| 10,10                                   |
| 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 |
| 6,6,6,1,1                               |
| 10,6,1,1,1,1                            |
| 10,1,1,1,1,1,1,1,1,1,1                  |
| 6,1,1,1,1,1,1,1,1,1,1,1,1,1,1           |

- The number of ways to make a sum $S$ from a set $D={a,b,\dots m,n}$ where $D[i] < D[j]$ for `i<j` is the sum of the ways to make $S$, $S-n,\dots S-xn$ from $D={a,b,c,\dots m}$

#### 8-8

Using the following table, the greedy algorithm would give the most feasible schedule. Greedy -> J1, J2, J3, J4

| Jobs | Time | Deadline |
| ---- | ---- | -------- |
| J1   | 1    | 3d       |
| J2   | 4    | 6d       |
| J3   | 2    | 7d       |
| J4   | 5    | 10d      |

#### 8-9

- Subproblem: subset of integers $S_1\dots S_i$ and remaining capacity $X$
- Recurrence: $DP(i,x) = max(DP(i+1,x),DP(i+1,x-S_i)+1)$
- Running Time: $O(nT)$

#### 8-10

TODO

#### 8-11

For each length of range `l` in `1...n` for each starting index `i` calculate the sum of the range of length `l`, starting at `i` as the sum of the range of length `l-1` starting at `i` plus the integer at `i+1 mod n`

#### 8-12

- Subproblem: $C(i,j) =$ The cheapest cost to cut up the string from $P_i \dots P_j$
- Recurrence: $C(i,j) = min(C(i,i+1)+C(i+1,j)+(P_j+P_i))$
- Running Time: $O(n^3)$

#### 8-13

- Subproblem: $E(m,n,k) =$ The best encoding for $D_1 \dots D_n$
- Recurrence: $E(m,n,k) = min(E(m-1,n-1,k)+E(m-1,n,k)+E(m,n-1,k))$
- Running Time: $O(mnk)$

#### 8-14

- Subproblem: $P(i,j)=$ Probability that the champion has $j$ points after $i$ games
- Recurrence: $P(i,j)=L_i \cdot P(i-1,j)+D_i \cdot P(i-1,j-1)+W_i \cdot P(i-1,j-1)$
- Running Time: $O(n^2)$

#### 8-15

- With only 1 egg, we have to find the `fth` floor and we start at the first and try each consecutive floor.
- Use a variation of binary search. In this case $E(k,n) \leq k\sqrt{n}$
- Subproblem: $E(k,n)=$ Minimun number of possible tosses to find the critical floor in a $n$ story building with $k$ eggs
- Recurrence: $E(k,n)=min(max(E(k,n-1),E(k-1,i-1))+1)$ on each floor, where $i$ represents the `ith` floor
- Running time: $O(kn^2)$

#### 8-16

- `B` means `BAD`, `G` means good

|     |     |     |
| --- | --- | --- |
| G   | B   | B   |
| B   | B   | G   |

- Implement a basic breadth first search algorithm that visits each block just once. Start at the top left corner and put each block in a queue. If we visit the lower right corner then we found the path.
- Can be done with a similar BFS as with the previous answer. Set a good block to zero and add one to a bad block. Once finished, we'll end up with a cost matrix that will help us find the shortest path.

#### 8-17

- Using this matrix:

|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| G   | G   | G   | G   | G   |
| G   | G   | B   | G   | G   |
| G   | B   | G   | B   | G   |
| G   | G   | G   | G   | G   |

|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| 0   | 1   | 2   | 3   | 4   |
| 1   | 2   | X   | 4   | 5   |
| 2   | X   | 6   | X   | 6   |
| 3   | 4   | 5   | 6   | 7   |

- We start with costs `0` at `[0,0]` therefore we got `X+Y-2-1` as the shortest path. We have to count how often the full set exists.

#### 8-18

We need to put as much books as possible in the shelves, as the greedy algorithm would do. Therefore the greedy algorithm will always find the optimal shelf placement. It seems as if the algorithm would run in $O(n)$ time

#### 8-19

- Subproblem: $C(i)=$ the shortest height shelving of book $B_1 \dots B_i$
- Recurrence: $C(i)=min(C(i-1)+max(h_k,h-j))$
- Running Time: $O(n^2)$

#### 8-20

- Subproblem: $C(j,k,i)=$ the cheapest way to dial the first $i$ digits where $j$ is the left finger and $k$ is the right finger
- Recurrence: $C(j,k,i)=min(C(j,k,i-1)+d(j,l,k,r))$
- Running Time: $O(nk^3)$

#### 8-21

- Sum every positive range and keep track of the maximum range. Pseudocode below:

```
function max_sum(nums) {
    let stored_nums = []
    for (let i = 0; i < nums.length; i++) {
        for (let j = i+1; j < nums.length; j++) {
            stored_nums.push(nums[i] + nums[i+1:j+1]);
        }
    }

    let max = stored_nums[0];
    for (let i = 1; i < stored_nums.length; i++) {
        if (stored_nums[i] > max) {
            max = stored_nums[i];
        }
    }

    if (max < 0) {
        max = 0;
    }

    return max;
}
```

- Subproblem: $MS(i,j)=$ The max sum in an array of $n-1$ numbers
- Recurrence: $MS(i,j)= max(MS(i-1,j),MS(i-1,j-1))$
- Runs in $O(n)$

#### 8-22

- Subproblem: $P(n,k)=$ Whether or not a parenthesization exists for the string $S_1 \dots S_n$ of length $n-1$
- Recurrence: $P(n,k)=(Solve(S_1 \dots S_n) and P(n-1,k-1)) or (Solve(S_1 \dots S_n) and P(n-1, k))$
- Runs in $O(nk)$

#### 8-23

TODO

#### 8-24

Solution using Dynamic Programming:

- Subproblem: $DP(n,k) =$ minimum number of coins to make change for `n-1` using $d_1\dots d_{k-1}$ denominations
- Recurrence: $DP(n,k) = min(DP(n-1,k-1)-1)$
- Running time of $O(nk)$. `n` being the number of coins and `k` the different denominations of coins.

#### 8-25

- This is a special case of the maximum contiguos sum problem. Pseudocode below:

```
function max_sum(nums) {
    let stored_nums = []
    for (let i = 0; i < nums.length; i++) {
        for (let j = i+1; j < nums.length; j++) {
            stored_nums.push(nums[i] + nums[i+1:j+1]);
        }
    }

    let max = stored_nums[0];
    for (let i = 1; i < stored_nums.length; i++) {
        if (stored_nums[i] > max) {
            max = stored_nums[i];
        }
    }

    if (max < 0) {
        max = 0;
    }

    return max;
}
```

- Instead of computing the result for $0,n$ instead we compute for $i,j$. We return 3 values indicating the index positions `i',j'` and max for the maximum sum of the `ith` through `jth` numbers. Worst case is $O(n)$.

#### 8-26

Go through each character of the magazine and use the given function to check if the character on the other side is the one that we want if the current character of the magazine is not it. Given a long enough magazine, most words can be made from the characters on the magazine.
