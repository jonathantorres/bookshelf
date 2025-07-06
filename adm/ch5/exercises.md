## Chapter 5 - Graph Traversal

#### 5-1

a. Graph 1 BFS: ABDICEGJFH, DFS: ABCEDGHFJI  
b. Graph 2 BFS: ABECFIDGJMHKNLOP, DFS: ABCDHGFEIJKLPONM

#### 5-2

A->B->D->E->C->F->H->G->I->J

#### 5-3

TODO

#### 5-4

TODO

#### 5-5

Graphs with a max degree 2 can be bipartite (even number of edges) or tripartite (odd number of edges). Consider a triangle (3 edges, 3 vertices). It's not bipartite even though every node has an even number of edges and the graph has an even number of edges.

#### 5-6

a. A graph with a starting vertex `v` with `n-1` edges coming out of it.  
b. A graph with a starting vertex `v` with `n-1` edges and nodes after it in a single line. `v->y->z`.  
c. A graph starting at vertex `v`, going half way through the search for `n/2` nodes that are discovered, there can be `n/2` nodes that are undiscovered.

#### 5-7

Yes, it's possible. Using the given pre-order and in-order traversals:

```
function reconstruct_tree(t) {
    new_tree = init_tree()
    pre_order(t, new_tree)
    return new_tree
}

function pre_order(t, new_tree) {
    add_item_to_tree(new_tree, t->value)
    pre_order(t->left, new_tree)
    pre_order(t->right, new_tree)
}
```

Yes, it's also possible with pre-order and post-order traversals by using the same pre-order algorithm. The tree will be the same and have the same structure.

#### 5-8

a. Loop through each row/column in the matrix and if the current value of the matrix is true, create the proper linked list for the current index, if a list is already there, just add the new entry to it. $O(n x m)$  
b. Loop through each key/list, and if a list is there, loop through it and add it to the matrix, keeping a key index on each iteration of the list, to use those indices when creating the incidence matrix. This should run on $O(n+m)$  
c. Same as the previous answers but creating a list for the key, if the current row/column is true, for the existence of the edge. This should run on $O(n+m)$

#### 5-9

If the expression is evaluated from left to right and doing the expression that are on parenthesis first. This can be done with a post-order traversal. When processing each node, treat the leafs as a literal, and anything else as an arithmetic expression. The multiplications will be processed first, followed by the divisions and doing the additions at the end.

#### 5-10

If the expression is evaluated from left to right and doing the expressions that are on parenthesis first. This can be done with depth-first search. When processing each node, treat the leafs as a literal, and anything else as an arithmetic expression. DFS will process the multiplications first, followed by the divisions and doing the additions at the end.

#### 5-11

TODO

#### 5-12

We're basically adding more edges for vertices that have a path of two edges. These can be added by doing a BFS from each vertex, and add the edges for each in $O(n(V+E))$. The adjacency matrix would probably have the worst performance.

#### 5-13

a. Do a BFS from any vertex in `G`. Traverse the tree of discovery and remove any leafs from it, any vertices that are left that is not the root form the vertex cover.  
b. Perform the same BFS and specified above, choose between removing the `n` children of degree one or the parent of degree `n+1`.  
c. Perform the same BFS and use a two-coloring technique (red-black) and perform a post order traversal.

#### 5-14

Yes, as long as the graph `G` is connected and we do not include the root as part of the final result. Given the graph displayed below, in which the vertex cover are the vertices 4 and 5 and it's DFS tree. If we remove all the leaf nodes, the nodes that are left are the node labeled 4 and 5 (not including the root)

![graph_and_tree](https://github.com/jonathantorres/bookshelf/blob/master/adm/ch5/img/5-14.jpg)

#### 5-15

- To build a vertex cover, we need to keep at least one vertex for each edge. The independent set requires at most one vertex for each edge.
- Together it means we need to keep only exactly one vertex for each edge, this reduces to a two-colour graph problem.
- This problem is efficiently handled by breadth-first search.

#### 5-16

This translates to the question of labeling the tree with two colors, because this way each edge's vertices are colored differently. The larger group of colors is the sought for maximum-size independent set.
a. Do a BFS on `G` and pick all the vertices that are leaves on this discovery tree.  
b. Do a BFS on `G` and remove all the leaf vertices from the tree of discovery, pick all the remaining vertices except the root node.  
c. Same as b.

#### 5-17

This can be done with DFS:
a. Compare every possible set of 3 vertices and test if there is an edge between them  
b. Use DFS and maintain an array of parent and check any back edge `u-v` whether grandparent of `u` is equal to `v`

#### 5-18

Using the sets of customers and movies, calculate which movies people want to see the most. And schedule the movies based on that.

- Most requested movie - Sat. evening
- 2nd most requested movie - Sun. evening
- Play the rest at the same time during those days.
- Bipartite graph

#### 5-19

Traverse the tree from `u` to `v` and count the number of edges. This would run on $O(h)$ in the worst case. `h` being the height of the tree.

#### 5-20

Traverse the graph, maybe with BFS or DFS and construct the new graph based on the data for each vertex.

#### 5-21

Use BFS from vertex `v`. For every node keep track of the level from the vertex `v`. When `w` is encountered for the first time the level of `w` is the length of the shortest path. Count how many times you discover `w` on that level. Stop expanding nodes when you go past the length of the shortest path.

#### 5-22

Do a BFS on the graph and evaluate each vertex and check it's degree. Since on each pass through a vertex, we also evaluate it's neighbors, do the neccesary replacements on that point. A recursive algorithm would be the most intuitive choice.

#### 5-23

a. Create a directed graph with vertices representing the children and the edges representing "`i` hates `j`" relations and use topological sorting  
b. Build a BFS graph from the directed graph from the previous answer. The maximum depth of this graph is the number of rows necessary

#### 5-24

The amount of strongly connected components would stay the same. The amount of reduced weakly components would be `n/3`

#### 5-25

Loop through every vertex on the graph, on each iteration, do a BFS starting from that vertex. Once the BFS is done for that vertex, scan every other vertex and if all of them are discovered, then break out of this loop and report this current vertex as the rooted tree. This would run on $O(n^2)$. Pseudocode:

```
function arborescence(G)
    root_vertex = nil
    for every vertex in G
        BFS(v)
        found_undiscovered = false
        for every vertex in G (not including v)
            if v is undiscovered
                found_undiscovered = true

        if found_undiscovered == false
            root_vertex = v

    if root_vertex == nil
        return false
    else
        return true
```

#### 5-26

a. Do a BFS starting on `v` and test whether `v` has `n-1` tree nodes rooted from `v`. You can also loop through the adjacency list of `v` and check if every other vextex in `G` is in it.  
b. Do the same as above (but the second option using the adjacency list) but do it for every vertex in the graph. The vertex that has every other vertex in it's adjacency list, would be the mother vertex. I think it's possible to be more than one.

#### 5-27

Proof by induction:

- A tournament with 2 vertices `(1,2)` has a Hamiltonian path. 1->2 or vice versa
- Now suppose our tournament with `n` vertices has a Hamiltonian path `1,..,n`. Now add a vertex `(n+1)` that is connected to every other node. 3 cases may occur:
- Case 1: If the first node of the `n` Hamiltonian path can be reached by vertex `(n+1)`, add `(n+1)` to the beginning of the path. New Hamiltonian path: `n+1,1,...,n`
- Case 2: If the last node of the `n` Hamiltonian path can reach the vertex `(n+1)`, add `(n+1)` to the end of the path. New Hamiltonian path: `1,...,n,n+1`
- Case 3: Take the first node of the `n` Hamiltonian path that can be reached by `(n+1)`. This must exist, because we are not in case 2. Call this node `k`. By definition of this node, `(k-1)` can reach `(n+1)`. Form the new Hamiltonian path as: `1,...,k-1,n+1,k,...,n`.

#### 5-28

- We know that the root of the DFS/BFS tree (with two or more children) of the graph is an articulation vertex.
- Go through each vertex and edge using DFS or BFS, any leaf in the resulting DFS/BFS tree, is not an articulation vertex.

#### 5-29

- This would be similar to 5-28
- We traverse the graph with DFS or BFS and once we construct the tree, we should delete just the leaf nodes of the tree
- I think they can be deleted in any order, as long as they are leaf nodes, it shouldn't disconnect the graph

#### 5-30

Yes, every bridge should be an edge, since that edge is a bridge node that will disconnect the graph.

#### 5-31

- Graphs
- Adjacency lists
- Adjacency matrix
- For BFS: queues
- For DFS: stack or recursion

#### 5-32

Traverse through the binary tree normally (it will do so in sorted order), keep a counter of the number of steps and stop and return the value at the `ith` step.
