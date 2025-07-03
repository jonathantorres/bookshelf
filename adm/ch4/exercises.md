## Chapter 4 - Sorting and Searching

#### 4-1

Use a $O(n log n)$ sorting algorithm like Heapsort, which will use the priority queue for the rating of each player. Put the top `n` players in team `A` and the bottom `n` players in team `B`.

#### 4-2

a. On each iteration, keep track of the largest number and the smallest number, substract the two at the end.  
b. Substract the last two numbers, since the numbers are already sorted.  
c. Sort the numbers using a `O(n log n)` algorithm, iterate through it and find the smallest gap.  
d. Iterate over the numbers and find the smallest gap, since they are already sorted.

#### 4-3

- Sort the numbers
- Create pairs of `(min1, max2n)`, `(min1, max2n-1)`.

#### 4-4

Using bucket sort:

```
Create 3 buckets
For each Pair P
    P.color add to bucket B.color
Output contents of buckets
```

#### 4-5

- Sort the numbers
- Partition the numbers by equal sets
- Return the number of the largest set

#### 4-6

An $O(n^2)$ algorithm:

```
For i in S1 {
    For j in S2 {
        if i+j == x {
            return (i,j)
        }
    }
}
```

An $O(n log n)$ algorithm, doing binary search:

```
Sort.(S2)
For i in S1 {
    num = x - i
    found = bsearch(S2, num)
    if found {
        return (i, found)
    }
}
```

#### 4-7

a. Cross reference each bill with a check, this will run in $O(n^2)$  
b. Go through the list and check if the book is in the publisher list $O(n)$  
c. Go through the cards, and count the distinct name of students that checked out a book $O(n)$

#### 4-8

a. Sort the set `S`, go through each and compare the current element plus the next one against `x`.  
b. Same as the previous answer, but it's already sorted.

#### 4-9

a. Sort the array `B`, go through each element in `A` and do a binary search on `B`, if found add that element to the output array. Loop through `A` and `B` at the same time, and check each element?  
b. Same as the first answer. Merge `A` and `B` and remove the duplicates.

#### 4-10

- Sort the `S` array
- Loop through `S` and check each `i + k` elements to see if they add to `T`.

#### 4-11

- Calculate $n/2$. Keep track of the count for each element with a hash table, eliminate those that are not repeated at least $n/2$ times.
- Same as before, but calculating $n/4$.

#### 4-12

- Sort the set
- Call `get_minimum(S)` on the heap structure `k` times.

#### 4-13

a. max-heap, takes $O(log n)$  
b. Array, $O(1)$ as long as we have the index  
c. Doesn't matter  
d. Array, $O(1)$, just get the first element

#### 4-14

Use a binary search tree (heap) to store the final result array. Go through each sorted list and insert it into the heap. Insertion will be in $O(log n)$ time.

#### 4-15

a. Use a sorted heap in descending order and call `get-max` twice.  
b. Same as the previous answer, but calling the function `get-max` 3 times.

#### 4-16

- Calculate the middle element of the array $(n/2)$, if the array is sorted, just find the $(n/2)$ element of it.
- Yes, you must look at both sides of the partition if it's not sorted.
- I think the best way to do this is to sort the array first.

#### 4-17

a. $O(n log n)$ in the worst case  
b. $O(n log n)$ in the worst case

#### 4-18

- Use the bucket sort solution, create 3 arrays (one for each color). Loop through `A` and add each color to it's appropriate array.
- This is known as the Dutch National Flag problem.

#### 4-19

a. If all elements are out of order, then `n` has exactly `n(n-1)/2` inversions.  
b. If `P` contains `x` inversions, then it also contained `n(n-1)/2 - x` in order pairs.  
c. Any permutation of any set is likely to be equal.

#### 4-20

- Quick sort will solve this on $O(n log n)$ time.
- If you partition the array with 0 as the pivot, all negatives will be before the positives. This can be done in $O(n)$ time.

#### 4-21

I would think that it would need to do the sorting in place. Instead of allocating a new array for the final sorted output.

#### 4-22

TODO

#### 4-23

- This can be achieved by using a self balanced binary tree.
- Keep a count of duplicates on each insertions on the tree.
- The tree is not going to be greated than $log n$ elements.

#### 4-24

Sort the elements from $A[\sqrt{n}+1]$ to $A[n]$, this should be better than $O(n log n)$.

#### 4-25

- The array will therefore consist of only very few distinct numbers and all others will be repetitions.
- Iterate through the original array and create two auxiliary arrays of numbers `A` and their repetition count `N`. This is done in $O(n)$.
- Sort the two arrays, comparing keys from `A`.
- Recreate the final sorted array by taking every number in `A` and repeat it `n` times. This can be done in $O(n)$.

#### 4-26

a. Go through each item in the list and make the comparisons, since we are comparing zeros and ones then the last item does not need to be compared. Resulting in $n-1$ comparisons.  
b. Go through each item in the list and move or swap the item to the leftmost position of all zeroes if it's zero, and move to the right if it's a one.

#### 4-27

- Keep a list of the line segments, with points stored as pairs of angles relative to `q`, and sort them by the minimum of the two angles.
- Iterate through the sorted list of minimum elements, incrementing a counter whenever the start of a line segment is encountered, and decrementing the counter whenever a line segment ends.

#### 4-28

TODO

#### 4-29

- Impossible since trees are used for priority queues that run in $O(log(n))$ time.
- If this claim was true one could construct a linear time sorting algorithm by inserting all elements and then extracting all maximum elements again. Since the lower bound of $O(n log n)$ for searching this is not possible.

#### 4-30

- Putting all the names in a single array and doing binary search gives the better performance.
- I think that yes, this would be a different story if linear search was used.

#### 4-31

$O(1)$ algorithm:

```
find_largest(A, k) {
	return A[k-1]
}
```

$O(ln n)$ algorithm:

```
find_largest(A) {
	large = A[0]
	for i=1; i<A.len();i++ {
		if A[i] > large {
			large = A[i]
		}
	}
	return large
}
```

#### 4-32

- Binary search.
- Start with a random number for `n` and do binary search.

#### 4-33

Use binary search

```
// test cases
L1 = [3,7,9,11,14]
L2 = [0,1,2,3,4,5]

start = 0
end = L1.len() - 1
same_exists = same_index_and_value_exist(L1, end)

same_index_and_value_exist(list, end) {
	i = floor(end/2)
	found = false

	if (end == 0) {
		return found
	}

	if i == list[i] {
		found = true
	} else if list[i] > i {
		same_index_and_value_exist(list, i)
	}

	return found
}
```

#### 4-34

Using binary search, but finding the number that's not there. Starting with $m/2$

```
// test cases
L = [1,7,9,11,14] // 1 to 14, m = 14, n = 5
m = L[end]
not_in_a_result = not_in_a(L, m)

not_in_a(list, m) {
	mid_m = ceil(m/2)

	if bin_search(list, mid_m) != false {
		// try another number between (mid_m+1 and m)
		not_in_a(list, mid_m-1)
		// try another number between (1 and mid_m-1)
		not_in_a(list, mid_m+1)
	} else {
		return mid_m
	}
}
```

#### 4-35

- Iterate through each row of the matrix.
- Do a binary search on each row.
- This would have a performance of $O(n log m)$ in the worst case.

#### 4-36

A slow algorithm would check every possible input by looping through the `n x n` array in $O(n^2)$ time. A more efficient approach would take advantage of the fact that the array is sorted and check the first element on each row to see if it equals to zero. This would run in $O(n)$ time.

#### 4-37

See `4-37.c`

#### 4-38

TODO

#### 4-39

TODO

#### 4-40

- I would use Quicksort
- About 20 minutes
- If an integer is 32 bytes then about 32MB

#### 4-41

- Quicksort (Advantages): Fast, $O(n log n)$
- Quicksort (Disadvantages): Worst case is $O(n^2)$ but inlikely
- Merge Sort (Advantages): Fast $O(n log n)$
- Merge Sort (Disadvantages): Not stable, takes a lot of memory space when merging
- Bubble Sort (Advantages): None
- Bubble Sort (Disadvantages): Slow! $O(n^2)$
- Insertion Sort (Advantages): None
- Insertion Sort (Disadvantages): Slow! $O(n^2)$
- Selection Sort (Advantages): None
- Selection Sort (Disadvantages): Slow! $O(n^2)$
- Heapsort (Advantages): Fast and useful $O(n log n)$
- Heapsort (Disadvantages): Works on specific data structures. A better data structure must be made in order to be effective

#### 4-42

```
A = [3,4,9,4,1,3]
unique_func(A) {
    Output = []
    for each i in A {
        if i is not in Output {
            push(Output, i);
        }
    }
    return Output;
}
```

#### 4-43

- Process the file in 2MB chunks
- You'll have 250 2MB files
- Use merge sort to combine the files

#### 4-44

- I don't think is possible if you always push to the top, as a stack does.
- A Heap can do that, but it won't behave exactly as a stack.

#### 4-45

TODO

#### 4-46

- Put 6 coins on each side of the scale, one side will be heavier.
- Use the heavier side from the first weighing and put 3 coins on each side of the scale.
- Using the heavier side from the 2nd weighing, pick 2 coins and put 1 on each side of the scale.
- If the scale is balanced then the coin you didn't weigh is the heavier one. Otherwise, the scale will show which one of the other 2 is the heavy coin.
