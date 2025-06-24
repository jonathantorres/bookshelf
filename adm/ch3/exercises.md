## Chapter 3 - Data Structures

#### 3-1

```
check_parens(string s) {
    if s starts with ')'
        return false
    if s starts with '('
        return false
    amount1 = calculate_open_parens(s)
    amount2 = calculate_closing_parens(s)
    if amount1 != amount2
        return false

    return true
}
```

#### 3-2

See `3-2.c`

#### 3-3

- Array of size 4, with 3 elements, remove 1 and insert 1 and so on.
- When the array is one-fourth full, shrink it's size to half of what it was.

#### 3-4

- Using an unsorted array, this way insertion can always be at position `n`. `Insert(D, value);`
- On every insertion, track the length of the dictionary.
- For deletion, the index of the item to be deleted should be provided `Delete(D, index);`
- For searching use a pointer to the address of the element to be found `Search(D, p);`

#### 3-5

- If the tree has 3 nodes, then each node has a total of 16 bytes for a total of 48 bytes. Divide that by the amount of bytes in memory?
- If the tree has 4 nodes, which 2 of them are leafs, then:

```
4 bytes * 2 + 8 bytes * 2
8 + 16
24 bytes in total
```

Divide 24 by the amount of bytes in memory?

#### 3-6

In the functions to insert and delete an element in the tree, do a procedure which tries it's best to adjust or balance the tree. To keep it's maximum height as logarithmic as possible.

#### 3-7

- Keep track of the minimum and maximum value in the tree on each insert and delete.
- Call the `successor` and `predeccessor` functions on each insert and delete that would update these values.

#### 3-8

- Use a binary search tree.
- Implement a search function with binary search, this should take `O(log(n))` time.
- When inserting, it will always be sorted.
- When deleting, we would search for what we want to delete, which takes `O(log(n))` and then delete it.
- When checking if a member is `x epsilon T` we woulg have to search with binary search which takes `O(log(n))` and do the check then.

#### 3-9

Since all the elements in `S2` have keys larger than the keys of the elements in `S1`, those two trees can be subtrees of one tree whose root node will have a key larger than the largest key in `S1` and smaller than the smallest key in `S2`.

Then `S2` will be the right subtree and `S1` the left subtree.

The easiest way to do this is to find the minimum element of `S2` (or the maximum of `S1`) and put it as the root of the concatenated tree and then update its left and right pointer to point to the root of `S1` and `S2` respectively. The worst-case running time will be `O(h)`, which is the time of retrieving the minimum (maximum) element of a tree.

#### 3-10

Heuristic pseudocode:

```
bin_packing(weights) {
    if weights.len() == 0 {
        return 0
    }
    bins_created = 1
    cur_bin = create_bin()
    foreach weights as w {
        if (!add_to_bin(cur_bin, w)) {
            cur_bin = create_bin()
            bins_created++
        }
    }
    return bins_created
}
```

#### 3-11

- Use a binary search tree, to get the smallest value implement a `Minimum(T, x)` function that should return the minimum value.
- Use a sorted array, and use binary search to answer for a query.

#### 3-12

```
S = [3,5,7,2,4]
R = S
k = 4
for i=0; i < S.len()-1; i++ {
	set = S[i] to S[S.len()-1]
	if (black_box(set, k)) {
		R = set
		break
	}
}
```

#### 3-13

- The `Add(i,y)` function should take `O(1)` since we can access the specified index `i` in the array and add the number there.
- For `Partial-sum(i)` we have to go through all of the numbers, and add them up. This would take `O(n)`. `n` being the number of numbers we want to sum.

#### 3-14

- A hash table should be appropriate for this.
- For the `Add(k, y)` function we use the index to find the appropriate value and add the value to it there. This would run in `O(1)`.
- For `Insert(k,y)` we can use the hashing function to generate an index for us, and insert the element on the index that was generated, this would run in `O(1)`.
- `Delete(k)` would work the same as `Add(k, y)` where we just delete the element at that specific index. This would run in `O(1)`.
- `Partial-sum(k)` is trickier, we'll have to search for all those elements that are less than `k` and add them up. This will take `O(n)` where `n` is the number of elements that are less than `k`.
- Also a balanced binary search tree would be appropriate. Perhaps even better.

#### 3-15

- A hash table composed of an array of arrays can be used, in which insertions and deletions will be `O(1)`
- If the bucket array is kept sorted then search can be `O(log n)` after using the hashing function to find the index in `O(1)`.

#### 3-16

See `3-16.c`

#### 3-17

See `3-17.c`

#### 3-18

- Binary search.
- Go to the letter section of the word I'm using and proceed alphabetically from the second letter onwards.

#### 3-19

- I would probably organize them by color.
- Beyond that, you can also organize them by category (work shirts, fancy shirts, day to day shirts etc. etc.)

#### 3-20

See `3-20.c`

#### 3-21

See `3-21.c`

#### 3-22

See `3-22.c`

#### 3-23

See `3-23.c`

#### 3-24

- A trie or a ternary search tree. Use the trie to do a search if the given url is already there, I think it should take `O(log(h))` time.
- A linked list is also an option, but the search would be a lot slower with it, `O(n)`.

#### 3-25

- Sort the letters in the magazine.
- Go through each letter in the string and do a binary search on the magazine. Checking each letter against the magazine each time through the loop.
- This would execute on `O(n)`.

#### 3-26

TODO

#### 3-27

TODO

#### 3-28

```
i = 0
j = 0
for num in X {
	prod = 1
	for num2 in X {
		if i == j {
			continue
		}
		prod *= num2
		j++
	}
	M[i] = prod
	i++
}
```

#### 3-29

```
occurences = {}; // dictionary or associative array
for i=0; i < words_in_doc.length; i++ {
    if is_uppercase(first_letter(words_in_doc[i]))
       && is_uppercase(first_letter(words_in_doc[i+1])) {
        full_word = words_in_doc[i] + ' ' + words_in_doc[i+1]
        if dic_key_exists(occurences, full_word) {
            occurences[full_word] += 1;
        } else {
            occurences[full_word] = 1;
        }
    }
}
```

- A hash table would be a good option, to store the occurrences. For example: use the words as the key and the number of repeats as the value ("New York -> 6"). If the word "New York" is repeated 6 times.
