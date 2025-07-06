## Chapter 6 - Weighted Graph Algorithms

#### 6-1

Graph A - Kruskal

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/a_kruskal.jpg)

Graph B - Kruskal

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/b_kruskal.jpg)

Graph A - Prim

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/a_prim.jpg)

Graph B - Prim

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/b_prim.jpg)

Graph A - Shortest Path

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/a_shortest.jpg)

Graph B - Shortest Path

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/b_shortest.jpg)

#### 6-2

No, in a MST we only care about the weight of the next tree edge. In shortest path, we want to include the closest outside vertex.

#### 6-3

No, the following graph is a counterexample. MST has a weight of 6 with edges `{A,B}, {B,C}, {C,D}`. In the full graph the minimum distance between A and D is 4.

![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/6-3.jpg)

#### 6-4

Yes, it's possible. Since Kruskal's algorithm will start adding the edges into the tree (avoiding cycles) in sorted order it could yield a different MST, especially in the cases in which there are more than 1 edge with the same weight in the graph

#### 6-5

Yes, it will still work. Since the algorithms will find the MST regardless if the edge has a positive or negative value.

#### 6-6

Do a BFS on `T` starting from `u` and stop once you reach `v`. Traverse the tree of discovery upwards from `v` and once an edge more expensive than `w` is found remove it and add `e` in its place.

#### 6-7

a. Yes, the edges of `T` still form the MST. They are not affected by the change since all the weights in the graph are the same.  
b. No, it does not, when increasing the weights of the edges, the shortest path between `s` and `t` will be different.

#### 6-8

TODO

#### 6-9

a. It's not an entire MST problem if we allow negative weight edges, because if we don't allow negative weights, then `T` would be the same as the MST.  
b. Run a preprocessing pass before running Kruskal's algorithm, add all edges together and then run Kruskal's algorithm normally until finished.

#### 6-10

a. Do a DFS starting from any vertex. Traverse the tree of discovery upward and once a backedge is found, add the edges from the current vertex up to the ancestor. Repeat this process and keep the set of edges in a array or hashtable. The entry with the smallest set is the feedback edge set.  
b. Find the MST of `G`. Use the DFS tree described above and add the edges of every cycle into a set. Select the set that adds up to the minimum weight of its edges.

#### 6-11

- Start with an arbitrary vertex. Put the edges of this vertex in a min heap, where each node of the heap contains a value equal to the weight of the edge, and a list of destination vertices.
- While min heap is not empty, take out the min edge, remove the destination vertex from the list, and add the edge to the tree.
- For each of the `n` vertices, we will extract the min edge from the heap. The heap has a size of `k`, and each extraction operation takes $log(k)$ time. So total time will be $O(n log(k))$

#### 6-12

Use a modified version (from the book) of an union find.

a. Looks like an union  
b. Looks like a find  
c. Looks like a find

#### 6-13

- This problem can be reduced to finding connected components in a graph.
- We can use union-set provided by the book. Modify the find function replacing it by path compression, splitting, or halving. Using both this and union by size make find and union run in (amortized) constant time.
- Initializing the union-set is $O(n)$, and running `m` union and finds are $O(2m)$. Thus, the total running time is $O(n+m)$

#### 6-14

Dijkstra's algorithm is the most suitable for this type of problem, it will find the shortest path in $O(n^2)$. Run Dijkstra's algorithm on every vertex other than `v`. This would run in $O(n^3)$

#### 6-15

No, any graph with a shortest-path spanning tree will be altered or possibly it will no longer be the shortest path if a constant value is added to every edge.

#### 6-16

a.  
![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/16_a.jpg)

b.  
![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/16_b.jpg)

#### 6-17

a. No, the graph on page 196. of the book gives a very good counterexample  
![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/17_a.jpg)

b. No, A counterexample to this is a square graph. The MST is `A->B->C->D` and the edge of weight 8 is never included. The path from A to D through the MST is 10, but the path from A->D is weight 8.  
![graph](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch6/img/17_b.jpg)

#### 6-18

a. If I understand this correctly, it seems that the graph `G` is unweighted, the edges have a cost of 0 and vertices a cost of 1. Running a BFS starting from vertex `a` will return the shortest path to `b`.  
b. This can be found using Dijkstra's algorithm by using the weight of the vertex as the way to decide the cost of a path (instead of the edges)  
c. Same as above but computing the cost by using both the edge cost and the cost of both vertices of the edge

#### 6-19

This can be solved by applying an All Pairs Shortest Path (an adjacency matrix is needed for this algorithm), Floyd-Warshall algorithm for directed graphs. This will run in $O(n^3)$ time.

#### 6-20

Yes, I think is possible, we would have to modify the algorithm to do the inverse, instead of minimum, look for a maximum value. Similar to working with a heap or a comparison function for a sorting algorithm.

#### 6-21

Perform a topological sort of the graph. Go through these vertices in order, if it's accesible update it's children with new distance if the new distance is shorter than the previous one. Topological sorting makes sure that we don't backtrack. This would run in $O(n+m)$ which is linear time.

#### 6-22

Use a modified version of Dijkstra's algorithm to find the path but making sure that the number of edges is not over `k`. Maybe stop the algorithm if it's impossible to find the path under `k` edges.

#### 6-23

TODO

#### 6-24

Iterate over every vertex in the graph, if that vertex is in the set then skip it, otherwise add one of it's edges to another vertex that's also not on the set.

#### 6-25

This can be solved by maximum matching. General matching would require Edmonds Blossom algorithm. Include an arbitrary edge for every uncovered vertex.
