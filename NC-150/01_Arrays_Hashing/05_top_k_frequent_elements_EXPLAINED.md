# Top K Frequent Elements (LeetCode #347)

## Problem Statement

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in **any order**.

### Examples

```
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Input: nums = [1], k = 1
Output: [1]
```

### Constraints
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k is in the range [1, number of unique elements]
- Answer is guaranteed to be unique

## Intuition

This is a classic "Top K" problem. The key steps are:
1. **Count frequencies** of each element
2. **Select top K** by frequency

The challenge is doing step 2 efficiently:
- Sorting: O(n log n) - sorts all elements
- Heap: O(n log k) - maintains k elements  
- Bucket Sort: O(n) - uses frequency as index!

**Bucket Sort Insight**: Maximum possible frequency is n (array length). We can create n+1 buckets where bucket[i] holds all elements with frequency i. Then scan from highest bucket down.

## Approach

### Approach 1: Bucket Sort (Optimal)

```
1. Count frequency of each element using hash map
2. Create buckets array of size n+1
   - buckets[i] = list of elements with frequency i
3. Iterate from highest index down
   - Add elements to result until we have k elements
```

### Approach 2: Min Heap

```
1. Count frequency of each element
2. Maintain min-heap of size k (by frequency)
3. For each unique element:
   - Push to heap
   - If heap size > k, pop minimum
4. Remaining k elements are the answer
```

### Approach 3: Quickselect

```
1. Count frequency of each element
2. Use quickselect to partition: find k-th largest frequency position
3. All elements from that position onward are top k
```

## Visual Walkthrough

### Example: nums = [1,1,1,2,2,3], k = 2

```
Step 1: Count frequencies
freq = {1: 3, 2: 2, 3: 1}

Step 2: Create buckets (size = 6+1 = 7)
index:    0    1    2    3    4    5    6
bucket:  []   [3]  [2]  [1]  []   []   []
              ↑    ↑    ↑
              freq=1 freq=2 freq=3

Step 3: Scan from right to left, collect k=2 elements
- bucket[6]: empty
- bucket[5]: empty
- bucket[4]: empty
- bucket[3]: [1] → result = [1]
- bucket[2]: [2] → result = [1, 2] ← we have k=2 elements!

Return [1, 2]
```

### Min Heap Approach

```
Maintain min-heap of size k=2:

Process (1, 3): heap = [(3,1)]
Process (2, 2): heap = [(2,2), (3,1)]
Process (3, 1): heap = [(2,2), (3,1)] - push (1,3), pop (1,3) since 1 < 2

Final heap: [(2,2), (3,1)]
Result: [2, 1] (elements with freq 2 and 3)
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Single element | `[1], k=1` | `[1]` | Minimal case |
| All same | `[1,1,1], k=1` | `[1]` | Only one unique element |
| All different | `[1,2,3], k=3` | `[1,2,3]` | All have same frequency |
| k equals unique | `[1,2], k=2` | `[1,2]` | Return all unique |
| Negative numbers | `[-1,-1,2], k=1` | `[-1]` | Handle negatives |
| Tie in frequency | `[1,1,2,2,3], k=2` | `[1,2]` or any 2 | Multiple valid answers |

## Complexity Analysis

### Bucket Sort
- **Time Complexity**: O(n)
  - O(n) to count frequencies
  - O(n) to create and fill buckets
  - O(n) to scan buckets (at most n elements total)
  
- **Space Complexity**: O(n)
  - O(n) for frequency map
  - O(n) for buckets

### Min Heap
- **Time Complexity**: O(n log k)
  - O(n) to count frequencies
  - O(n log k) for heap operations on n elements with heap size k
  
- **Space Complexity**: O(n + k)
  - O(n) for frequency map
  - O(k) for heap

### Quickselect
- **Time Complexity**: O(n) average, O(n²) worst
  - Partitioning is O(n), expected log n partitions
  
- **Space Complexity**: O(n)
  - For frequency map and unique elements array

## Common Mistakes

1. **Using max-heap instead of min-heap**: Max-heap doesn't help with "top k" - we need to evict smallest
2. **Not understanding bucket indexing**: bucket[freq] holds elements, not bucket[value]
3. **Off-by-one in bucket size**: Need n+1 buckets (0 to n)
4. **Heap with wrong comparison**: Heap should compare by frequency, not value

## Related Problems

- [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) - Quickselect/Heap
- [Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) - Similar bucket sort idea
- [Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) - With lexicographic order

## Key Takeaways

1. **Bucket sort for bounded range**: When values are bounded (here: 1 to n), bucket sort gives O(n)
2. **Min-heap for top K**: Counterintuitive but efficient - evict smallest to keep largest
3. **Count first, select second**: Two-phase approach is clean and efficient
4. **Python's Counter.most_common()**: Built-in solution, uses heap internally
5. **Quickselect alternative**: O(n) average but O(n²) worst case

