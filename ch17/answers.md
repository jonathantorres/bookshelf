## 17. Free Space Management (Answers)

1. The free list grows over time, with fragmented free memory spaces

2. The free list is even bigger than the previous run, and it searches through more elements

3. Less searches are made, up to 3 searched elements in total, in the previous run it went up to 7 searches

4. Run the examples and see the results

5. I don't see that much difference, still going through some searches, around 99-100 searches, which is little considering that 1000 allocations are being made

6. The less the number the more frees are done on the list, since the allocated chunk is a lot smaller

7. This run can generate a fragmented free list `./malloc.py -n 10 -H 0 -p FIRST -l SIZESORT- -s 0 -c -A +4,+9,+31,-15,+8,+12,-28`
