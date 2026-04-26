# Time Based Key-Value Store (LeetCode #981)

## Problem Statement

Design a time-based key-value data structure that can:
- Store multiple values for the same key at different timestamps
- Return the value with the largest timestamp <= given timestamp

## Approach

- **Data structure**: `Map<key, List<(timestamp, value)>>`
- **Set**: Append to list (timestamps are increasing)
- **Get**: Binary search for largest timestamp <= query

## Key Insight

Since timestamps are strictly increasing in set calls, the list for each key is automatically sorted. This allows binary search in get operations.

## Complexity

- **Set**: O(1) amortized
- **Get**: O(log n) where n is number of values for that key
- **Space**: O(total values stored)

