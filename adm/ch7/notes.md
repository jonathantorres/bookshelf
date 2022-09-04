## Chapter 7 - Notes
- Combinatorial searches, when augmented with tree pruning techniques, can be used to find the optimal solution of small optimization problems. How small depends upon the specific problem, but typical size limits are somewhere between `15 <= n <= 50` items.
- Clever pruning can make short work of surprisingly hard combinatorial search problems. Proper pruning will have a greater impact on search time than any other factor.
- Forget about this molten metal business. Simulated annealing is effective because it spends much more of it's time working on good elements of the solution space than on bad ones, and because it avoids getting trapped repeatedly in the same local optima.
- Simulated annealing is a simple but effective technique for efficiently obtaining good but not optimal solutions to combinatorial search problems.
- I have never encountered any problem where genetic algorithms seemed to me the right way to attack it. Further, I have never seen any computational results reported using genetic algorithms that have fovorably impressed me. Stick to simulated annealing for your heuristic search voodoo needs.
