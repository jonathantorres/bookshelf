## Chapter 7 - Combinatorial Search and Heuristic Methods

#### 7-1

Derangement program implemented here: [7-1.js](7-1.js)

#### 7-2

Multiset program implemented here: [7-2.js](7-2.js)

#### 7-3

Given 2 graphs `G1` and `G2`:

- Compare the number of vertices in `G1` and `G2` for equality.
- Compare the number of edges in `G1` and `G2` for equality.
- Sort the vertices of `G1` and `G2` by degree and compare the degrees of each pair of vertices from `G1` and `G2` for equality.
- Use backtracking to generate a mapping of the vertices.

#### 7-4

Anagram program implemented here: [7-4.js](7-4.js)

#### 7-5

TODO

#### 7-6

TODO

#### 7-7

- Only options to solve this is brute force and search heuristics
- Perform a BFS starting from vertex `v`
- All of the vertices that are distance 1 from `v` are placed to it's immediate right, followed by vertices at distance 2 and so forth until all the vertices in `G` are accounted for.

#### 7-8

- Employing heuristics that give good but not optimal solutions is usually the better approach in practice.
- Provide NP-Completeness first.
- To solve the satisfiability exactly there's no much choice rather than backtracking algorithms, such as the David-Putman procedure.
- $2^m$ assignments to test in the worst case.

#### 7-9

- Best solution is an exhaustive search via backtracking.
- Search through all `k` subsets of the vertices, pruning a subset as soon as it contains a vertex that is not adjacent to all the rest.
- The upper bound on the maximum clique in `G` is the highest vertex degree plus 1.
- A better upper bound comes from sorting the vertices in order of decreasing degree.
- Let `j` be the largest index such that degree of the `j`th vertex is at least `j-1`.
- The largest clique in the graph contains no more than `j` vertices, since no vertex of degree `< (j-1)` can appear in a clique of size `j`.

#### 7-10

- Resort to backtracking
- Incremental methods are the heuristic of choice for vertex coloring.
- Vertices are colored sequentially, with the colors chosen in response to colors already assigned in the vertex neighborhood.
- Insert the vertices in nonincreasing order of degree, since high-degree vertices have more color constraints and so are most likely to require an additional color if inserted late.
- Incremental methods can be further improved by using color interchange.

#### 7-11

TODO

#### 7-12

- Use BFS to identify the shortest cycle in `G`.
- Delete all the vertices in the cycle from `G` and the shortest remaining cycle identified.
- Employ this find-and-delete procedure until the graph is acyclic.

#### 7-13

- Greedy is the most natural and effective heuristic for set cover.
- Select the largest subset for the cover, and then delete all it's elements from the universal set.
- Add the subset containing the largest number of remaining uncovered elements repeatedly until all are covered.
- This heuristic always gives a set cover using at most `ln n` times as many sets as optimal.

#### 7-14

Permutations program implemented here: [7-14.js](7-14.js)

#### 7-15

Subsets program implemented here: [7-15.js](7-15.js)

#### 7-16

This is basically the same program as in 7-4, which can be found here: [7-4.js](7-4.js)

#### 7-17

```
words(nums) {
    w = []
    letters = map of nums and letters
    for n in nums {
        word = ""
        if n >= 2 {
            for k in letters[n] {
                word += k
            }
            w.push(word)
        }
    }
    return w
}
```

#### 7-18

- Enumerate all the subsets of `n` elements in the gray code order.
- Enumerate all the subsets of a set such that you only need to either insert one element or remove one from the previous subset to get the new subset.
- Details on chapter 14.5 of the book.

#### 7-19

I'd say just one call, and we add 3 to the call from (rng04), so that the maximum possible number doesn't go over 7 or is not greater than 7.
