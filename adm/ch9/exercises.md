## Chapter 9 - Intractable Problems and Approximation Algorithms

#### 9-1

```
(x + y + !z + w + u + !v)·(!x + !y + z + !w + u + v)·(x + !y + !z + w + u + !v)·(x + !y)
true + false + false     · false + false + true     · false + false + false    · false
false + false            · false + true             · false + false            · false
false                    · false                    · false                    · false
                                 false + false
                                     false
```

#### 9-2

Convert the expression to 3-SAT first, If $C = \\{\\{v1,\overline{v3},\overline{v4}\\}, \\{\overline{v1},v2,\overline{v4}\\}\\}$

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch9/img/9-2.jpg)

#### 9-3

- First determine the length of the shortest TSP tour
- Loop over all the edges
- If the graph with the edge removed has a TSP tour of lenght `k`, remove this edge
- After the loop, we are left with a graph containing the vertices of the original graph connected by a subset of the edges of the original graph
- This reduced graph should contain a TSP tour of length `k`

#### 9-4

TODO

#### 9-5

TODO

#### 9-6

TODO

#### 9-7

- Create a set of edges for each vertex `u`, where the set contains all the edges that have one vertex in `u`
- Let the large set `x` be the set of all edges in the graph. Pseudocode below:

```
VertexCover(G) {
  X = all the vertices of G
  F = a family of subsets from X
  k = 2
  SetCover(X, F, k)
}
```

#### 9-8

- This is the same problem as set cover
- Use a graph where each vertex represent the card that you want and the edge the packet from where it belongs. Use the vertex cover procedure to solve the card collector problem:

```
Collector(packets, k) {
    foreach packet P {
        VertexCover(P)
    }
}
```

#### 9-9

- This problem is hard since Hamiltonian path is also hard.
- Use the hamiltonian path procedure to make sure that every vertex is visited at least once, return false once a vertex greater than `k` is found

```
HamiltonianPath(G) {
  S = A spanning tree of G
  k = 2
  LowDegree(S, k)
}
```

#### 9-10

Mantain a count of vertices and a count of edges, use a procedure to find a subgraph, if a subgraph is found do a BFS on it and count every edge and vertex on it:

```
Dense(G,k,y) {
    s = find_sub(G)
    if s {
        count every edge and vertex of s
    }
}
```

#### 9-11

Call a clique subroutine on `G` to get the size of it, also call a subroutine for independent set of size `k`, if both values of the subroutines are equal to `k`, then `G` satisfies the clique, no-clique.

```
CliqueNoClique(G,k) {
  S = Clique(G)
  T = IndependentSet(G,k)
  return true if both S and T equal k
}
```

#### 9-12

- The hamiltonian cycle is already NP-hard. We need to find the Eulerian subgraph first. If there's only one such subgraph, then every edge of this graph is the solution.
- Count the number of edges of the returned subgraph (if any).

```
EurelianEdges(G) {
  S = EurelianSubgraph(G)
  if S {
    return the count of edges from S
  }
}
```

#### 9-13

- Label the vertices 1 to `n`. Let `S` be the set `{1,2,3...n}`
- The subset for each edge `{u,v}` which contains the number labels of `u` and `v`

Reduction from vertex cover:

```
VertexCover(V,E,j) {
  S = {V[0]...V[n]}
  C = {E[0]...E[n]}
  k = j

  HittingSet(S,C,k)
}
```

#### 9-14

- Create graph `G` such that an edge between vertices `(vi, vj)` contains the required weight of both vertices
- Go through each edge until the weight equals `W` but as long as `V` is greater than the sum of each vertex traversed.

Pseudocode and reduction from Integer Partition:

```
IntegerPartition(n) {
  S = The graph G described above (built from n)
  W = weight calculated after going through each edge of S
  V = value calculated after going through each edge of S
  Knapsack(S, W, V)
}
```

#### 9-15

- Construct a complete weighted graph `G=(V,E)`, start from vertex `V` and keep track of each vertex visited, maybe in a cache (array) once an already visited vertex is found, then the path cannot be found.

Reduction from Hamiltonian Cycle

```
HamiltonianCycle(H) {
  G = weighted graph built as described above
  S = start vertex from cycle of G
  T = end vertex from cycle of G
  HamiltonianPath(G, S, T)
}
```

#### 9-16

- I think this is the same problem as the hamiltonian path, but visiting every vertex up until `k` and stopping once the same vertex is visited. If this happens, then the longest path was not found.

Reduction from Hamiltonian Cycle

```
HamiltonianCycle(H) {
  G = graph built as described above
  K = 2
  LongestPath(G, K)
}
```

#### 9-17

TODO

#### 9-18

TODO

#### 9-19

TODO

#### 9-20

TODO

#### 9-21

- By going through each vertex and edge, we can construct the DFS tree and then do a topological sort on it.
- If there's a consecutive path on the result of the sort, then there's a Hamiltonian path on the DAG.
- Before doing the sorting, make sure there are no repeating vertices, since we are dealing with a DAG.

#### 9-22

- Unlike 3-SAT and Satisfiability, 2-SAT can indeed be solved in polynomial time.
- By grouping together all of the clauses that use the same variable, apply the inference rule to each pair of clauses.
- By doing this, it is possible to find all inferences that are possible from a given $2CNF$ instance. This can be tested in $O(n^3)$

#### 9-23

- This can be done in linear time, therefore is not in NP
- This can be solved in polynomial time, therefore is not in NP
- We have to find a vertex cover to answer the question, the vertex cover problem is NP-complete. Therefore, to find a vertex cover of size $k$ is also NP-complete.

#### 9-24

- Because it's just doing a modulo check on the value, instead of finding the multiple numbers that multiply to it's result.
- This is just doing a check, instead of calculating the requested value.

#### 9-25

- This is an NP-Hard problem.
- But it is possible to assign truth values in a way to make three out of four clauses true, every truth assignment will attempt to do this.
- The solution for this leads to the solution of the boolean satisfiability problem.

#### 9-26

- Once we construct the DFS tree, count the inner nodes that are left.
- If we have a graph of `n` nodes, and we delete the leaves from the DFS tree, any backedges of the DFS tree will amount for the cover of the graph.

#### 9-27

TODO

#### 9-28

- This would depend on the target capacity.
- If at least $n/2$ items are not greater than half of the bin capacity, that heuristic will yield twice as many bins.

#### 9-29

Use 5 items with weights:

- 0.3 kg
- 0.7 kg
- 0.9 kg
- 0.1 kg
- 0.5 kg

#### 9-30

TODO
